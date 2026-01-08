section .text
global two_fer
two_fer:
    ; Provide your implementation here
    ; The function has type signature void two_fer(const char *name, char *buffer)
    ; It has no return value
    ; The first argument is of type const char*, which is the address of a read-only NUL-terminated sequence of bytes stored in memory that represents the name of a person
    ; If no name is passed, this address has a value of 0
    ; The second argument is of type char*, which is the address of a writable sequence of bytes stored in memory
    ; The resulting string should be NUL-terminated and stored at the location pointed to by the address provided in the second argument.
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
