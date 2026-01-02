section .text
global square
square:
    ; Provide your implementation here
    ; The function has type signature uint64_t square(int64_t number)
    ; The return value is of type uint64_t, which is an unsigned 64-bit integer
    ; The argument is of type int64_t, which is a signed 64-bit integer
    ret

global total
total:
    ; Provide your implementation here
    ; The function has type signature uint64_t total(void)
    ; The return value is of type uint64_t, which is an unsigned 64-bit integer
    ; It has no argument
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
