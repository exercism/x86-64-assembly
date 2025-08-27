section .text

global modifier
global ability
global make_dnd_character

modifier:
    ; Provide your implementation here
    ret

ability:
    ; Provide your implementation here
    ret

make_dnd_character:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
