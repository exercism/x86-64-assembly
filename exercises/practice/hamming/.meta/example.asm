;
; Calculate the Hamming difference between two DNA strands.
;
; Parameters:
;   rdi - strand1
;   rsi - strand2
; Returns:
;   rax - the difference between two DNA strands
;   -1 if lengths differ
;

section .text
global distance
distance:
    pxor xmm0, xmm0
    movdqu xmm1, [rdi]
    movdqu xmm2, [rsi]
    movdqa xmm3, xmm1
    pcmpeqb xmm3, xmm0
    pcmpeqb xmm0, xmm2
    pcmpeqb xmm1, xmm2
    pmovmskb ecx, xmm3
    pmovmskb edx, xmm0
    pmovmskb eax, xmm1
    not eax
    and eax, 0xFFFF
    popcnt eax, eax
    mov r8d, -1
    cmp ecx, edx
    cmovne eax, r8d
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
