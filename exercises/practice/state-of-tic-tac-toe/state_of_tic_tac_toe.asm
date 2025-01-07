ONGOING equ 0
DRAW equ 1
WIN equ 2
INVALID equ 3

section .text
global gamestate
gamestate:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
