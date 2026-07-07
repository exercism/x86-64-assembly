section .text

%macro _clobber_regs 0
    mov rax, 0xFFFFFFFFFFFFFFFF
    mov rdi, 0xFFFFFFFFFFFFFFFF
    mov rsi, 0xFFFFFFFFFFFFFFFF
    mov rdx, 0xFFFFFFFFFFFFFFFF
    mov rcx, 0xFFFFFFFFFFFFFFFF
    mov r8, 0xFFFFFFFFFFFFFFFF
    mov r9, 0xFFFFFFFFFFFFFFFF
    mov r10, 0xFFFFFFFFFFFFFFFF
    mov r11, 0xFFFFFFFFFFFFFFFF

    pxor xmm0, xmm0
    pcmpeqb xmm0, xmm0
    %assign _i 1
    %rep 15
        movdqa xmm %+ _i, xmm0
        %assign _i _i + 1
    %endrep
    %undef _i
%endmacro

global clobber
clobber:
    sub rsp, 8
    movdqa xmm0, [rsp]
    _clobber_regs
    add rsp, 8
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
