default rel

section .rodata
    polite db ", please.", 0
    polite_length dq $ - polite

section .text

global front_door_response
global front_door_password
global back_door_response
global back_door_password

front_door_response:
    mov al, byte [rdi]
    ret

front_door_password:
    mov rsi, rdi
    lodsb
    cmp al, 'a'
    jl .store_upper
    add al, 'A' - 'a'
.store_upper:
    stosb
.loop:
    lodsb
    cmp al, `\0`
    je .exit
    cmp al, 'a'
    jge .store
    add al, 'a' - 'A'
.store:
    stosb
    jmp .loop
.exit:
    ret

back_door_response:
    mov rsi, rdi
    mov dl, 0
.loop:
    lodsb
    cmp al, `\0`
    je .exit
    cmp al, 'A'
    jl .ignore
    cmp al, 'Z'
    jl .letter
    cmp al, 'z'
    jg .ignore
    cmp al, 'a'
    jg .letter
.ignore:
    jmp .loop
.letter:
    mov dl, al
    jmp .loop
.exit:
    mov al, dl
    ret

back_door_password:
    mov r8, rdi
    mov r9, rsi
    mov rdi, rsi
    call front_door_password
    mov rsi, r9
    mov rdi, r8
.first_loop:
    lodsb
    cmp al, `\0`
    je .end_first_loop
    stosb
    jmp .first_loop
.end_first_loop:
    lea rsi, [polite]
    mov rcx, qword [polite_length]
    rep movsb
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
