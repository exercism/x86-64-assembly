section .rodata
align 16
factor: dq 0.5, 0.5

section .text

global sum_yields
sum_yields:
    movaps xmm0, oword [rdi]
    addps  xmm0, oword [rsi]
    movaps oword [rdx], xmm0
    ret

global scaled_deviation
scaled_deviation:
    movapd xmm1, oword [rdi]
    movupd xmm2, oword [rsi]
    subpd  xmm1, xmm2
    movupd xmm0, oword [rdx]
    mulpd  xmm0, xmm1
    movupd oword [rcx], xmm0
    ret

global calibrate_batch
calibrate_batch:
    movapd   xmm0, oword [rsi]        ; reference
    movapd   xmm1, oword [rdx]        ; offset
    movapd   xmm2, oword [rel factor] ; factor

    cvtps2pd xmm3, qword [rdi]        ; first row
    cvtps2pd xmm4, qword [rdi + 8]    ; second row

    subpd    xmm3, xmm1
    subpd    xmm4, xmm1

    movapd   xmm1, xmm0
    divpd    xmm0, xmm3
    divpd    xmm1, xmm4

    mulpd    xmm0, xmm2
    mulpd    xmm1, xmm2

    movapd   oword [rcx]     , xmm0
    movapd   oword [rcx + 16], xmm1
    ret

global normalize_scores
normalize_scores:
    xor eax, eax
    movapd xmm1, oword [rdx]
.loop:
    movapd xmm0, oword [rdi + 8*rax]
    mulpd  xmm0, oword [rsi + 8*rax]
    divpd  xmm0, xmm1
    movapd oword [rdi + 8*rax], xmm0
    add rax, 2
    cmp rax, rcx
    jb .loop
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
