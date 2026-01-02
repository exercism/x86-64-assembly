section .text
global distance
distance:
    ; Provide your implementation here
    ; The function has type signature int distance(const char *strand1, const char *strand2)
    ; The return value is of type int, which is a 32-bit signed integer
    ; Each argument is the address of a read-only NUL-terminated sequence of bytes stored in memory
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
