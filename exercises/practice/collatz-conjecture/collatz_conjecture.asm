ERROR_VALUE equ -1

section .text
global steps
steps:
    ; Provide your implementation here
    ; The function has type signature int steps(int number)
    ; The return value and the argument are of type int, which is a 32-bit signed integer type
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
