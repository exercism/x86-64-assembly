section .rodata

ABS_MSK equ (1 << 31) - 1
EXP_MSK equ 0xFF << 23

align 16
abs_mask: dd ABS_MSK, ABS_MSK, ABS_MSK, ABS_MSK
exp_mask: dd EXP_MSK, EXP_MSK, EXP_MSK, EXP_MSK
bias_f32: dd 127, 127, 127, 127

section .text

global rectify_trace
rectify_trace:
    movaps xmm0, [rsi]
    andps  xmm0, [rel abs_mask]
    movaps [rdi], xmm0
    ret

global reading_scale
reading_scale:
    movaps xmm0, [rsi]
    andps xmm0, [rel exp_mask]
    psrld xmm0, 23
    psubd xmm0, [rel bias_f32]
    movdqa [rdi], xmm0
    ret

global coarsen_displacements
coarsen_displacements:
    movq xmm0, rdx
    movdqa xmm1, [rsi]
    psrad xmm1, xmm0
    movdqa [rdi], xmm1
    ret

global gate_channels
gate_channels:
    movdqa xmm0, [rsi]
    por xmm0, [rdx]
    movdqa xmm1, [rcx]
    pandn xmm1, xmm0
    movdqa [rdi], xmm1
    ret

global toggle_calibration
toggle_calibration:
    movdqa xmm0, [rsi]
    movdqa xmm1, [rcx]
    pandn  xmm1, [rdx]
    pxor xmm0, xmm1
    movdqa [rdi], xmm0
    ret

global amplify_trace
amplify_trace:
    movdqa xmm0, [rdx]
    pslld xmm0, 23
    paddd xmm0, [rsi]
    movaps [rdi], xmm0
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
