;
; Determine if a sentence is a pangram.
;
; Parameters:
;   rdi - str
; Returns:
;   rax - true if pangram, else false
;
section .text
global is_pangram
is_pangram:
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
.next:
    inc rdi                ; Advance input string to next char
    cmp byte [rdi], 0      ; See if we reached the end
    jne .loop_start        ; If chars remain, loop back

.loop_end:
    cmp ecx, 0x3FFFFFF     ; Check if every letter of the alphabet is used
    sete al                ; If so, return true, else return false
    ret
