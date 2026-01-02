section .text
global square_root
square_root:
    ; Provide your implementation here
    ; The function has type signature int square_root(int radicand)
    ; The return value and the argument are of type int, which is a 32-bit signed integer
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
