section .text
global create
global move

create:
    ; Provide your implementation here
    ret

move:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
