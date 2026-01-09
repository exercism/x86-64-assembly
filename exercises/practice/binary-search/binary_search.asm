section .text
global find
find:
    ; Provide your implementation here
    ; This function has type signature int find(int *array, int size, int value)
    ; The first argument is the address to a memory location where an array of 32-bit signed integers is stored
    ; The second and third arguments are of type int, which is a signed 32-bit integer
    ; The function should return the index of the element in the array as a signed 32-bit integer, or -1 if the element is not in the array
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
