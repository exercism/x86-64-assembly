section .text
global to_rna
to_rna:
    ; Provide your implementation here
    ; The function has type signature void to_rna(const char *strand, char *buffer)
    ; It has no return value
    ; The first argument is the address to a read-only sequence of bytes stored in memory
    ; The second argument is the address to a writable sequence of bytes stored in memory
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
