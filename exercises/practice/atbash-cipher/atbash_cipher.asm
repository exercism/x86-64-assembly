section .text
global encode, decode

encode:
    ; Provide your implementation here
    ret

decode:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
