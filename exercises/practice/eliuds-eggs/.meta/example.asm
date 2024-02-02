;
; Counts 1 bits in number
;
; Parameter:
;   rdi - number
; Returns:
;   rax - count of 1 bits
;
section .text
global egg_count
egg_count:
                             ; rdx - least significant 1 bit in rdi
                             ; rax - current count
    xor rax, rax             ; Current count is 0
    test rdi, rdi
    jz .report

.remove_one:
    xor rdx, rdx
    sub rdx, rdi             ; -rdi
    and rdx, rdi             ; least significant 1 bit in rdi
    inc rax
    xor rdi, rdx             ; clear least significant 1
    jnz .remove_one

.report:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
