;
; Determine if a word or phrase is an isogram.
;
; Parameters:
;   rdi - str
; Returns:
;   rax - true if isogram, else false
;
section .text
global is_isogram
is_isogram:
    xor eax, eax           ; Set return value
    xor ecx, ecx           ; Initialize bitmap of used letters

    cmp byte [rdi], 0      ; Check if input string is empty
    je .loop_end           ; If empty, skip loop
.loop_start:
    movzx edx, byte [rdi]  ; Read char from input string
    or edx, 32             ; If uppercase, convert to lowercase
    sub edx, 'a'
    cmp edx, 26            ; Check if alphabetic
    jae .next              ; If not, process next char
    bts ecx, edx           ; Mark letter as used in bitmap
    jc .loop_end           ; If letter has already been used, return false
.next:
    inc rdi                ; Advance input string to next char
    cmp byte [rdi], 0      ; See if we reached the end
    jne .loop_start        ; If chars remain, loop back

.loop_end:
    setnc al               ; Return true
    ret
