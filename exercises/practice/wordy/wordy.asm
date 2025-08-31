default rel

SUCCESS equ 0
SYNTAX_ERROR equ 1
UNKNOWN_OPERATION equ 2

section .text
global answer

answer:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
