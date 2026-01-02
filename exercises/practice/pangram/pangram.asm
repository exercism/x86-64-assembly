section .text
global is_pangram
is_pangram:
    ; Provide your implementation here
    ; The function has type signature int is_pangram(const char *str)
    ; The return value is of type int, which is a 32-bit signed integer
    ; The return value should be set to zero if false and non-zero if true
    ; The argument is of type const char*, which is the address of a read-only NUL-terminated sequence of bytes stored in memory
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
