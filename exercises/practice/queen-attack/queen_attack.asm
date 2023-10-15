section .text
global can_create
can_create:
    ; Provide your implementation here
    ret

global can_attack
can_attack:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
