default rel

section .data
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
dq 0    ; Sentinel value to indicate end of array

;
; Convert a resistor band's color to its numeric representation.
;
; Parameters:
;   rdi - color
;
; Returns:
;   rax - array index or -1 if not found
;
section .text
global color_code
color_code:
    xor eax, eax               ; Set loop counter to 0
    lea r8, [color_array]      ; Save color array
    mov rsi, [r8 + rax * 8]    ; Fetch a color
.arr_loop_start:
    mov rcx, rdi               ; Save color parameter
    mov dl, byte [rsi]         ; Fetch a byte
    cmp dl, byte [rcx]         ; Compare with color parameter
    jne .str_loop_end          ; Not equal => skip loop
.str_loop_start:
    inc rsi
    inc rcx
    mov dl, byte [rsi]         ; Fetch a byte
    cmp dl, byte [rcx]         ; Compare with color parameter
    jne .str_loop_end          ; Not equal => exit loop
    test dl, dl                ; Is it NUL?
    jne .str_loop_start        ; No => next iteration

.str_loop_end:
    cmp dl, byte [rcx]         ; Found a match?
    je .return                 ; Yes => return array index

    inc eax                    ; Increment loop counter
    mov rsi, [r8 + rax * 8]    ; Fetch a color
    test rsi, rsi              ; End of array?
    jne .arr_loop_start        ; No => next iteration

    mov eax, -1                ; Set return value

.return:
    ret

;
; Get a list of resistor band colors.
;
; Returns:
;   rax - array of colors
;
global colors
colors:
    lea rax, [color_array]     ; Set return value
    ret
