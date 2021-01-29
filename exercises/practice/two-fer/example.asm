default rel

section .rodata
one_for: db "One for "
one_for_len: equ $ - one_for

you: db "you"
you_len: equ $ - you

one_for_me: db ", one for me.", 0
one_for_me_len: equ $ - one_for_me

;
; Create a sentence of the form "One for X, one for me."
;
; Parameters:
;   rdi - name
;   rsi - buffer
;
section .text
global two_fer
two_fer:
    mov rax, rdi             ; Save name

    mov rdi, rsi             ; Set destination to buffer
    lea rsi, [one_for]       ; Set source
    mov rcx, one_for_len     ; Set string length
    rep movsb                ; Append string to buffer

    test rax, rax            ; Check if name is provided
    jne .copy_name           ; If so, append name to buffer

    lea rsi, [you]           ; Set source
    mov rcx, you_len         ; Set string length
    rep movsb                ; Append string to buffer
    jmp .end

.copy_name:
    mov rsi, rax             ; Set source to name
    cmp byte [rsi], 0        ; Check if name is an empty string
    je .end                  ; If empty, skip loop
.loop_start:
    movsb                    ; Append char to buffer
    cmp byte [rsi], 0        ; See if we reached end of name
    jne .loop_start          ; If chars remain, loop back

.end:
    lea rsi, [one_for_me]    ; Set source
    mov rcx, one_for_me_len  ; Set string length
    rep movsb                ; Append string to buffer
    ret
