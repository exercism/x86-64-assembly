;
; Calculate the Hamming difference between two DNA strands.
;
; Parameters:
;   rdi - strand1
;   rsi - strand2
; Returns:
;   rax - the difference between two DNA strands
;
section .text
global distance
distance:
    xor eax, eax        ; Initialize difference

    cmp byte [rdi], 0   ; Check if strand1 is an empty string
    je .loop_end        ; If empty, skip loop
    cmp byte[rsi], 0    ; Check if strand2 is an empty string
    je .loop_end        ; If empty, skip loop
.loop_start:
    mov cl, byte [rdi]  ; Read char from strand1
    cmp cl, byte [rsi]  ; Compare with char from strand2
    je .next            ; If equal, process next char
    inc eax             ; Increment difference
.next:
    inc rdi             ; Advance strand1 to next char
    inc rsi             ; Advance strand2 to next char
    cmp byte [rdi], 0   ; See if we reached end of strand1
    je .loop_end        ; If there are no more chars, exit loop
    cmp byte [rsi], 0   ; See if we reached end of strand2
    jne .loop_start     ; If chars remain, loop back

.loop_end:
    mov cl, byte [rdi]  ; Read char from strand1
    cmp cl, byte [rsi]  ; Compare with char from strand2
    je .return          ; If equal, return the difference

    mov eax, -1         ; Return -1 to indicate an error

.return:
    ret
