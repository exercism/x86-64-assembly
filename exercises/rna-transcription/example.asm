;
; Given a DNA strand, return its RNA Complement Transcription.
;
; Parameters:
;   rdi - dna
;   rsi - buffer
;
section .text
global to_rna
to_rna:
    cmp byte[rdi], 0       ; Found NUL?
    je .loop_end           ; Yes => skip loop
.loop_start:
    cmp byte [rdi], 'C'
    je .cytosine
    cmp byte [rdi], 'G'
    je .guanine
    cmp byte [rdi], 'T'
    je .thymine
    cmp byte [rdi], 'A'
    jne .next
    mov byte [rsi], 'U'
    jmp .next
.cytosine:
    mov byte [rsi], 'G'
    jmp .next
.guanine:
    mov byte [rsi], 'C'
    jmp .next
.thymine:
    mov byte [rsi], 'A'
.next:
    inc rdi
    inc rsi
    cmp byte [rdi], 0      ; Found NUL?
    jne .loop_start        ; No => next iteration
.loop_end:
    mov byte [rsi], 0      ; Null-terminate buffer
    ret
