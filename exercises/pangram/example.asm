;
; Determine if a sentence is a pangram.
;
; Parameters:
;   rdi - sentence
;
; Returns:
;   rax - 1 if pangram, else 0
;
section .text
global is_pangram
is_pangram:
    xor eax, eax             ; Used letters bitmap
    cmp byte [rdi], 0        ; Found NUL?
    je .loop_end             ; Yes => skip loop
.loop_start:
    movzx ecx, byte [rdi]    ; Fetch byte
    or ecx, 32
    sub ecx, 'a'
    cmp ecx, 26              ; Is alphabetic character?
    jae .skip                ; No => skip
    bts eax, ecx             ; Update used letters bitmap
.skip:
    inc rdi
    cmp byte [rdi], 0        ; Found NUL?
    jne .loop_start          ; No => next iteration
.loop_end:
    cmp eax, 0x3FFFFFF       ; Is every letter used?
    sete al                  ; Yes => return true
    ret
