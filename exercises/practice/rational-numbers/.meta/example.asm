section .text

global add
global sub
global mul
global div
global rational_absolute
global exprational
global expreal
global reduce

%macro ABS 1
    cmp %1, 0
    jge %%end
    neg %1
%%end:
%endmacro

add:   
    ; rdi - first numerator
    ; rsi - first denominator
    ; rdx - second numerator
    ; rcx - second denominator
    ; rax - result numerator
    ; rdx - result denominator

    mov r8, rsi
    imul r8, rcx ; common multiple

    imul rdi, rcx ; x = numerator1 * denominator2
    imul rdx, rsi ; y = numerator2 * denominator1

    add rdi, rdx ; numerator = x + y
    mov rsi, r8 ; denominator = common multiple

    call reduce ; reduce to eliminate common factors

    ret

sub:
    ; rdi - first numerator
    ; rsi - first denominator
    ; rdx - second numerator
    ; rcx - second denominator
    ; rax - result numerator
    ; rdx - result denominator

    ; subtraction is addition of the negative of the second element

    neg rdx

    call add

    ret

mul:
    ; rdi - first numerator
    ; rsi - first denominator
    ; rdx - second numerator
    ; rcx - second denominator
    ; rax - result numerator
    ; rdx - result denominator

    imul rdi, rdx ; numerator = numerator1 * numerator2
    imul rsi, rcx ; denominator = denominator1 * denominator2

    call reduce ; reduce to eliminate common factors

    ret

div:
    ; rdi - first numerator
    ; rsi - first denominator
    ; rdx - second numerator
    ; rcx - second denominator
    ; rax - result numerator
    ; rdx - result denominator

    ; division is multiplication by the inverse

    xchg rdx, rcx

    call mul 

    ret

rational_absolute:
    ; rdi - first numerator
    ; rsi - first denominator
    ; rax - result numerator
    ; rdx - result denominator

    ; reduces to make sure only numerator is negative
    ; then apply ABS to numerator

    call reduce
    ABS rax

    ret

; helper for calculating x^n, for x integer and n non-negative integer
; the code is roughly equivalent to:
;
; if (n == 0) return 1;
; return n & 1 ? x * (int_pow(x, n >> 1) ^ 2) : (int_pow(x, n >> 1) ^ 2);
;
; which makes the exponentiation O(log2n) 
; the recursion depth is at most 32 for a 32-bit n

int_pow:
    ; rdi - x
    ; rsi - n
    ; return is a int64_t in rax

    cmp rsi, 0
    je .ret_1 ; base case: n == 0 -> return 1

    mov r11, 1
    mov r10, rsi
    and r10, 1 
    cmovnz r11, rdi ; for n odd, the square of the result must
                    ; be multiplied by the base.
                    ; 1 is mempty of multiplication in case of n even

    push r11 ; preserves r11

    shr rsi, 1 ; exponent divided by 2

    call int_pow

    pop r11 ; restores r11
    
    imul rax, rax ; int_pow(x, n >> 1) ^ 2
    imul rax, r11 ; n odd -> (int_pow(x, n >> 1) ^ 2) * x 
                  ; n even -> (int_pow(x, n >> 1) ^ 2) * 1

    ret

.ret_1:
    ; base case

    mov rax, 1
    ret

exprational:
    ; rdi - numerator
    ; rsi - denominator
    ; rdx - n (int64_t)
    ; rax - result numerator
    ; rdx - result denominator

    cmp rdx, 0
    jge .positive ; if n is positive, continue
    ; otherwise exchanges the values of numerator and denominator
    ; and negates n, so that it is now positive

    xchg rdi, rsi
    neg rdx

.positive:
    mov r8, rsi
    mov rsi, rdx

    call int_pow ; numerator ^ n

    mov r9, rax ; saves partial result

    mov rdi, r8
    mov rsi, rdx

    call int_pow ; denominator ^ n

    mov rsi, rax ; denominator = denominator ^ n
    mov rdi, r9 ; numertor = numerator ^ n

    call reduce ; reduce (shouldn't be necessary if input is already reduced)

    ret

; helper for calculating x^n, for x float and n non-negative integer
; the code is roughly equivalent to:
;
; if (n == 0) return 1;
; return n & 1 ? x * (int_pow(x, n >> 1) ^ 2) : (int_pow(x, n >> 1) ^ 2);
;
; which makes the exponentiation O(log2n) 
; the recursion depth is at most 32 for a 32-bit n

float_pow:
    ; xmm1 - x
    ; rsi - n
    ; return is a float in xmm0

    cmp rsi, 0
    je .ret_1 ; base case: n == 0 -> return 1

    mov rax, 1
    cvtsi2ss xmm3, rax
    mov r10, rsi
    and r10, 1 
    jz .even ; for n odd, the square of the result must
             ; be multiplied by the base.
             ; 1 is mempty of multiplication in case of n even

    movss xmm3, xmm1
.even:
    sub rsp, 4
    movss dword [rsp], xmm3 ; preserves base in the stack

    shr rsi, 1 ; exponent divided by 2

    call float_pow

    movss xmm3, dword [rsp]
    add rsp, 4 ; restores base and the stack
    
    mulss xmm0, xmm0 ; float_pow(x, n >> 1) ^ 2
    mulss xmm0, xmm3 ; n odd -> (float_pow(x, n >> 1) ^ 2) * x 
                     ; n even -> (float_pow(x, n >> 1) ^ 2) * 1

    ret

.ret_1:
    ; base case 

    mov rax, 1
    cvtsi2ss xmm0, rax
    ret

; helper for calculating the nth-root of x, for x int64_t and n non-negative integer
;
; the algorithm is a binary search that searchs for a which satisfies:
; a ^ n == x
;
; As a binary search, the time complexity is O(log2n) 

rootN:
    ; calculates the nth-root of an integer
    ; rax - x
    ; rsi - n
    ; return is a float in xmm0

    cvtsi2ss xmm7, rax ; value
    mov r8, 0 
    cvtsi2ss xmm6, r8 ; low = 0

    add r8, rax
    cvtsi2ss xmm8, r8 ; high = x

    mov r8, 2
    cvtsi2ss xmm5, r8 ; divisor = 2

.bsearch:
    ucomiss xmm6, xmm8
    jae .end_search ; while (low < high) 

    movss xmm1, xmm6 ; mid = low
    addss xmm1, xmm8 ; mid = low + high
    divss xmm1, xmm5 ; mid = (low + high) / 2

    push rsi ; preserves exponent for next iteration

    call float_pow ; mid ^ n

    pop rsi ; restores exponent for next iteration

    ucomiss xmm0, xmm7 
    je .end_search ; found mid, so that mid ^ n == x
    jb .increase_low ; mid ^ n < x -> low = mid
    ; otherwise high = mid

    movss xmm8, xmm1 ; high = mid
    jmp .bsearch

.increase_low:
    movss xmm6, xmm1 ; low = mid
    jmp .bsearch

.end_search:
    movss xmm0, xmm1
    ret

expreal:
    ; rdi - x as a int64_t
    ; rsi - numerator
    ; rdx - denominator
    ; return is a float in xmm0

    cmp rsi, 0
    setl r9b ; saves the sign of the exponent

    ABS rsi ; absolute value of the exponent

    call int_pow ; rax = x ^ numerator

    mov rsi, rdx ; n = denominator

    call rootN ; nth-root of (x ^ numerator)

    cmp r9b, 1
    jne .return ; exponent non-negative may return right away
    ; otherwise result must be inverted

    mov rax, 1
    cvtsi2ss xmm3, rax
    divss xmm3, xmm0
    movss xmm0, xmm3 ; xmm0 = 1 / result

.return:
    ret

reduce:
    ; rdi - first numerator
    ; rsi - first denominator
    ; rax - result numerator
    ; rdx - result denominator

    cmp rdi, 0
    sete r8b
    setl r10b

    cmp rsi, 0
    sete r9b
    setl r11b

    or r8b, r9b
    jnz .zero ; in case any of numerator or denominator is 0
              ; return { 0, 1 }

    xor r11b, r10b ; r11b is the sign flag

    ABS rdi
    ABS rsi

    mov r8, rsi ; divisor
    inc r8
.find_common_factors:
    dec r8

    cmp r8, 1
    jle .end ; continue while (divisor > 1)

    mov rax, rdi
    xor rdx, rdx
    div r8

    cmp rdx, 0
    sete r9b ; if set, numerator is divisible by divisor

    mov rax, rsi
    xor rdx, rdx
    div r8

    cmp rdx, 0
    sete r10b ; if set, denominator is divisible by divisor

    and r9b, r10b
    jz .find_common_factors ; if either numerator or denominator is not divisible
                            ; then goes to next iteration
    ; otherwise divisor is a commo factor

    mov rax, rdi
    xor rdx, rdx
    div r8

    mov rdi, rax ; numerator /= divisor

    mov rax, rsi
    xor rdx, rdx
    div r8

    mov rsi, rax ; denominator /= divisor
    mov r8, rsi ; divisor = denominator (will decrease at the start of next iteration)

    jmp .find_common_factors

.end:
    cmp r11b, 1
    jne .return ; non negative number may return right away
    ; otherwise numerator must be negated
    
    neg rdi
.return:
    mov rax, rdi
    mov rdx, rsi
    ret

.zero:
    xor rax, rax
    mov rdx, 1
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
