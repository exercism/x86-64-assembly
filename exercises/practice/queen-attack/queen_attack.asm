section .text
global can_create
can_create:
    ; Provide your implementation here
    ; The function has type signature int can_create(int row, int column)
    ; Both arguments and the return value are of int type, which is a 32-bit signed integer
    ; The return value should be set to zero if false and non-zero if true
    ret

global can_attack
can_attack:
    ; Provide your implementation here
    ; The function has type signature int can_attack(int white_row, int white_column, int black_row, int black_column)
    ; All arguments and the return value are of int type, which is a 32-bit signed integer
    ; The return value should be set to zero if false and non-zero if true
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
