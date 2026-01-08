section .text
global age
age:
    ; Provide your implementation here
    ; The function has type signature float age(enum planet planet, int seconds)
    ; The return value is of type float, which is a 32-bit floating-point number
    ; The first argument is of type enum planet, which is a 32-bit signed integer that represents a planet:
    ; 0 -> Mercury
    ; 1 -> Venus
    ; 2 -> Earth
    ; 3 -> Mars
    ; 4 -> Jupiter
    ; 5 -> Saturn
    ; 6 -> Uranus
    ; 7 -> Neptune
    ; The second argument is of type int, which is a 32-bit signed integer
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
