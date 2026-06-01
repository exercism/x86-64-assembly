section .rodata
align 16

SIGN_MASK: dd 0, 0x80000000, 0, 0

C1:   dd -0.16666666666666667          ; - 1 / 3!
      dd -0.5                          ; - 1 / 2!
      dd 0.16666666666666667           ; 1 / 3!
      dd 0.5                           ; 1 / 2!

C2:   dd 0.008333333333333333          ; 1 / 5!
      dd 0.04166666666666667           ; 1 / 4!
      times 2 dd 0

C3:   dd -0.0001984126984126984        ; - 1 / 7!
      dd -0.001388888888888889         ; - 1 / 6!
      dd 0.0001984126984126984         ;  1 / 7!
      dd 0.001388888888888889          ;  1 / 6!

C4:   dd 2.7557319223985893e-06        ; 1 / 9!
      dd 2.4801587301587302e-05        ; 1 / 8!
      times 2 dd 0

TWO_DIV_PI: times 4 dd 0.6366197723675814     ; 2 / PI
PI_DIV_TWO: times 4 dd 1.5707963705062866     ; PI / 2
ONE: times 4 dd 1.0

ONE_DIV_LOG2: dd 1.4426950408889634
LN2: dd 0.693147180559

FLOOR equ 1

section .text

global complex_real
global complex_imaginary
global complex_mul
global complex_add
global complex_sub
global complex_div
global complex_abs
global complex_conjugate
global complex_exp
global complex_real_add
global real_complex_add
global complex_real_sub
global real_complex_sub
global complex_real_mul
global real_complex_mul
global complex_real_div
global real_complex_div

%macro exp_taylor 0
    ; This macro calculates e^x
    ;
    ; For a large x, taylor expansion takes much longer to converge
    ; so we first reduce x to a small r and to a power of two k
    ;
    ; We know that e^x = 2^(x * log2(e)) = 2^(x / ln2)
    ;
    ; let z = x / ln2 and z = k + f, where k = floor(z) and f < 1
    ; then 2^z = 2^(k + f) = 2^k + 2^f
    ;
    ; let r = x - k*ln2 = z*ln2 - k*ln2 = ln2*(z - k) = ln2*f
    ; then 2^f = e^(ln2*f) = e^r
    ;
    ; so e^x = 2^k * e^r
    ;
    ; r is small, so we can calculate e^r with taylor expansion
    ; and 2^k can be applied directly to e^r with shifts on the raw IEE exponent field

    movaps xmm1, xmm4
    mulss xmm1, [rel ONE_DIV_LOG2]   ; xmm1 = x * log2e = x / ln2 = z
    roundss xmm1, xmm1, FLOOR        ; xmm1 = floor(z) = k
    cvtss2si eax, xmm1               ; we save k to shift the result later

    ; now we need to calculate r = x - k*ln2
    movaps xmm2, xmm1
    mulss xmm2, [rel LN2]            ; xmm2 = k*kn2
    subss xmm4, xmm2                 ; xmm4 = x - k*ln2 = r

    ; we are now calculating the taylor expansion of r with 7 factors:
    ; e^r = 1 + (r^2)/2! + ... + (r^7)/7!
    ;
    ; we have the inverse of the factorials already precomputed and saved in memory
    ; we start from 1/7! and continuously multiply x and add the next factorial inverse

    movss xmm2, [rel ONE] ; cache 1.0 in xmm2 to be used later. This saves one memory load

    movss xmm1, [rel C3 + 8]
    mulss xmm1, xmm4
    addss xmm1, [rel C3 + 12]
    mulss xmm1, xmm4
    addss xmm1, [rel C2]
    mulss xmm1, xmm4
    addss xmm1, [rel C2 + 4]
    mulss xmm1, xmm4
    addss xmm1, [rel C1 + 8]
    mulss xmm1, xmm4
    addss xmm1, [rel C1 + 12]
    mulss xmm1, xmm4
    addss xmm1, xmm2
    mulss xmm1, xmm4
    addss xmm1, xmm2

    ; now xmm1 = e^r

    add eax, 127
    shl eax, 23
    movd xmm2, eax ; now xmm2 is 2^k in IEEE format

    mulss xmm1, xmm2 ; xmm1 = e^r * 2^k = e^x
    pshufd xmm4, xmm1, 0b00_00_00_00 ; we pack e^x in the first two lanes of xmm4
%endmacro

%macro sin_cos_taylor 0
   insertps xmm0, xmm0, 0b01_00_1100

   ; xmm0 now holds the angle on the two first lanes
   ; we calculate sin and cos on both lanes in parallel using SIMD operations

   movaps xmm2, [rel ONE]         ; 1.0f
   movaps xmm1, [rel TWO_DIV_PI]  ; 2 / PI

   mulps xmm1, xmm0               ; (2 / PI) * angle
   roundps xmm1, xmm1, FLOOR      ; xmm1 = floor ((2 / PI) * angle) -> the whole number of quadrants
   cvtss2si eax, xmm1             ; eax mod 4 indicates the quadrant

   ; This follows from:
   ;
   ; let the angle be denoted as 2 * PI * r + k, where k < 2 * PI
   ;
   ; (2 * PI * r + k) * (2 / PI) = 4 * r + 2 * k / PI
   ; 4 * r mod 4 == 0 -> (4 * r + 2 * k / PI) mod 4 = (2 * k / PI) mod 4
   ;
   ;
   ; (2 * k / PI) mod 4 == 0 -> 2 * k < PI     -> k < PI / 2     (1º quadrant)
   ; (2 * k / PI) mod 4 == 1 -> 2 * k < 2 * PI -> k < PI         (2º quadrant)
   ; (2 * k / PI) mod 4 == 2 -> 2 * k < 3 * PI -> k < 3 * PI / 2 (3º quadrant)
   ; (2 * k / PI) mod 4 == 3 -> 2 * k < 4 * PI -> k < 2 * PI     (4º quadrant)
   ;
   ; since k < 2 * PI, we've exhausted all options

   mulps xmm1, [rel PI_DIV_TWO]  ; xmm1 = floor ((2 / PI) * angle) * (PI / 2)
   ; now xmm1 holds the angle corresponding to the whole number of quadrants

   subps xmm0, xmm1              ; xmm0 = angle - (floor ((2 / PI) * angle) * (PI / 2))
   ; now xmm0 holds the residual angle x, reduced to the first quadrant

   ; we go backwards from the last term in the taylor expansion, so that multiplication accumulates correctly
   ; at the end the factor divided by n! will correspond to x^n
   movaps xmm1, xmm0
   mulps xmm1, xmm0
   movaps xmm3, xmm1
   ; xmm1 = x^2
   mulps xmm3, [rel C4]
   ; sin = (x^2 / 9!), cos = (x^2 / 8!)
   addps xmm3, [rel C3]
   ; sin = (x^2 / 9!) - (1 / 7!), cos = (x^2 / 8!) - (1 / 6!)
   mulps xmm3, xmm1
   ; sin = (x^4 / 9!) - (x^2 / 7!), cos = (x^4 / 8!) - (x^2 / 6!)
   addps xmm3, [rel C2]
   ; sin = (x^4 / 9!) - (x^2 / 7!) + 1 / 5!, cos = (x^4 / 8!) - (x^2 / 6!) + (1 / 4!)
   mulps xmm3, xmm1
   ; sin = (x^6 / 9!) - (x^4 / 7!) + (x^2 / 5!), cos = (x^6 / 8!) - (x^4 / 6!) + (x^2 / 4!)
   addps xmm3, [rel C1]
   ; sin = (x^6 / 9!) - (x^4 / 7!) + (x^2 / 5!) - (1 / 3!), cos = (x^6 / 8!) - (x^4 / 6!) + (x^2 / 4!) - (1 / 2!)
   mulps xmm3, xmm1
   ; sin = (x^8 / 9!) - (x^6 / 7!) + (x^4 / 5!) - (x^2 / 3!), cos = (x^8 / 8!) - (x^6 / 6!) + (x^4 / 4!) - (x^2 / 2!)
   addps xmm3, xmm2
   ; sin = (x^8 / 9!) - (x^6 / 7!) + (x^4 / 5!) - (x^2 / 3!) + 1, cos = (x^8 / 8!) - (x^6 / 6!) + (x^4 / 4!) - (x^2 / 2!) + 1
   mulss xmm3, xmm0
   ; cos is complete, sin requires one extra multiplication by x
   ; Result: sin = (x^9 / 9!) - (x^7 / 7!) + (x^5 / 5!) - (x^3 / 3!) + x, cos = (x^8 / 8!) - (x^6 / 6!) + (x^4 / 4!) - (x^2 / 2!) + 1

   ; We have calculated sin and cos for the reduced angle at the first quadrant
   ; So this is our base case
   ;
   ; For the other quadrants, we rely on the following:
   ; 1. on the second quadrant, cos is negative and sin is positive
   ; 2. on the third quadrant, cos is negative and sin is negative
   ; 3. on the fourth quadrant, cos is positive and sin is negative
   ; 4. sin and cos change places on the second and fourth quadrants.
   ;
   ; This last statement follows geometrically, given that:
   ; 1. sin is the vertical distance formed by the angle on the unit circle
   ; 2. cos is the horizontal distance formed by the angle on the unit circle

   ; we now save the two lanes of xmm0 and check the quadrant
   movq rcx, xmm3
   mov rdx, rcx
   shr rdx, 32     ; cos
   mov ecx, ecx    ; sin

   ; ecx will hold the value of sin(x) at the end
   ; edx will hold the value of cos(x) at the end

   mov r8d, 1
   shl r8d, 31
   mov r9d, edx
   xor r9d, r8d    ; -cos
   xor r8d, ecx    ; -sin

   and eax, 3      ; mod 4

   ; 4° quadrant
   cmp eax, 3
   cmovz edx, ecx  ; sin
   cmovz ecx, r9d  ; -cos

   ; 3° quadrant
   cmp eax, 2
   cmovz ecx, r8d  ; -sin
   cmovz edx, r9d  ; -cos

   ; 2° quadrant
   cmp eax, 1
   cmovz ecx, edx  ; cos
   cmovz edx, r8d  ; -sin

   ; otherwise, 1° quadrant

   shl rcx, 32     ; sin goes to second lane position
   or rcx, rdx     ; we accumulate, rcx now holds [ cos, sin ]
   movq xmm0, rcx  ; we restore in XMM0
%endmacro

complex_real:
    ; result is already in xmm0
    ret

complex_imaginary:
    insertps xmm0, xmm0, 0b01_00_1110
    ret

complex_abs:
    mulps xmm0, xmm0
    pshufd xmm1, xmm0, 0b00_00_00_01
    addps xmm0, xmm1
    sqrtss xmm0, xmm0
    ret

complex_conjugate:
    xorps xmm0, [rel SIGN_MASK]
    ret

complex_exp:
    movaps xmm4, xmm0
    exp_taylor
    sin_cos_taylor
    mulps xmm0, xmm4
    ret

real_complex_add:
    insertps xmm0, xmm0, 0b00_00_1110
    jmp complex_add
complex_real_add:
    insertps xmm1, xmm1, 0b00_00_1110
complex_add:
    addps xmm0, xmm1
    ret

real_complex_sub:
    insertps xmm0, xmm0, 0b00_00_1110
    jmp complex_sub
complex_real_sub:
    insertps xmm1, xmm1, 0b00_00_1110
complex_sub:
    subps xmm0, xmm1
    ret

real_complex_mul:
    insertps xmm0, xmm0, 0b00_00_1110
    jmp complex_mul
complex_real_mul:
    insertps xmm1, xmm1, 0b00_00_1110
complex_mul:
    pshufd xmm0, xmm0, 0b00_01_01_00 ; [a, b, b, a]
    pshufd xmm1, xmm1, 0b01_01_00_00 ; [c, c, d, d]
    mulps xmm0, xmm1                 ; [a*c, b*c, b*d, a*d]
    pshufd xmm1, xmm0, 0b00_00_11_10 ; [b*d, a*d, _, _]
    addsubps xmm0, xmm1
    ret

real_complex_div:
    insertps xmm0, xmm0, 0b00_00_1110
    jmp complex_div
complex_real_div:
    insertps xmm1, xmm1, 0b00_00_1110
complex_div:
    movaps xmm2, xmm1
    mulps xmm2, xmm1
    pshufd xmm3, xmm2, 0b00_00_00_01
    addps xmm2, xmm3
    pshufd xmm0, xmm0, 0b01_00_00_01    ; [b, a, a, b]
    pshufd xmm1, xmm1, 0b01_01_00_00    ; [c, c, d, d]
    mulps xmm0, xmm1                    ; [b*c, a*c, a*d, b*d]
    pshufd xmm1, xmm0, 0b00_00_11_10    ; [a*d, b*d, _, _]
    addsubps xmm0, xmm1                 ; [b*c - a*d, a*c + b*d]
    divps xmm0, xmm2                    ; [(b*c - a*d)/(c^2 + d^2), (a*c + b*d)/(c^2 + d^2)]
    pshufd xmm0, xmm0, 0b00_00_00_01    ; swap -> [(a*c + b*d)/(c^2 + d^2), (b*c - a*d)/(c^2 + d^2)]
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
