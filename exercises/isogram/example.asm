;
; Determine if a word or phrase is an isogram.
;
; Parameters:
;   rdi - phrase
;
; Returns:
;   rax - 1 if isogram, else 0
;
section .text
global is_isogram
is_isogram:
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
    jc .loop_end
.skip:
    inc rdi
    cmp byte [rdi], 0        ; Found NUL?
    jne .loop_start          ; No => next iteration
.loop_end:
    setnc al                 ; Set return value
    ret
