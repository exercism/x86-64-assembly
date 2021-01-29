default rel

section .rodata
black: db "black", 0
brown: db "brown", 0
red: db "red", 0
orange: db "orange", 0
yellow: db "yellow", 0
green: db "green", 0
blue: db "blue", 0
violet: db "violet", 0
grey: db "grey", 0
white: db "white", 0

color_array:
dq black
dq brown
dq red
dq orange
dq yellow
dq green
dq blue
dq violet
dq grey
dq white
dq 0  ; Sentinel value to indicate end of array

;
; Convert a resistor band's color to its numeric representation.
;
; Parameters:
;   rdi - color
; Returns:
;   rax - the resistor band's numeric representation or -1 if not found
;
section .text
global color_code
color_code:
    xor eax, eax              ; Initialize array index
    lea rcx, [color_array]    ; Load color array
    mov rdx, [rcx + rax * 8]  ; Read color from array
.arr_loop_start:
    mov rsi, rdi              ; Save input color

    mov r8b, byte [rdx]       ; Read char from color
    cmp r8b, byte [rsi]       ; Compare with char from input color
    jne .str_loop_end         ; If not equal, skip loop
.str_loop_start:
    inc rdx                   ; Advance color to next char
    inc rsi                   ; Advance input color to next char
    mov r8b, byte [rdx]       ; Read char from color
    cmp r8b, byte [rsi]       ; Compare with char from input color
    jne .str_loop_end         ; If not equal, exit loop
    test r8b, r8b             ; See if we reached end of color
    jne .str_loop_start       ; If chars remain, loop back

.str_loop_end:
    cmp r8b, byte [rsi]       ; Check if we found a match
    je .return                ; If we found a match, return the array index
    inc eax                   ; Increment array index
    mov rdx, [rcx + rax * 8]  ; Read color from array
    test rdx, rdx             ; See if we reached end of array
    jne .arr_loop_start       ; If colors remain, loop back

    mov eax, -1               ; Return -1

.return:
    ret

;
; Get a list of resistor band colors.
;
; Returns:
;   rax - a list of colors
;
global colors
colors:
    lea rax, [color_array]  ; Return the list of colors
    ret
