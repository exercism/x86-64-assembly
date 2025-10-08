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
    mov rsi, rsp
    mov r10, 10
.stringify:
    cwd
    div r10w
    add dl, '0'
    dec rsi
    mov byte [rsi], dl
    test ax, ax
    jnz .stringify ; stringify number, saving chars in the stack, in reversed order
    mov rcx, rsp
    sub rcx, rsi
    rep movsb ; add stringified number
    lea rsi, [th]
    cmp byte [rsp - 2], '1'
    setne r8b
    cmp byte [rsp - 1], '1'
    sete r9b
    lea rdx, [first]
    test r8b, r9b
    cmovnz rsi, rdx ; if second last digit is not '1' and last digit is '1', suffix is "st"
    cmp byte [rsp - 1], '2'
    sete r9b
    lea rdx, [second]
    test r8b, r9b
    cmovnz rsi, rdx ; if second last digit is not '1' and last digit is '2', suffix is "nd"
    cmp byte [rsp - 1], '3'
    sete r9b
    lea rdx, [third]
    test r8b, r9b
    cmovnz rsi, rdx ; if second last digit is not '1' and last digit is '3', suffix is "rd"
    mov rcx, 2
    rep movsb ; add ordinal suffix
    lea rsi, [end_text]
    mov rcx, qword [end_text_sz]
    rep movsb ; add end text
    mov byte [rdi], 0 ; add NULL
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
