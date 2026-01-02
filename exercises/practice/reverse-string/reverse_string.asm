section .text
global reverse
reverse:
    ; Provide your implementation here
    ; The function has type signature void reverse(char *str)
    ; It has no return value
    ; The argument is of type char*, which is the address of a writable NUL-terminated sequence of bytes stored in memory
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
