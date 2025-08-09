default rel

section .rodata
    ; colors are saved with the size of the string + the string + the corresponding value
    ; the size allows for looping over the string more easily, for comparison

    black db 6, "black", 0, 0
    brown db 6, "brown", 0, 1
    red db 4, "red", 0, 2
    orange db 7, "orange", 0, 3
    yellow db 7, "yellow", 0, 4
    green db 6, "green", 0, 5
    blue db 5, "blue", 0, 6
    violet db 7, "violet", 0, 7
    grey db 5, "grey", 0, 8
    white db 6, "white", 0, 9

    ; suffixes are saved without NULL because they are composable (specifically kilo/mega/giga with ohms)

    ohms db "ohms"
    kilo db "kilo"
    mega db "mega"
    giga db "giga"

section .data
    giga_mul dq 1_000_000_000
    mega_mul dq 1_000_000
    kilo_mul dq 1_000

section .text
global label

; this macro finds the corresponding value associated with a color string
; it receives the string as parameter and loops over each string pointer until a match is found

%macro find_color 1
    lea r11, [black]
    xor rax, rax
%%loop:
    mov rdi, %1 ; string to be searched
    mov rsi, r11 ; current color string
    lodsb ; gets size
    mov rcx, rax ; stores size in rcx for REP
    add r11, rax
    add r11, 2 ; r11 points to start of the color, so it must be increment by the string size
               ; plus 1 for the size at the start and plus 1 to get to next color
    rep cmpsb
    jne %%loop ; if comparison returns unequal, continue looping
%%end:
    lodsb ; otherwise, rsi now points to the value at the end of the matching string
%endmacro

; this macro adds the suffix corresponding to the pointer passed as a parameter

%macro suffix 1
    lea rsi, [%1]
    mov rcx, 4 ; all suffixes strings have 4 of size
    rep movsb
%endmacro

; this macro takes 0 or 2 parameters
; it uses conditional assembly to process certain instructions only when the number of parameters is 2
; the 0 parameter version processes values lesser than 1000, without extra suffix (other than the obligatory "ohms")
; the 2 parameter version processes values with an extra suffix, which require extra processing to check for '.', etc.

%macro handle_multiple 0-2
    mov rax, r10

; the 2 parameter version must check if there's a remainder after dividing by the multiple
; so as to add '.' if necessary

%if %0 == 2
    xor rdx, rdx
    mov r11, qword [%1]
    div r11
    mov r9, rdx ; r9 gets the remainder
%endif

    ; pushes all digits to the stack to add them in the correct order
    ; prologue

    push rbp
    mov rbp, rsp

    mov r11, 10
    xor rcx, rcx ; counter
%%get_digits:
    xor rdx, rdx
    div r11

    inc rcx ; increases counter
    dec rsp ; decreases stack pointer, to push value

    add dl, '0' ; digits are pushed to stack as chars
    mov byte [rsp], dl

    cmp rax, 0
    jne %%get_digits

    mov rsi, rsp
    rep movsb ; adds digits to buffer

    ; epilogue

    mov rsp, rbp
    pop rbp

; checks if there's a '.'

%if %0 == 2
    cmp r9, 0
    je %%separator

    mov al, '.'
    stosb

    xor rdx, rdx
    imul rax, r9, 10 ; remainder is multiplied by 10
    mov r11, qword [%1]
    div r11 ; and then divided by the multiple, to get just the digit

    add al, '0' ; transforms into a char
    stosb
%endif

%%separator:
    mov al, ' '
    stosb

%if %0 == 2
    suffix %2
%endif

%endmacro

label:
    ; rdi - output char buffer
    ; rsi - input string array
    ; end of input array is marked with NULL
    ; return is void

    ; Part of this solution comes from my solution to resistor color duo
    ;

    ; both rdi and rsi are used by find_color and must be preserved beforehand
    mov rdx, rdi
    mov r10, rsi

    find_color [r10]
    mov r8, rax ; r8 holds first color value

    find_color [r10 + 8]
    mov r9, rax ; r9 holds second color value

    find_color [r10 + 16]
    ; rax holds third color value

    mov rdi, rdx ; restore rdi

    imul r10, r8, 10
    add r10, r9 ; r10 holds the accumulated value for the two first colors
add_zeros:
    cmp rax, 0
    je finish_adding_zeros

    dec rax
    imul r10, r10, 10 ; continuosly multiply accumulator by 10 until end of trailing zeros
    jmp add_zeros

finish_adding_zeros:
    ; dispatch for relevant multiple

    cmp r10, qword [giga_mul]
    jge handle_giga

    cmp r10, qword [mega_mul]
    jge handle_mega

    cmp r10, qword [kilo_mul]
    jge handle_kilo

    ; if less than 1000, just adds digits
    handle_multiple
    jmp end

handle_giga:
    handle_multiple giga_mul, giga
    jmp end

handle_mega:
    handle_multiple mega_mul, mega
    jmp end

handle_kilo:
    handle_multiple kilo_mul, kilo
    jmp end

end:
    ; adds "ohms"
    suffix ohms

    ; adds NULL
    mov al, 0
    stosb
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
