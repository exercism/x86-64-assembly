section .data
one_for: db "One for "
one_for_len: equ $ - one_for

you: db "you"
you_len: equ $ - you

one_for_me: db ", one for me.", 0
one_for_me_len: equ $ - one_for_me

section .text
global two_fer
two_fer:
    mov rax, rdi

    ; Copy "One for " into output buffer
    mov rdi, rsi
    mov rsi, one_for
    mov rcx, one_for_len
    rep movsb

    ; Check if name is NULL
    test rax, rax
    jne .not_null

    ; Copy "you" into output buffer
    mov rsi, you
    mov rcx, you_len
    rep movsb
    jmp .end

.not_null:
    ; Copy name into output buffer
    mov rsi, rax
    cmp byte [rsi], 0
    je .end
.loop_start:
    movsb
    cmp byte [rsi], 0
    jne .loop_start

.end:
    ; Copy ", one for me." into output buffer
    mov rsi, one_for_me
    mov rcx, one_for_me_len
    rep movsb
    ret
