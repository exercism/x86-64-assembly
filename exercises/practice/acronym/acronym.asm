section .text
global abbreviate
abbreviate:
    ; Provide your implementation here
    ; rdi - char * in - read
    ; rsi - char * out - write result, assume length 0x100
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif