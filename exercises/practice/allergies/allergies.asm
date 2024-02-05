section .text
global allergic_to
allergic_to:
    ; Provide your implementation here
    ret

global list
list:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
