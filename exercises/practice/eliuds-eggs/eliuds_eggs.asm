section .text
global egg_count
egg_count:
    ; Provide your implementation here
    ; The function has type signature int egg_count(int number)
    ; The return value and the argument are of type int, which is a 32-bit signed integer
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
