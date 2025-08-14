UNEQUAL equ 0
EQUAL equ 1
SUBLIST equ 2
SUPERLIST equ 3

section .text
global sublist

sublist:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc nowrite progbits
%endif


