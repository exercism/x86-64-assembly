section .text

%macro _clobber_regs 0
    mov rdi, 0xFFFFFFFFFFFFFFFF
    mov rsi, 0xFFFFFFFFFFFFFFFF
    mov rdx, 0xFFFFFFFFFFFFFFFF
    mov rcx, 0xFFFFFFFFFFFFFFFF
    mov r8, 0xFFFFFFFFFFFFFFFF
    mov r9, 0xFFFFFFFFFFFFFFFF
    mov r10, 0xFFFFFFFFFFFFFFFF
    mov r11, 0xFFFFFFFFFFFFFFFF
%endmacro

global clobber
clobber:
    mov rax, rdi
    _clobber_regs
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
