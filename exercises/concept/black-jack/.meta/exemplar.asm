C2 equ 2
C3 equ 3
C4 equ 4
C5 equ 5
C6 equ 6
C7 equ 7
C8 equ 8
C9 equ 9
C10 equ 10
CJ equ 11
CQ equ 12
CK equ 13
CA equ 14

TRUE equ 1
FALSE equ 0

section .text

global value_of_card
global higher_card
global value_of_ace
global is_blackjack
global can_split_pairs
global can_double_down

value_of_card:
    cmp rdi, C10
    jle .number

    cmp rdi, CA
    jl .ten_card

    mov rax, 1
    ret

.ten_card:
    mov rax, 10
    ret

.number:
    mov rax, rdi
    ret

higher_card:
    mov r8, rdi
    mov r9, rsi
    call value_of_card
    mov rdi, rsi
    mov rsi, rax
    call value_of_card
    cmp rsi, rax
    je .two_cards
    jg .first_higher

    mov rax, r9
    mov rdx, 0
    ret

.first_higher:
    mov rax, r8
    mov rdx, 0
    ret

.two_cards:
    mov rax, r8
    mov rdx, r9
    ret

value_of_ace:
    cmp rdi, CA
    je .return_one

    cmp rsi, CA
    je .return_one

    call value_of_card
    mov rdi, rsi
    mov rsi, rax
    call value_of_card
    add rsi, rax

    cmp rsi, 10
    jle .return_eleven

.return_one:
    mov rax, 1
    ret

.return_eleven:
    mov rax, 11
    ret

is_blackjack:
    cmp rdi, CA
    je .first_ace

    cmp rsi, CA
    je .second_ace

    jmp false

.first_ace:
    mov rdi, rsi
.second_ace:
    call value_of_card
    cmp rax, 10
    je true

false:
    mov rax, FALSE
    ret

true:
    mov rax, TRUE
    ret

can_split_pairs:
    call value_of_card
    mov rdi, rsi
    mov rsi, rax
    call value_of_card
    cmp rsi, rax
    je true
    jmp false

can_double_down:
    cmp rdi, CA
    je .first_ace

    cmp rsi, CA
    je .second_ace

    call value_of_card
    mov rdi, rsi
    mov rsi, rax
    call value_of_card
    add rax, rsi
    jmp .compare

.first_ace:
    mov rdi, rsi
.second_ace:
    call value_of_card
    inc rax
.compare:
    cmp rax, 9
    jl false
    cmp rax, 11
    jg false
    jmp true


%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
