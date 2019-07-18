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
    cmp byte[rdi], 0   ; Check if dna is an empty string
    je .loop_end       ; If empty, skip loop
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
    inc rdi            ; Advance dna to next char
    inc rsi            ; Advance buffer to next char
    cmp byte [rdi], 0  ; See if we reached end of dna
    jne .loop_start    ; If chars remain, loop back

.loop_end:
    mov byte [rsi], 0  ; Null-terminate buffer
    ret
