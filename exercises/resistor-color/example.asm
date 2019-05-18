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

color_array_len: equ ($ - color_array) / 8

section .text
global color_code
color_code:
    ; Loop through the color array
    mov eax, 0
.arr_loop_start:
    mov rdx, color_array
    mov rsi, [rdx + rax * 8]

    ; Compare array color with input color
    mov ecx, 0
    mov dl, byte [rsi + rcx]
    cmp dl, byte [rdi + rcx]
    jne .str_loop_end
.str_loop_start:
    inc ecx
    mov dl, byte [rsi + rcx]
    cmp dl, byte [rdi + rcx]
    jne .str_loop_end
    cmp dl, 0
    jne .str_loop_start

.str_loop_end:
    ; If we found a match, return the index
    cmp dl, byte [rdi + rcx]
    je .return

    inc eax
    cmp eax, color_array_len
    jne .arr_loop_start

    ; Return -1 to indicate that no match was found
    mov eax, -1

.return:
    ret

global colors
colors:
    mov rax, color_array
    ret
