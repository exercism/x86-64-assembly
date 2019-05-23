;
; Calculate the Hamming Distance between two DNA strands.
;
; Parameters:
;   rdi - strand1
;   rsi - strand2
;
; Returns:
;   rax - distance
;
section .text
global distance
distance:
    xor eax, eax          ; Set distance to 0

    cmp byte [rdi], 0     ; Found NUL in strand1?
    je .loop_end          ; Yes => skip loop
    cmp byte[rsi], 0      ; Found NUL in strand2?
    je .loop_end          ; Yes => skip loop
.loop_start:
    mov cl, byte [rdi]    ; Fetch byte from strand1
    cmp cl, byte [rsi]    ; Compare with strand2
    je .skip              ; Equal => skip increment
    inc eax               ; Increment distance
.skip:
    inc rdi
    inc rsi
    cmp byte [rdi], 0     ; Found NUL in strand1?
    je .loop_end          ; Yes => exit loop
    cmp byte [rsi], 0     ; Found NUL in strand2?
    jne .loop_start       ; No => next iteration

.loop_end:
    mov cl, byte [rdi]    ; Fetch byte from strand1
    cmp cl, byte [rsi]    ; Compare with strand2
    je .return            ; Equal => return distance

    mov eax, -1           ; Set return value

.return:
    ret
