section .rodata
align 16
reorder: db 2, 1, 0, 3, 6, 5, 4, 7, 10, 9, 8, 11, 14, 13, 12, 15

section .text

global to_display_order
to_display_order:
    movdqa xmm1, [rel reorder]
    shl rdx, 4
    xor ecx, ecx
.loop:
    movdqa xmm0, [rsi + rcx]
    pshufb xmm0, xmm1
    movdqa [rdi + rcx], xmm0
    add rcx, 16
    cmp rcx, rdx
    jb .loop

    ret

global fill_region
fill_region:
    pinsrd xmm0, [rsi], 0
    pshufd xmm0, xmm0, 0b00_00_00_00

    shl rdx, 4
    xor ecx, ecx
.loop:
    movdqa [rdi + rcx], xmm0
    add rcx, 16
    cmp rcx, rdx
    jb .loop

    ret

global weave_scanlines
weave_scanlines:
    movdqa xmm0, [rsi]
    movdqa xmm1, [rdx]
    movdqa xmm2, xmm0
    punpcklbw xmm0, xmm1
    punpckhbw xmm2, xmm1
    movdqa [rdi], xmm0
    movdqa [rdi + 16], xmm2
    ret

global pack_samples
pack_samples:
    movdqa xmm0, [rsi]
    packuswb xmm0, [rdx]
    movdqa [rdi], xmm0
    ret

global split_coordinates
split_coordinates:
    movdqa xmm0, [rdx]
    movdqa xmm1, [rcx]
    movdqa xmm2, xmm0
    shufps xmm0, xmm1, 0b10_00_10_00
    shufps xmm2, xmm1, 0b11_01_11_01
    movdqa [rdi], xmm0
    movdqa [rsi], xmm2
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
