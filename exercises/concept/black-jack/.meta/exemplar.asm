C2 equ 2
C3 equ 3
C4 equ 4
C5 equ 5
C6 equ 6
C7 equ 7
C8 equ 8
C9 equ 9
C10 equ 10
CJ equ 11
CQ equ 12
CK equ 13
CA equ 14

TRUE equ 1
FALSE equ 2

section .text

global value_of_card
global higher_card
global value_of_ace
global is_blackjack
global can_split_pairs
global can_double_down

value_of_card:
    ret

higher_card:
    ret

value_of_ace:
    ret

is_blackjack:
    ret

can_split_pairs:
    ret

can_double_down:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
