EMPTY_RESULT equ 0
INVALID_INPUT equ -1

; Both functions have a similar and straightforward implementation:
;
; 1 - They iterate over all numbers from current min to max in an outer loop;
; 2 - In each iteration of the outer loop, they iterate over all numbers
; from current min to max, again;
; 3 - Both numbers are multiplied and checked for being palindromic;
; 4.1 - If they are, the largest function checks if the product is larger than the current
; accumulator. If it is, the new product is stored, the buffer is reset and the new factors
; are stored. If the product is equal, the new factors are stored after the current ones;
; 4.2 - The smallest function does the same, but checking if the product is lesser than
; current accumulator;
; 5 - Since both loops (outer and inner) go in increasing order of factors, then the factors
; are already stored in sorted order, as expected by the tests;
; 6 - At the end, the accumulator is passed to RAX. In the case of largest function,
; starting value for the accumulator is EMPTY_RESULT, so nothing else needs to be done. And
; in the case of smallest function, the starting value is MAX_UINT64, so RAX is reset to
; EMPTY_RESULT and a CMOV is used to move the accumulator if lesser than MAX_UINT64

section .text
global largest
global smallest


; r10 = 0xCCCCCCCCCCCCCCCD = ⌈2^67 / 10⌉
; To divide by 10: multiply by r10 and shift rdx right by 3
; https://lemire.me/blog/2019/02/08/faster-remainders-when-the-divisor-is-a-constant-beating-compilers-and-libdivide/

; result in flag: ZF=1 → palindrome, ZF=0 → not
%macro is_palindrome 1
    mov r9, %1 ; leading digits
    xor rcx, rcx ; trailing digits, reversed

    ; check whether leading is a multiple of 10
    mov rax, r9
    mul r10
    shr rdx, 3 ; rdx = leading / 10
    lea rax, [rdx + rdx*4]
    add rax, rax ; rax = 10 * (leading / 10)
    cmp r9, rax
    jne %%absorb ; not a multiple of 10 → first iteration

    test r9, r9 ; ZF=1 iff leading == 0 (palindrome); else non-zero multiple of 10
    jmp %%done

%%step:
    mov rax, r9
    mul r10
    shr rdx, 3 ; rdx = leading / 10
    lea rax, [rdx + rdx*4]
    add rax, rax ; rax = 10 * (leading / 10)

%%absorb:
    sub r9, rax ; r9 = leading % 10
    lea rcx, [rcx + rcx*4]
    add rcx, rcx ; rcx = 10 * trailing
    add rcx, r9 ; trailing := trailing * 10 + leading % 10
    mov r9, rdx ; leading := leading / 10

%%check:
    cmp r9, rcx
    ja %%step ; leading > trailing ?
    je %%done ; leading == trailing ? (even-length)

    mov rax, rcx
    mul r10
    shr rdx, 3 ; rdx = trailing / 10
    cmp r9, rdx ; ZF = (leading == trailing / 10), odd-length
%%done:
%endmacro


largest:
    ; RDI - pointer to a struct of a uint64_t and a buffer of 20 arrays of 2 uint64_t
    ; RSI - min value, as a uint64_t
    ; RDX - max value, as a uint64_t
    ; return is the result (largest palindromic product) in RAX, as a int64_t

    cmp rsi, rdx
    jg invalid

    mov r10, 0xCCCCCCCCCCCCCCCD
    push rbp
    mov rbp, rsp
    sub rsp, 32

    mov qword [rbp - 8], rdi
    mov qword [rbp - 16], rsi
    mov qword [rbp - 24], rdx
    mov r11, EMPTY_RESULT

.outer:
    mov qword [rbp - 32], rsi
.inner:
    mov rsi, qword [rbp - 32]
    cmp rsi, qword [rbp - 24]
    jg .end_inner

    inc qword [rbp - 32]
    imul rsi, qword [rbp - 16]

    is_palindrome rsi
    jne .inner

.add_to_buffer:
    cmp rsi, r11
    jl .inner
    je .add

    mov r11, rsi
    mov rdi, qword [rbp - 8]
    mov qword [rdi], 0
.add:
    mov rdi, qword [rbp - 8]
    mov rax, qword [rdi]
    inc qword [rdi]

    add rdi, 8
    shl rax, 4
    add rdi, rax

    mov rax, qword [rbp - 16]
    stosq

    mov rax, qword [rbp - 32]
    dec rax
    stosq

    jmp .inner

.end_inner:
    inc qword [rbp - 16]
    mov rsi, qword [rbp - 16]

    cmp rsi, qword [rbp - 24]
    jle .outer

    mov rax, r11

    mov rsp, rbp
    pop rbp
    ret

smallest:
    ; RDI - pointer to a struct of a uint64_t and a buffer of 20 arrays of 2 uint64_t
    ; RSI - min value, as a uint64_t
    ; RDX - max value, as a uint64_t
    ; return is the result (smallest palindromic product) in RAX, as a int64_t

    cmp rsi, rdx
    jg invalid

    mov r10, 0xCCCCCCCCCCCCCCCD
    push rbp
    mov rbp, rsp
    sub rsp, 32

    mov qword [rbp - 8], rdi
    mov qword [rbp - 16], rsi
    mov qword [rbp - 24], rdx
    mov r11, -1

.outer:
    mov qword [rbp - 32], rsi
.inner:
    mov rsi, qword [rbp - 32]
    cmp rsi, qword [rbp - 24]
    jg .end_inner

    inc qword [rbp - 32]
    imul rsi, qword [rbp - 16]

    cmp rsi, r11
    ja .end_inner
    je .add

    is_palindrome rsi
    jne .inner

.add_to_buffer:
    mov r11, rsi
    mov rdi, qword [rbp - 8]
    mov qword [rdi], 0
.add:
    mov rdi, qword [rbp - 8]
    mov rax, qword [rdi]
    inc qword [rdi]

    add rdi, 8
    shl rax, 4
    add rdi, rax

    mov rax, qword [rbp - 16]
    stosq

    mov rax, qword [rbp - 32]
    dec rax
    stosq

    jmp .inner

.end_inner:
    inc qword [rbp - 16]
    mov rsi, qword [rbp - 16]

    cmp rsi, qword [rbp - 24]
    jle .outer

    mov rax, EMPTY_RESULT
    cmp r11, -1
    cmovne rax, r11

    mov rsp, rbp
    pop rbp
    ret

invalid:
    mov rax, INVALID_INPUT
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
