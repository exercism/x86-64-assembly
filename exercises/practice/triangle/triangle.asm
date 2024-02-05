section .text

global is_equilateral
is_equilateral:
    ; Provide your implementation here
    ret

global is_isosceles
is_isosceles:
    ; Provide your implementation here
    ret

global is_scalene
is_scalene:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif