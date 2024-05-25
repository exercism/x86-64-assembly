;
; Determine if a number is an Armstrong number.
;
; Parameter:
;   rdi - number
; Returns:
;   rax - true if armstrong number, else false
;
section .text
global is_armstrong_number
is_armstrong_number:
    mov rbp, rsp              ; Save copy of stack pointer
    mov rsi, rsp              ; Save copy of stack pointer
    mov rax, rdi              ; number, with lowest digits progressively removed
    mov rbx, 10

extract_digit:
    xor rdx, rdx              ; Clear rdx
    div rbx                   ; Unsigned divide rdx:rax by rbx
    push rdx                  ; Store remainder
    test rax, rax
    jnz extract_digit         ; repeat while rax is not 0

    sub rsi, rsp
    sar rsi, 3                ; Count of digits

process_digit:
    pop rbx                   ; current digit
    mov rax, 1                ; current digit, raised to power of 0, 1, ...
    mov rcx, rsi

multiply:
    mul rbx
    loop multiply

    sub rdi, rax              ; rax has current digit, raised to power rsi
    cmp rsp, rbp
    jne process_digit         ; repeat while there are digits on the stack

    xor rax, rax
    test rdi, rdi             ; check if number minus digit powers is 0
    jnz return

    inc rax                   ; return true

return:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
