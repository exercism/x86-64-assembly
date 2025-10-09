default rel

section .rodata
    mid_text db ", you are the "
    mid_text_sz dq $-mid_text
    end_text db " customer we serve today. Thank you!"
    end_text_sz dq $-end_text
    th db "th"
    first db "st"
    second db "nd"
    third db "rd"

section .text
global format

format:
    movsb
    cmp byte [rsi], 0
    jne format ; add first name

    lea rsi, [mid_text]
    mov rcx, qword [mid_text_sz]
    rep movsb ; add middle text

    mov ax, dx
    mov r11, rsp
    mov r10, 10
.stringify:
    cwd
    div r10w
    add dl, '0' ; converts digit to its char equivalent
    dec rsp ; allocates 1 byte in the stack
    mov byte [rsp], dl ; saves char digit in the stack
    test ax, ax
    jnz .stringify ; stringify number, saving chars in the stack, in reversed order

    mov rsi, rsp
    mov rcx, r11
    sub rcx, rsp ; rcx is now the size of the stringified number (r11 - rsp)
    mov rdx, rcx ; rdx holds number of digits
    rep movsb ; add stringified number

    lea rsi, [th] ; default ordinal suffix is "th"
    cmp byte [r11 - 2], '1'
    setne r8b ; true if number has >= 2 digits and does not end in "1n", where n is a digit ['0'..'9']

    cmp rdx, 2
    setl r9b ; true if number has less than 2 digits
    or r8b, r9b ; true if number has < 2 digits or has >= 2 digits and does not end in "1n", where n is a digit ['0'..'9']

    cmp byte [r11 - 1], '1'
    sete r9b ; true if number ends in '1'
    lea rdx, [first]
    test r8b, r9b
    cmovnz rsi, rdx ; if last digit is '1' and (number has 1 digit or second last digit is not '1'), suffix is "st"

    cmp byte [r11 - 1], '2'
    sete r9b ; true if number ends in '2'
    lea rdx, [second]
    test r8b, r9b
    cmovnz rsi, rdx ; if last digit is '2' and (number has 1 digit or second last digit is not '1'), suffix is "nd"

    cmp byte [r11 - 1], '3'
    sete r9b ; true if number ends in '3'
    lea rdx, [third]
    test r8b, r9b
    cmovnz rsi, rdx ; if last digit is '3' and (number has 1 digit or second last digit is not '1'), suffix is "rd"

    mov rcx, 2 ; all ordinal suffixs have size 2
    rep movsb ; add ordinal suffix

    lea rsi, [end_text]
    mov rcx, qword [end_text_sz]
    rep movsb ; add end text

    mov byte [rdi], 0 ; add NULL
    mov rsp, r11
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
