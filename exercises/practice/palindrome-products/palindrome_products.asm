section .text
global largest
global smallest

largest:
    ; Provide your implementation here
    ret

smallest:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
