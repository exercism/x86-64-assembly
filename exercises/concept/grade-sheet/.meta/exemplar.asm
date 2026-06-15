section .rodata
align 16
threshold: dd 50.0, 50.0, 50.0, 50.0
rank_one: dd 1, 1, 1, 1
rank_two: dd 2, 2, 2, 2
rank_three: dd 3, 3, 3, 3

section .text

global flag_above_threshold
flag_above_threshold:
    movaps xmm0, oword [rsi]
    cmpnleps xmm0, oword [rdx]
    movaps oword [rdi], xmm0
    ret

global flag_perfect
flag_perfect:
    movaps xmm0, oword [rsi]
    cmpeqps xmm0, oword [rdx]
    movaps oword [rdi], xmm0
    ret

global assign_ranks
assign_ranks:
    movaps xmm0, oword [rsi]
    movaps xmm1, xmm0
    cmpnleps xmm0, oword [rel threshold]
    movaps xmm2, oword [rel rank_one]
    blendvps xmm2, oword [rel rank_two]
    movaps xmm0, xmm1
    cmpeqps xmm0, oword [rdx]
    blendvps xmm2, oword [rel rank_three]
    movaps oword [rdi], xmm2
    ret

global count_failures
count_failures:
    xor eax, eax
    shl rsi, 4
    lea rdi, [rdi + rsi]
    neg rsi
    movdqa xmm1, oword [rdx]
.loop:
    movdqa xmm0, xmm1
    pcmpgtd xmm0, oword [rdi + rsi]
    movmskps ecx, xmm0
    popcnt ecx, ecx
    add eax, ecx
    add rsi, 16
    jnz .loop

    ret

global all_passed
all_passed:
    shl rsi, 4
    lea rdi, [rdi + rsi]
    neg rsi
    pxor xmm0, xmm0
.loop:
    movdqa xmm1, oword [rdi + rsi]
    por xmm0, xmm1
    add rsi, 16
    jnz .loop

    xor eax, eax
    ptest xmm0, xmm0
    setz al
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
