default rel

section .data
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
    mov rax, rdi               ; Save name

    mov rdi, rsi               ; Set destination to buffer
    lea rsi, [one_for]         ; Set source
    mov rcx, one_for_len       ; Num bytes to copy
    rep movsb                  ; Copy bytes

    test rax, rax              ; Is name NULL?
    jne .copy_name             ; No => copy name into buffer

    lea rsi, [you]             ; Set source
    mov rcx, you_len           ; Num bytes to copy
    rep movsb                  ; Copy bytes
    jmp .end

.copy_name:
    mov rsi, rax               ; Set source to name
    cmp byte [rsi], 0          ; Found NUL?
    je .end                    ; Yes => skip loop
.loop_start:
    movsb                      ; Copy byte
    cmp byte [rsi], 0          ; Found NUL?
    jne .loop_start            ; No => next iteration

.end:
    lea rsi, [one_for_me]      ; Set source
    mov rcx, one_for_me_len    ; Num bytes to copy
    rep movsb                  ; Copy bytes
    ret
