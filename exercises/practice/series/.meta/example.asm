EMPTY_SERIES equ -1
ZERO_LENGTH equ -2
NEGATIVE_LENGTH equ -3
EXCESSIVE_LENGTH equ -4

SLICE_SIZE equ 20

section .text
global slices

slices:
	; rdi - output array of arrays of chars (char buffer[][SLICE_SIZE])
    ; rsi - input string
    ; rdx - length of the slices, as a uint64_t
    ; return is the size of the output array, as a int64_t, in rax

    ; The implementation is straightforward
    ; First, the input is counted
    ; Then, the number of slices is calculated
    ; After that, the input array is iterated for each slice
    ; and the number of chars corresponding to slice length is copied
    ;
    ; It's worth mentioning that the output array is of the form char buffer[][SLICE_SIZE]
    ; so rdi is a pointer to the beginning of the outer array
    ; and each char array is SLICE_SIZE * sizeof(char) distant from the previous one

    cmp rdx, 0
    je zero_length
    jl negative_length

    mov r8, rsi ; preserves rsi for after the count
    mov rcx, -1 ; doesn't count NULL
count_input:
    inc rcx
    lodsb
    cmp al, 0
    jne count_input

    cmp rcx, 0
    je empty_series

    cmp rcx, rdx
    jl excessive_length

    mov r9, rdi ; preserves rdi for successive MOVSB
    mov r10, rdx ; preserves slice length

    sub rcx, rdx
    inc rcx ; num of slices

    mov rdx, rcx ; counter for iterating over the input array
                 ; rcx is used for REP in each iteration, so another register is needed

    mov r11, rcx ; preserves num of slices for returning at the end

add_slices:
    dec rdx

    mov rsi, r8
    inc r8

    mov rdi, r9
    add r9, SLICE_SIZE

    mov rcx, r10 ; moves slice length to rcx for REP
    rep movsb

    mov al, 0
    stosb ; appends NULL

    cmp rdx, 0
    jne add_slices ; loops until end of num of slices

    mov rax, r11 ; returns number os slices

	ret

empty_series:
    mov rax, EMPTY_SERIES
    ret

zero_length:
    mov rax, ZERO_LENGTH
    ret

negative_length:
    mov rax, NEGATIVE_LENGTH
    ret

excessive_length:
    mov rax, EXCESSIVE_LENGTH
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
