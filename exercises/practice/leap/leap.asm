section .text
global leap_year
leap_year:
    ; Provide your implementation here
    ; The function has type signature int leap_year(int year)
    ; The return value and the argument are of type int, which is a 32-bit signed integer
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
