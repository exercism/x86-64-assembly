EMPTY_RESULT equ 0
INVALID_INPUT equ -1

; largest iterates outer from max down to min.
; For each outer, inner iterates from outer down to min.

; smallest iterates outer from min up to max.
; For each outer, inner iterates from outer up to max.

; Inner exits early once the running product can no longer beat the best palindrome found.

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

    push r13
    push r14
    push r15

    mov r8, rdi ; pointer to struct
    mov r10, 0xCCCCCCCCCCCCCCCD ; see is_palindrome
    xor r11, r11 ; best product
    mov r13, rsi ; min value
    mov r14, rdx ; index for outer loop

.outer:
    mov r15, r14 ; upcoming index for inner loop

.inner:
    mov rsi, r15
    cmp rsi, r13
    jl .end_inner

    dec r15 ; upcoming index for inner loop
    imul rsi, r14 ; product

    cmp rsi, r11
    jb .end_inner
    je .add

    is_palindrome rsi
    jne .inner

    mov r11, rsi ; new best product
    mov rdi, r8
    xor rax, rax ; initial count 0
    stosq
.add:
    inc qword [r8]

    mov rax, r15
    inc rax ; index for inner loop
    stosq

    mov rax, r14 ; index for outer loop
    stosq

    jmp .inner

.end_inner:
    dec r14
    cmp r14, r13
    jge .outer

    mov rax, r11

    pop r15
    pop r14
    pop r13
    ret


smallest:
    ; RDI - pointer to a struct of a uint64_t and a buffer of 20 arrays of 2 uint64_t
    ; RSI - min value, as a uint64_t
    ; RDX - max value, as a uint64_t
    ; return is the result (smallest palindromic product) in RAX, as a int64_t

    cmp rsi, rdx
    jg invalid

    push r13
    push r14
    push r15

    mov r8, rdi ; pointer to struct
    mov r10, 0xCCCCCCCCCCCCCCCD ; see is_palindrome
    mov r11, -1 ; best product
    mov r13, rdx ; max value
    mov r14, rsi ; index for outer loop

.outer:
    mov r15, r14 ; upcoming index for inner loop

.inner:
    mov rsi, r15
    cmp rsi, r13
    jg .end_inner

    inc r15 ; upcoming index for inner loop
    imul rsi, r14 ; product

    cmp rsi, r11
    ja .end_inner
    je .add

    is_palindrome rsi
    jne .inner

    mov r11, rsi ; new best product
    mov rdi, r8
    xor rax, rax ; initial count 0
    stosq
.add:
    inc qword [r8]

    mov rax, r14 ; index for outer loop
    stosq

    mov rax, r15
    dec rax ; index for inner loop
    stosq

    jmp .inner

.end_inner:
    inc r14
    cmp r14, r13
    jle .outer

    mov rax, EMPTY_RESULT
    cmp r11, -1
    cmovne rax, r11

    pop r15
    pop r14
    pop r13
    ret


invalid:
    mov rax, INVALID_INPUT
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
