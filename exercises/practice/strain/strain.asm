section .text
global keep
keep:
    ; Provide your implementation here
    ret

global discard
discard:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
