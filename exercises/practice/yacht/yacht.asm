CHOICE equ 0
ONES equ 1
TWOS equ 2
THREES equ 3
FOURS equ 4
FIVES equ 5
SIXES equ 6
LITTLE_STRAIGHT equ 7
BIG_STRAIGHT equ 8
FULL_HOUSE equ 9
FOUR_OF_A_KIND equ 10
YACHT equ 11

section .text
global score

score:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
