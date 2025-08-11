INVALID_CHARACTER equ -1
NEGATIVE_SPAN equ -2
INSUFFICIENT_DIGITS equ -3

section .text
global largest_product
largest_product:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif


