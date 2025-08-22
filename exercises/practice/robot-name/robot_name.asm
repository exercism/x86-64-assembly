section .text

global create_name
global reset_name
global release_names

create_name:
    ; Provide your implementation here
    ret

reset_name:
    ; Provide your implementation here
    ret

release_names:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
