default rel

section .data
    negate_mask dd 0x80000000

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

; Those functions work with a struct of 2 floats
;
; As is the case with structs, parameters are passed
; in a single register, whenever possible
;
; Here, both parameters are in different lanes (32-bit)
; of a single XMM register
;
; One of the ways to move bits from lanes,
; in order to access those different members,
; is shifting bytes (not bits) using psrldq or pslldq
;
; However, having the bits packed in two lanes of a single register
; means we sometimes can use SIMD instructions,
; which operate in all lanes in parallel.
; This is of course much more efficient

%macro extract_members 2
    ; Below implementation depends on SSE2
    movaps %1, %2
    psrldq %1, 4

    ; Alternative implementation
    ; movq rax, %2
    ; shr rax, 32
    ; movd %1, eax
%endmacro

%macro accumulate_members 3
    ; Below implementation depends on SSE2
    movaps %1, %3
    pslldq %1, 4
    movss %1, %2

    ; Alternative implementation
    ; movd eax, %3
    ; shl rax, 32
    ; xor rdx, rdx
    ; movd edx, %2
    ; or rax, rdx
    ; movq %1, rax
%endmacro

complex_real:
    ; both real and imag are in xmm0
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; return is real in xmm0's first lane
    ; where it is already
    ret

complex_imaginary:
    ; both real and imag are in xmm0
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; return is imag in xmm0's first lane

    extract_members xmm0, xmm0
    ret

complex_mul:
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; Since there are 2 structs, values are in xmm0 and xmm1
    ; return is a new struct in xmm0's first two lanes

    ; Below implementation depends on SSE3

    movaps xmm6, xmm1
    mulps xmm6, xmm0 ; xmm6's first 2 lanes are now:
                     ; (a * c) and (b * d)

    hsubps xmm6, xmm6 ; xmm6's first lane is now:
                      ; a * c - d * d

    extract_members xmm2, xmm0
    extract_members xmm3, xmm1

    mulss xmm2, xmm1 ; b * c
    mulss xmm3, xmm0 ; a * d
    addss xmm2, xmm3 ; b * c + a * d

    accumulate_members xmm0, xmm6, xmm2

    ; Alternative implementation
    ; extract_members xmm2, xmm0
    ; extract_members xmm3, xmm1

    ; movss xmm4, xmm0
    ; mulss xmm4, xmm1 ; a*c

    ; movss xmm5, xmm2
    ; mulss xmm5, xmm3 ; b*d

    ; subss xmm4, xmm5 ; a*c - b*d

    ; mulss xmm2, xmm1 ; b*c
    ; mulss xmm3, xmm0 ; a*d
    ; addss xmm2, xmm3 ; b*c + a*d

    ; accumulate_members xmm0, xmm4, xmm2
    ret

complex_add:
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; Since there are 2 structs, values are in xmm0 and xmm1
    ; return is a new struct in xmm0's first two lanes

    addps xmm0, xmm1
    ret

complex_sub:
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; Since there are 2 structs, values are in xmm0 and xmm1
    ; return is a new struct in xmm0's first two lanes

    subps xmm0, xmm1
    ret

complex_div:
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; Since there are 2 structs, values are in xmm0 and xmm1
    ; return is a new struct in xmm0's first two lanes

    ; Below implementation depends on SSE3

    movaps xmm2, xmm1
    mulps xmm2, xmm0 ; xmm2's first 2 lanes are now:
                     ; (a * c) and (b * d)

    haddps xmm2, xmm2 ; xmm2's first lane is now:
                      ; a * c + b * d

    movaps xmm3, xmm1
    mulps xmm3, xmm3 ; xmm3's first 2 lanes are now:
                     ; (c²) and (d²)

    haddps xmm3, xmm3 ; xmm3's first lane is now:
                      ; c² + d²

    divss xmm2, xmm3 ; (a * c + b * d) / (c² + d²) -> real part

    extract_members xmm4, xmm0
    extract_members xmm5, xmm1

    mulss xmm4, xmm1 ; b * c
    mulss xmm5, xmm0 ; a * d
    subss xmm4, xmm5 ; b * c - a * d
    divss xmm4, xmm3 ; (b * c - a * d) / (c² + d²) -> imag part

    accumulate_members xmm0, xmm2, xmm4

    ; Alternative implementation
    ;
    ; extract_members xmm2, xmm0
    ; extract_members xmm3, xmm1

    ; movss xmm4, xmm1
    ; mulss xmm4, xmm4 ; c²

    ; movss xmm5, xmm3
    ; mulss xmm5, xmm5 ; d²

    ; addss xmm4, xmm5 ; c² + d²

    ; movss xmm5, xmm0
    ; mulss xmm5, xmm1 ; a * c

    ; movss xmm6, xmm2
    ; mulss xmm6, xmm3 ; b * d

    ; addss xmm5, xmm6 ; a*c + b*d

    ; divss xmm5, xmm4 ; (a*c + b*d) / (c² + d²) -> real part

    ; mulss xmm2, xmm1 ; b*c
    ; mulss xmm3, xmm0 ; a*d
    ; subss xmm2, xmm3 ; b*c - a*d

    ; divss xmm2, xmm4 ; (b * c - a * d) / (c² + d²) -> imag part

    ; accumulate_members xmm0, xmm5, xmm2
    ret

complex_abs:
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; return is a (real² + imag²)⁽⁰·⁵⁾ as a float in xmm0

    ; Below implementation depends on SSE3

    mulps xmm0, xmm0 ; xmm0's first 2 lanes are now:
                     ; (a²) and (b²)

    haddps xmm0, xmm0 ; xmm0's first lane is now:
                      ; a² + b²

    sqrtss xmm0, xmm0 ; xmm0's first lane is now:
                      ; sqrt(a² + b²)

    ; Alternative implementation
    ; extract_members xmm1, xmm0
    ; mulss xmm1, xmm1
    ; mulss xmm0, xmm0
    ; addss xmm0, xmm1
    ; sqrtss xmm0, xmm0
    ret

complex_conjugate:
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; return is a new struct with imag part negated, in xmm0

    movss xmm1, dword [negate_mask]
    pslldq xmm1, 4
    xorps xmm0, xmm1
    ret

; 3 helpers for calculating complex_exp:
; A-> exp_taylor: calculates e^a, where a is a float
; B-> cos_taylor: calculates cos(x), where x is in radians (a float)
; C-> sin_taylor: calculates sin(x), where x is in radians (a float)
;
; They all use a taylor expansion, but accumulating the factorial
; to avoid unnecessary duplication of work
;
; Instead of checking for precision each iteration, they all loop
; until the end of max iterations, which were set as 10

exp_taylor:
    mov rax, 1 ; n
    cvtsi2ss xmm4, eax ; term
    movss xmm5, xmm4 ; sum
    mov rcx, 10 ; num of iterations
.loop:
    movss xmm6, xmm2
    cvtsi2ss xmm7, eax

    divss xmm6, xmm7 ; x / n
    mulss xmm4, xmm6 ; term *= x / n
    addss xmm5, xmm4 ; sum += term

    inc eax ; n++
    loop .loop

    movss xmm2, xmm5 ; return sum
    ret

cos_taylor:
    mov rax, 1 ; n
    cvtsi2ss xmm4, eax ; term
    movss xmm5, xmm4 ; sum
    mov rcx, 10 ; num of iterations

    movss xmm6, xmm2
    mulss xmm6, xmm6 ; x²
.loop:
    mov r8, rax
    shl r8, 1 ; 2*n
    lea r9, [r8 - 1]
    imul r9, r8 ; (2*n - 1) * 2*n
    cvtsi2ss xmm7, r9d

    movss xmm8, xmm6
    divss xmm8, xmm7 ; x² / ((2*n - 1) * 2*n)

    movss xmm7, dword [negate_mask]
    xorps xmm8, xmm7 ; - x² / ((2*n - 1) * 2*n)

    mulss xmm4, xmm8 ; term *= - x² / ((2*n - 1) * 2*n)
    addss xmm5, xmm4 ; sum += term

    inc eax ; n++
    loop .loop

    movss xmm2, xmm5 ; return sum
    ret

sin_taylor:
    movmskps r10d, xmm2
    bt r10d, 0
    jnc .positive

    movss xmm7, dword [negate_mask]
    andps xmm2, xmm7

.positive:
    mov rax, 1 ; n
    movss xmm4, xmm2 ; term
    movss xmm5, xmm4 ; sum
    mov rcx, 10 ; num of iterations

    movss xmm6, xmm2
    mulss xmm6, xmm6 ; x²
.loop:
    mov r8, rax
    shl r8, 1 ; 2*n
    lea r9, [r8 + 1] ; 2*n + 1
    imul r9, r8 ; (2*n + 1) * 2*n
    cvtsi2ss xmm7, r9d

    movss xmm8, xmm6

    divss xmm8, xmm7 ; x² / ((2*n + 1) * 2*n)

    movss xmm7, dword [negate_mask]
    xorps xmm8, xmm7 ; - x² / ((2*n + 1) * 2*n)

    mulss xmm4, xmm8 ; term *= - x² / ((2*n + 1) * 2*n)
    addss xmm5, xmm4 ; sum += term

    inc eax ; n++
    loop .loop

    movss xmm2, xmm5

    bt r10d, 0
    jnc .end ; if sign not set, return sum
    ; otherwise return -sum

    movss xmm7, dword [negate_mask]
    xorps xmm2, xmm7
.end:
    ret

complex_exp:
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; return is a new struct in xmm0

    extract_members xmm1, xmm0

    movss xmm2, xmm0 ; a
    call exp_taylor
    movss xmm0, xmm2 ; e^a

    movss xmm2, xmm1 ; b
    call cos_taylor
    movss xmm3, xmm2
    mulss xmm3, xmm0 ; e^a * cos(b) -> real part

    movss xmm2, xmm1 ; b
    call sin_taylor
    mulss xmm2, xmm0 ; e^a * sin(b) -> imag part

    accumulate_members xmm0, xmm3, xmm2
    ret

complex_real_add:
    ; XMM0 - first number (as a complex_t)
    ; XMM1 - second number (as a float)
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; return is a complex in XMM0

    xorps xmm2, xmm2
    movss xmm2, xmm1
    addps xmm0, xmm2
    ret

real_complex_add:
    ; XMM0 - first number (as a float)
    ; XMM1 - second number (as a complex_t)
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; return is a complex in XMM0

    xorps xmm2, xmm2
    movss xmm2, xmm0
    addps xmm2, xmm1
    movaps xmm0, xmm2
    ret

complex_real_sub:
    ; XMM0 - first number (as a complex_t)
    ; XMM1 - second number (as a float)
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; return is a complex in XMM0

    xorps xmm2, xmm2
    movss xmm2, xmm1
    subps xmm0, xmm2
    ret

real_complex_sub:
    ; XMM0 - first number (as a float)
    ; XMM1 - second number (as a complex_t)
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; return is a complex in XMM0

    xorps xmm2, xmm2
    movss xmm2, xmm0
    subps xmm2, xmm1
    movaps xmm0, xmm2
    ret

complex_real_mul:
    ; XMM0 - first number (as a complex_t)
    ; XMM1 - second number (as a float)
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; return is a complex in XMM0

    xorps xmm2, xmm2
    movss xmm2, xmm1
    movaps xmm1, xmm2
    jmp complex_mul

real_complex_mul:
    ; XMM0 - first number (as a float)
    ; XMM1 - second number (as a complex_t)
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; return is a complex in XMM0

    xorps xmm2, xmm2
    movss xmm2, xmm0
    movaps xmm0, xmm2
    jmp complex_mul

complex_real_div:
    ; XMM0 - first number (as a complex_t)
    ; XMM1 - second number (as a float)
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; return is a complex in XMM0

    xorps xmm2, xmm2
    movss xmm2, xmm1
    movaps xmm1, xmm2
    jmp complex_div

real_complex_div:
    ; XMM0 - first number (as a float)
    ; XMM1 - second number (as a complex_t)
    ; both real and imag are in one single xmm
    ; real -> first lane (32-bit)
    ; imag -> second lane (32-bit)
    ; return is a complex in XMM0

    xorps xmm2, xmm2
    movss xmm2, xmm0
    movaps xmm0, xmm2
    jmp complex_div

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
