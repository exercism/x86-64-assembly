default rel

section .rodata
sure: db "Sure.", 0
whoa: db "Whoa, chill out!", 0
calm: db "Calm down, I know what I'm doing!", 0
fine: db "Fine. Be that way!", 0
whatever: db "Whatever.", 0

section .text
global response
response:
    cld
    mov rsi, rdi
    mov rcx, 1
    xor r8, r8 ; nonempty?
    xor r9, r9 ; ends with a question mark?
    xor r10, r10 ; contains upper-case?
    xor r11, r11 ; contains lower-case?
    jmp .read

.parse:
    cmp al, ' '
    jbe .read

    mov r8, rcx ; nonempty

    xor r9, r9
    cmp al, '?' ; ends with a question mark?
    cmove r9, rcx

    sub al, 'A'
    cmp al, 26 ; contains upper-case?
    cmovb r10, rcx

    sub al, 32
    cmp al, 26 ; contains lower-case?
    cmovb r11, rcx

.read:
    lodsb
    test al, al
    jnz .parse

    test r8, r8
    jz .return_fine

    ; Does the input contain upper-case and no lower-case?
    sub r10, r11
    cmp r10, rcx
    je .yell

    test r9, r9
    jz .return_whatever

.return_sure:
    ; This is his response if you ask him a question, such as "How are you?"
    lea rax, [sure]
    ret

.yell:
    test r9, r9
    jnz .return_calm

.return_whoa:
    ; This is his answer if you YELL AT HIM.
    lea rax, [whoa]
    ret

.return_calm:
    ; This is what he says if you yell a question at him.
    lea rax, [calm]
    ret

.return_fine:
    ; This is how he responds to silence.
    lea rax, [fine]
    ret

.return_whatever:
    ; This is what he answers to anything else.
    lea rax, [whatever]
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
