section .text
global abbreviate
abbreviate:
    mov edx, 1
    xor r8d, r8d
    xor r9d, r9d
.loop:
    movzx eax, byte [rdi]
    inc rdi
    test eax, eax
    jz .exit
    cmp eax, ' '
    setz r8b
    cmp eax, '-'
    setz r9b
    or r8b, r9b
    cmovnz edx, r8d
    jnz .loop
    test edx, edx
    jz .loop
    and eax, ~32
    sub eax, 'A'
    cmp eax, 26
    jae .loop
    xor edx, edx
    add eax, 'A'
    mov [rsi], al
    inc rsi
    jmp .loop
.exit:
    mov [rsi], al
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
