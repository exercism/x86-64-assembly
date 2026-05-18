section .rodata

align 16
C1:   dd -0.16666666666666667          ; - 1 / 3!
      dd -0.5                          ; - 1 / 2!
      times 2 dd 0

C2:   dd 0.008333333333333333          ; 1 / 5!
      dd 0.04166666666666667           ; 1 / 4!
      times 2 dd 0

C3:   dd -0.0001984126984126984        ; - 1 / 7!
      dd -0.001388888888888889         ; - 1 / 6!
      times 2 dd 0

C4:   dd 2.7557319223985893e-06        ; 1 / 9!
      dd 2.4801587301587302e-05        ; 1 / 8!
      times 2 dd 0

TWO_DIV_PI: times 4 dd 0.6366197723675814     ; 2 / PI
PI_DIV_TWO: times 4 dd 1.5707963705062866     ; PI / 2
TO_RADIAN: times 4 dd 0.017453292519943295    ; PI / 180
ONE: times 4 dd 1.0

ABS_MSK: dd 0x7FFFFFFF                ; CLEARS SIGN BIT IN A 32-BIT FLOAT
INF: dd 0x7F800000
DELTA: dd 0.0001

FLOOR equ 1

section .text
global find_sequence

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                         TRIGONOMETRIC HELPERS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                SIN_COS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Algorithm is:
; 1. reduces the problem to the first quadrant.
; 2. calculates both sin and cos using taylor expansion with
;    precalculated constants for factorial divisors.
; 3. fix sign and swaps sin and cos according to the quadrant
;
; The argument (angle, in degrees) is passed in XMM0.
; It is converted to radians by the function.
;
; Returns sin(x) and cos(x) packed in XMM0: [sin, cos]
;
; CLOBBERS: rax, rcx, rdx, r8, r9, xmm0, xmm1, xmm2, xmm3
; PRESERVES: r10, r11, xmm4 - xmm15
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro sin_cos_taylor 0
   insertps xmm0, xmm0, 0b00_01_1100

   ; xmm0 now holds the angle on the two first lanes
   ; we calculate sin and cos on both lanes in parallel using SIMD operations

   mulps xmm0, [rel TO_RADIAN]   ; converts from degrees to radians

   movaps xmm2, [rel ONE]         ; 1.0f
   movaps xmm1, [rel TWO_DIV_PI]  ; 2 / PI

   mulps xmm1, xmm0              ; (2 / PI) * angle
   roundps xmm1, xmm1, FLOOR     ; xmm1 = floor ((2 / PI) * angle) -> the whole number of quadrants
   cvtss2si eax, xmm1            ; eax mod 4 indicates the quadrant

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

   movaps xmm3, xmm0             ; x
   mulps xmm0, xmm0              ; x^2

   movaps xmm1, xmm0

   ; we go backwards from the last term in the taylor expansion, so that multiplication accumulates correctly
   ; at the end the factor divided by n! will correspond to x^n
   mulps xmm0, [rel C4]  ; sin = (x^2 / 9!), cos = (x^2 / 8!)
   addps xmm0, [rel C3]  ; sin = (x^2 / 9!) - (1 / 7!), cos = (x^2 / 8!) - (1 / 6!)
   mulps xmm0, xmm1      ; sin = (x^4 / 9!) - (x^2 / 7!), cos = (x^4 / 8!) - (x^2 / 6!)
   addps xmm0, [rel C2]  ; sin = (x^4 / 9!) - (x^2 / 7!) + 1 / 5!, cos = (x^4 / 8!) - (x^2 / 6!) + (1 / 4!)
   mulps xmm0, xmm1      ; sin = (x^6 / 9!) - (x^4 / 7!) + (x^2 / 5!), cos = (x^6 / 8!) - (x^4 / 6!) + (x^2 / 4!)
   addps xmm0, [rel C1]  ; sin = (x^6 / 9!) - (x^4 / 7!) + (x^2 / 5!) - (1 / 3!), cos = (x^6 / 8!) - (x^4 / 6!) + (x^2 / 4!) - (1 / 2!)
   mulps xmm0, xmm1      ; sin = (x^8 / 9!) - (x^6 / 7!) + (x^4 / 5!) - (x^2 / 3!), cos = (x^8 / 8!) - (x^6 / 6!) + (x^4 / 4!) - (x^2 / 2!)
   addps xmm0, xmm2      ; sin = (x^8 / 9!) - (x^6 / 7!) + (x^4 / 5!) - (x^2 / 3!) + 1, cos = (x^8 / 8!) - (x^6 / 6!) + (x^4 / 4!) - (x^2 / 2!) + 1
   mulss xmm0, xmm3      ; cos is complete, sin requires one extra multiplication by x
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
   movq rcx, xmm0
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

   shl rdx, 32     ; cos goes back to second lane position
   or rcx, rdx     ; we accumulate, rcx now holds [ sin, cos ]
   movq xmm0, rcx  ; we restore in XMM0
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                DISTANCE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Takes a packed register with 2 arguments
; Returns the squared distance on its first lane
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
%macro squared_distance 1
   mulps %1, %1
   haddps %1, %1
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                SIGNATURE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; extern size_t find_sequence(uint32_t buffer[], const coordinate_t start, const prism_t *prisms, size_t num_prisms);
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                          STRUCTS' MEMORY LAYOUT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; coordinate_t:
; 1. float x
; 2. float y
; 3. float angle
; - alignment(coordinate_t) == 4
; - sizeof(coordinate_t) == 12
;
; prism_t:
; 1. uint32_t id
; 2. float x
; 3. float y
; 4. float angle
; - alignment(prism_t) == 4
; - sizeof(prism_t) == 16
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                            CALLING CONVENTION
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; xmm0 -> [ x, y ] as packed 32-bit floating-point numbers
; xmm1 -> float angle
;
; rdi -> buffer
; rsi -> prisms
; rdx -> num_prisms
;
; return in rax
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
find_sequence:
   push r12
   push r13
   xor r11d, r11d

   test rdx, rdx
   jz .end

   shl rdx, 4
   mov r13, rdx          ; length of prisms, in bytes

   movq xmm5, xmm0       ; xmm5 = [start x, start y]

   insertps xmm1, xmm1, 0b00_00_1110 ; zeroes-out all lanes but the first
   movaps xmm0, xmm1
   movaps xmm4, xmm1     ; accumulator for refracted angle

   sin_cos_taylor
   ; xmm0 = [sin, cos]

   movaps xmm6, xmm0     ; xmm6 = [sin, cos]

   ; constants
   movss xmm7, [rel DELTA]
   movss xmm8, [rel ABS_MSK]
.while_true:
   xor ecx, ecx
   movss xmm9, [rel INF]       ; running minimum squared distance
   xor r12, r12                ; pointer to the running minimum prism. Starts as NULL
.loop:
   cmp rcx, r13
   jae .end_loop

   lea r10, [rsi + rcx]
   add rcx, 16

   mov rdx, [r10 + 4]
   movq xmm0, rdx              ; xmm0 = [x, y]
   subps xmm0, xmm5            ; xmm0 = [delta x, delta y]

   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   ; We need to check 3 things:
   ;
   ; 1. the prism is on the ray's path.
   ; 2. the prism is in the same direction the ray is going.
   ; 3. the prism's position is different than the last ray position (it's not the same prism).
   ;
   ; Using the tangent directly may give errors when cos(angle) approaches zero, or when delta x approaches zero
   ; So instead we compare two different vectors:
   ;
   ; A - the unit vector for the ray's direction, i.e., { x = cos(angle), y = sin(angle) }
   ; B - the vector formed of the delta between the ray and the prism, i.e., { x = delta x, y = delta y }
   ;
   ; To check the last two conditions, we use the dot product between them.
   ; If it is negative, condition 2 fails
   ; If it is zero, either condition 3 or condition 1 fails (prism at same position as the ray, or perpendicular to the path)
   ;
   ; The dot product must be strictly positive, then.
   ;
   ; To check the first condition, we need to check if the angle between the vectors is zero.
   ; We use the following property:
   ;
   ; cross / dot = tan(a), where a is the angle between vectors A and B
   ;
   ; For an angle approaching zero, tan(angle) also approaches zero
   ; However, we need to account for precision errors, so we use a minimum DELTA as substitute for tan(angle):
   ;
   ; ABS(cross / dot) <= DELTA
   ;
   ; To avoid an expensive DIVSS instruction, we use the equivalent;
   ;
   ; ABS(cross) <= DELTA * ABS(dot)
   ;
   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

   ; first we check the dot product (conditions 2 and 3)

   pshufd xmm2, xmm6, 0b11_10_00_01 ; xmm2 = [cos, sin]
   mulps xmm2, xmm0                 ; xmm2 = [delta x * cos, delta y * sin]
   haddps xmm2, xmm2                ; xmm2 = dot product (projection on the line)

   ucomiss xmm2, xmm7
   jbe .loop                   ; prism is not in front of the laser

   ; dot is positive after the jump

   mulss xmm2, xmm7           ; ABS(dot) * DELTA

   ; we now calculate cross

   movaps xmm3, xmm6
   mulps xmm3, xmm0            ; xmm3 = [delta x * sin, delta y * cos]
   hsubps xmm3, xmm3           ; xmm3 = - cross product

   andps xmm3, xmm8            ; xmm3 = ABS(cross)

   ucomiss xmm3, xmm2
   ja .loop

   ; ABS(cross) <= DELTA * ABS(dot) -> prism is on the ray's path and in front of it

   squared_distance xmm0 ; xmm0 is modified in-place

   ucomiss xmm0, xmm9
   jae .loop

   ; it is the closest prism so far

   movaps xmm9, xmm0
   mov r12, r10

   jmp .loop

.end_loop:
   test r12, r12
   jz .end

   mov edx, [r12]
   mov [rdi + 4*r11], edx   ; store id

   inc r11d

   addss xmm4, [r12 + 12]  ; angle
   insertps xmm0, xmm4, 0b00_00_1110

   sin_cos_taylor
   ; xmm0 = [sin, cos]

   mov rdx, [r12 + 4]
   movq xmm5, rdx        ; xmm5 = [new start x, new start y]
   movaps xmm6, xmm0     ; xmm6 = [new sin, new cos]

   jmp .while_true

.end:
   mov eax, r11d

   pop r13
   pop r12
   ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
