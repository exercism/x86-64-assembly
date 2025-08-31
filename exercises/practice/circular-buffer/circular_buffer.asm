default rel

section .bss

section .text

global create_buffer
global read_buffer
global write_buffer
global clear_buffer
global overwrite_buffer
global delete_buffer

create_buffer:
    ; Provide your implementation here
    ret

read_buffer:
    ; Provide your implementation here
    ret

write_buffer:
    ; Provide your implementation here
    ret

clear_buffer:
    ; Provide your implementation here
    ret

overwrite_buffer:
    ; Provide your implementation here
    ret

delete_buffer:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
