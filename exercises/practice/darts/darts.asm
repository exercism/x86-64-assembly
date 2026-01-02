section .text
global score
score:
    ; Provide your implementation here
    ; The function has type signature uint8_t score(double x, double y)
    ; The return value is of type uint8_t, which is a 8-bit unsigned integer
    ; Both arguments are of type double, which is a 64-bit floating-point
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
