section .text

global latest
global personal_best
global personal_top_three

latest:
    ; Provide your implementation here
    ; The function has type signature int32_t latest(size_t scores_count, const int32_t *scores)
    ; The return value is of type int32_t, which is a 32-bit signed integer
    ; scores_count is a 64-bit integer, passed in rdi
    ; scores is the address to a read-only sequence of 32-bit signed integers, passed in rsi
    ;
    ; The function should return the last element in the input array
    ; 32-bit integer values are returned in eax
    ret

personal_best:
    ; Provide your implementation here
    ; The function has type signature int32_t personal_best(size_t scores_count, const int32_t *scores)
    ; The return value is of type int32_t, which is a 32-bit signed integer
    ; scores_count is a 64-bit integer, passed in rdi
    ; scores is the address to a read-only sequence of 32-bit signed integers, passed in rsi
    ;
    ; The function should return the greatest element in the input array
    ; 32-bit integer values are returned in eax
    ret

personal_top_three:
    ; Provide your implementation here
    ; The function has type signature size_t personal_top_three(int32_t *buffer, const int32_t *scores, size_t scores_count)
    ; The return value is of type size_t, which is a 64-bit unsigned integer
    ; buffer is the address to a writable sequence of 32-bit signed integers, passed in rdi
    ; scores is the address to a read-only sequence of 32-bit signed integers, passed in rsi
    ; scores_count is a 64-bit integer, passed in rdx
    ;
    ; The function should write in the output buffer up to the three greatest elements in the input array
    ; And return the size of this buffer.
    ; 64-bit integer values are returned in rax
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
