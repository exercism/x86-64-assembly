section .text

global create
global add_minutes
global subtract_minutes
global equal

create:
    ; Provide your implementation here
    ret

add_minutes:
    ; Provide your implementation here
    ret

subtract_minutes:
    ; Provide your implementation here
    ret

equal:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
