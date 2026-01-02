default rel

section .text
global score
score:
    ; Provide your implementation here
    ; The function has type signature int score(const char *score)
    ; The return value is of type int, which is a 32-bit signed integer
    ; The argument is of type const char*, which is the address to a read-only NUL-terminated string
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
