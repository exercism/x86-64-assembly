section .text

global latest
global personal_best
global personal_top_three

; scores_count is a 32-bit integer, passed in rdi
; scores is an array of 32-bit constant integers, passed in rsi
;
; The function should return the last element in the input array
; Integer values are returned in rax

latest:
    ; Provide your implementation here
    ret

; scores_count is a 32-bit integer, passed in rdi
; scores is an array of 32-bit constant integers, passed in rsi
;
; The function should return the greatest element in the input array
; Integer values are returned in rax

personal_best:
    ; Provide your implementation here
    ret

; buffer is an array of 32-bit integers, passed in rdi
; scores is an array of 32-bit constant integers, passed in rsi
; scores_count is a 32-bit integer, passed in rdx
;
; The function should write in the output buffer up to the three greatest elements in the input array
; And return the size of this buffer.
; Integer values are returned in rax

personal_top_three:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
