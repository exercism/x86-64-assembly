section .text
global transmit_sequence, decode_message

transmit_sequence:
    ; Provide your implementation here
    ret

decode_message:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
