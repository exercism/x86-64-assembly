;
; Determine if a word or phrase is an isogram.
;
; Parameters:
;   rdi - phrase
; Returns:
;   rax - true if isogram, else false
;
section .text
global is_isogram
is_isogram:
    xor eax, eax           ; Initialize bitmap of used letters

    cmp byte [rdi], 0      ; Check if phrase is an empty string
    je .loop_end           ; If empty, skip loop
.loop_start:
    movzx ecx, byte [rdi]  ; Read char from phrase
    or ecx, 32             ; If uppercase, convert to lowercase
    sub ecx, 'a'           ; Subtract 'a' to get a number between 0 and 26
    cmp ecx, 26            ; Check if alphabetic
    jae .next              ; If not, process next char
    bts eax, ecx           ; Mark letter as used in bitmap
    jc .loop_end           ; If letter has already been used, return false
.next:
    inc rdi                ; Advance phrase to next char
    cmp byte [rdi], 0      ; See if we reached end of phrase
    jne .loop_start        ; If chars remain, loop back

.loop_end:
    setnc al               ; Return true
    ret
