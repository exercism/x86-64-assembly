section .text
global square_of_sum
square_of_sum:
    ; Provide your implementation here
    ret

global sum_of_squares
sum_of_squares:
    ; Provide your implementation here
    ret

global difference_of_squares
difference_of_squares:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
