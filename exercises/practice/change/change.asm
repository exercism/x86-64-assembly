NEGATIVE_TARGET equ -1
UNREACHABLE_TARGET equ -2

section .text
global find_fewest_coins

find_fewest_coins:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
