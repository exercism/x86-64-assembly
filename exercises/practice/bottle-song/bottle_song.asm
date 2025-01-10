default rel

section .data

section .text
global recite
recite:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
