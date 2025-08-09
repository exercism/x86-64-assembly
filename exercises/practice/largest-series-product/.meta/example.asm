INVALID_CHARACTER equ -1
NEGATIVE_SPAN equ -2
INSUFFICIENT_DIGITS equ -3

section .text
global largest_product
largest_product:
    ; edi - span length as a int
    ; rsi - input string of digits
    ; output is a int64_t in rax, representing the product

    cmp edi, 0
    jl negative_span

    mov r8d, edi
    mov r9, rsi
    mov r10, -1 ; counter for num of digits in input
count_input_string:
    inc r10
    lodsb

    cmp al, 0
    je end_count

    ; checks if all chars are valid digits
    cmp al, '0'
    jl invalid_character
    cmp al, '9'
    jg invalid_character

    jmp count_input_string

end_count:
    cmp r8, r10
    jg insufficient_digits

    sub r10, r8
    inc r10 ; num of windows

    xor rax, rax ; max value
    mov r8, -1 ; current window index
window_loop:
    inc r8
    cmp r8, r10
    jge end_window_loop

    mov rsi, r9 ; restore input pointer
    add rsi, r8 ; start of window
    mov rcx, -1 ; digit index
    mov r11, 1 ; accumulator for product (1 is mempty)
    xor rdx, rdx ; to store current digit
accumulate_window:
    inc rcx
    cmp ecx, edi
    je check_maximum ; end of window

    mov dl, byte [rsi + rcx]
    sub dl, '0'
    cmp dl, 0
    je ignore_window ; if value is 0, all windows containing it result in 0
                     ; they can, therefore, be excluded

    imul r11, rdx ; accumulate product
    jmp accumulate_window

ignore_window:
    add r8, rcx ; next non-zero window is in r8 + rcx + 1
                ; as r8 is increment at the start of the loop, it's safe to simply add rcx to r8
    jmp window_loop

check_maximum:
    cmp r11, rax
    cmovg rax, r11 ; moves new accumulator to rax if it's greater
    jmp window_loop

invalid_character:
    mov rax, INVALID_CHARACTER
    ret

negative_span:
    mov rax, NEGATIVE_SPAN
    ret

insufficient_digits:
    mov rax, INSUFFICIENT_DIGITS
    ret

end_window_loop:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
