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
    mov r8, rsp               ; Save copy of stack pointer
    mov r9, rsp               ; Save copy of stack pointer
    mov rax, rdi              ; number, with lowest digits progressively removed
    mov r10, 10

extract_digit:
    xor rdx, rdx              ; Clear rdx
    div r10                   ; Unsigned divide rdx:rax by r10
    push rdx                  ; Store remainder
    test rax, rax
    jnz extract_digit         ; repeat while rax is not 0

    sub r9, rsp
    sar r9, 3                 ; Count of digits

process_digit:
    pop r10                   ; current digit
    mov rax, 1                ; current digit, raised to power of 0, 1, ...
    mov rcx, r9

multiply:
    mul r10
    loop multiply

    sub rdi, rax              ; rax has current digit, raised to power r9
    cmp rsp, r8
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
