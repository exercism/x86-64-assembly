default rel

section .rodata
points: db 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10

section .text
global score
score:
    cld
    mov rsi, rdi
    lea r8, [points]
    xor r9, r9 ; total
    xor r10, r10
    xor rax, rax
    jmp .read

.update:
    or al, 32 ; force to lower-case
    sub al, 'a'
    cmp al, 26
    jae .read ; jump if not a letter

    mov r10b, byte [r8 + rax] ; look up letter value
    add r9, r10

.read:
    lodsb
    test al, al
    jnz .update

    mov rax, r9
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
