default rel

section .rodata

reciprocal: db 0,1,0,9,0,21,0,15,0,3,0,19,0,0,0,7,0,23,0,11,0,5,0,17,0,25

section .text
global encode, decode

;   rdi - buffer
;   rsi - string
;   rdx - a
;   rcx - b

;   r8 - chunk size
;   r9 - 26
;   r10 - effective a
;   r11 - effective b
;   r12 - remainder of chunk
;   r13 - digit (0..9) or letter (0..25)
decode:
    xor r8, r8 ; no chunking
    jmp process

encode:
    mov r8, 5

process:
    cld ; each lodsb/stosb will increment rsi/rdi
    mov r9, 26
    cmp rdx, r9
    jae .reject ; out of range for reciprocal table

    lea r11, [reciprocal]
    xor r10, r10
    mov r10b, byte [r11 + rdx]
    test r10, r10
    jz .reject ; a is not coprime to m

    push r12
    push r13
    xor r13, r13
    test r8, r8
    jz .invert

    mov r10, rdx ; a
    mov r11, rcx ; b
    mov r12, r8 ; chunk size
    jmp .read

.invert:
    xor rax, rax

.shift:
    add rax, r9
    cmp rax, rcx
    jb .shift

    sub rax, rcx ; -b, shifted by 26 until non-negative
    mul r10 ; multiply by effective a
    mov r11, rax ; effective b
    mov r12, -1 ; no chunking
    jmp .read

.classify:
    mov r13b, al
    sub r13b, '0'
    cmp r13b, 10
    jb .write ; jump if we have a digit

    mov r13b, al
    or r13b, 32 ; force to lower-case
    sub r13b, 'a'
    cmp r13b, r9b
    jae .read ; jump if we do not have a letter

    mov rax, r10
    mul r13
    add rax, r11 ; effective a * letter index + effective b
    xor rdx, rdx
    div r9
    mov rax, rdx ; remainder when divided by 26
    add rax, 'a'

.write:
    test r12, r12
    jnz .write_letter_or_digit

    mov r12, r8 ; start a new chunk
    mov r13b, al
    mov al, ' '
    stosb
    mov al, r13b

.write_letter_or_digit:
    stosb
    dec r12

.read:
    lodsb
    test al, al
    jnz .classify

    pop r13
    pop r12
    xor rax, rax
    stosb
    ret

.reject:
    mov byte [rdi], 0
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
