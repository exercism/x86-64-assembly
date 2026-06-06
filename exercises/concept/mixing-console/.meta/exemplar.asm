section .text

global mix_tracks
mix_tracks:
    movdqa xmm0, oword [rsi]
    paddsw xmm0, oword [rdx]
    movdqa oword [rdi], xmm0
    ret

global remove_bleed
remove_bleed:
    movdqa xmm0, oword [rsi]
    movdqu xmm1, oword [rdx]
    psubsw xmm0, xmm1
    movdqu oword [rdi], xmm0
    ret

global combine_meters
combine_meters:
    movdqa xmm0, oword [rsi]
    paddusb xmm0, oword [rdx]
    movdqa oword [rdi], xmm0
    ret

global apply_fade
apply_fade:
    xor eax, eax
.loop:
    movdqa xmm0, oword [rsi + 2*rax]
    pmulhw xmm0, oword [rdx + 2*rax]
    movdqa oword [rdi + 2*rax], xmm0
    add rax, 8
    cmp rax, rcx
    jb .loop
    ret

global attenuate_track
attenuate_track:
    xor eax, eax
    movdqa xmm1, oword [rdx]
    cvtdq2ps xmm1, xmm1
.loop:
    pmovsxwd xmm0, qword [rsi + 2*rax]
    cvtdq2ps xmm0, xmm0
    divps xmm0, xmm1
    cvttps2dq xmm0, xmm0
    movdqa oword [rdi + 4*rax], xmm0
    add rax, 4
    cmp rax, rcx
    jb .loop
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
