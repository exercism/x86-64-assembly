section .text

global latest
global personal_best
global personal_top_three

latest:
    ; Provide your implementation here
    ret

personal_best:
    ; Provide your implementation here
    ret

personal_top_three:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
