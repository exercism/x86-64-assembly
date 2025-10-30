BAD_BASE equ -1
BAD_DIGIT equ -2

section .text
global rebase

rebase:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
