section .text
global square_of_sum
square_of_sum:
    ; Provide your implementation here
    ; The function has signature int square_of_sum(int number)
    ; The return value and the argument are of type int, which is a 32-bit signed integer
    ret

global sum_of_squares
sum_of_squares:
    ; Provide your implementation here
    ; The function has signature int sum_of_squares(int number)
    ; The return value and the argument are of type int, which is a 32-bit signed integer
    ret

global difference_of_squares
difference_of_squares:
    ; Provide your implementation here
    ; The function has signature int difference_of_squares(int number)
    ; The return value and the argument are of type int, which is a 32-bit signed integer
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
