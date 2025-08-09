default rel

section .rodata
    wink db "wink, "
    wink_len dq $-wink

    double_blink db "double blink, "
    double_blink_len dq $-double_blink

    close_your_eyes db "close your eyes, "
    close_your_eyes_len dq $-close_your_eyes

    jump db "jump, "
    jump_len dq $-jump

section .data
    codes dq wink, double_blink, close_your_eyes, jump ; array of pointers to strings
    lens  dq wink_len, double_blink_len, close_your_eyes_len, jump_len ; array of pointers to lengths

section .text

; first paramenter is starting position
; second is operation applied to starting position to change state
; third is ending position (exclusive)
; this allows for reusing the same macro to add the string in reversed order

%macro add_string 3
    mov rdx, %1
%%loop:
    %2 rdx ; operation is performed before comparison
    cmp rdx, %3
    je %%end

    bt r8, rdx
    jnc %%loop ; if bit not set, continue

    adc r10, 0 ; if any bit was set, r10 is greater than 0

    mov r11, rdx
    shl r11, 3 ; each pointer is a qword

    lea rsi, [codes] ; points to beginning of codes array
    add rsi, r11 ; points to relevant string pointer
    mov rsi, qword [rsi] ; dereferences string pointer, to get actual string

    lea rcx, [lens] ; points to beginning of the lens array
    add rcx, r11 ; points to relevant length
    mov rcx, qword [rcx] ; dereferences array pointer to get pointer to actual length
    mov rcx, qword [rcx] ; dereferences pointer to get actual length

    rep movsb ; moves the string to buffer

    jmp %%loop
%%end:
%endmacro

global commands
commands:
    ; rdi - output char buffer
    ; esi - code number
    ; char buffer is modified in place
    ; corresponding strings are concatenated using ", " as separator
    ; the separator is already added to the strings
    ; so it must be removed from the end if any string was added
    ; return is void

    mov r8d, esi
    cld

    xor r10, r10 ; flag to know if any string was added

    bt r8, 4
    jc reversed_string

    add_string -1, inc, 4
    jmp end_commands

reversed_string:
    add_string 4, dec, -1

end_commands:
    mov rax, 2 ; separator length
    cmp r10, 0
    cmovne r10, rax ; if r10 different than 0, moves separator length to r10

    sub rdi, r10 ; r10 is decremented by separator length
                 ; or by nothing if no string added

    mov byte [rdi], 0 ; appends NULL
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
