section .text
global encode
global decode

%macro traverse 4
    cmp rsi, 1
    je %%end                  ; 1 rail, returns right away

    sub rsp, 64               ; prologue

    ; we are stuck in SSE land, due to CI restrictions (macOS)
    ; on modern CPUs, a ZMM register could hold all 64 bytes of the string
    ; no loop would be needed
    pxor xmm0, xmm0
    mov rdx, -16
%%find_length:
    add rdx, 16
    pcmpistri xmm0, [rdi + rdx], 0b00_00_10_00
    jnz %%find_length
    add rcx, rdx              ; string length

    lea r10, [rsi + rsi - 2]  ; period
    xor r8d, r8d              ; rail
    xor edx, edx
%%loop:
    cmp r8, rsi
    jae %%end_loop

    mov r9, r8
    mov r11, r10
    sub r11, r8

    test r8, r8
    jz %%single                ; first rail has only 1 point of repetition

    cmp r8, r11
    jz %%single                ; last rail has only 1 point of repetition

    ; all other rails have 2 points of repetition
%%pair:
    cmp r9, rcx
    jae %%next

    movzx eax, byte [rdi + %1]
    mov byte [rsp + %2], al

    inc rdx

    cmp r11, rcx
    jae %%next

    movzx eax, byte [rdi + %3]
    mov byte [rsp + %4], al

    inc rdx

    add r9, r10                ; first point cycle
    add r11, r10               ; second point cycle
    jmp %%pair

%%single:
    cmp r9, rcx
    jae %%next

    movzx eax, byte [rdi + %1]
    mov byte [rsp + %2], al

    inc rdx

    add r9, r10                ; single point cycle
    jmp %%single

%%next:
    inc r8                     ; next rail
    jmp %%loop

%%end_loop:
    ; encoded/decoded string is on stack
    ; copies back to destination buffer
    movdqu xmm0, [rsp]
    movdqu xmm1, [rsp + 16]
    movdqu xmm2, [rsp + 32]
    movdqu xmm3, [rsp + 48]
    movdqu [rdi], xmm0
    movdqu [rdi + 16], xmm1
    movdqu [rdi + 32], xmm2
    movdqu [rdi + 48], xmm3
    mov byte [rdi + rcx], 0   ; NULL

    add rsp, 64               ; epilogue
%%end:
%endmacro

; extern void encode(char message[], size_t rails);
; message is modified in-place
encode:
    traverse r9, rdx, r11, rdx
    ret

; extern void decode(char message[], size_t rails);
; message is modified in-place
decode:
    traverse rdx, r9, rdx, r11
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
