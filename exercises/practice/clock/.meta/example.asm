section .text

global create
global add_minutes
global subtract_minutes
global equal

subtract_minutes:
    ; rdi - hour, as a int64_t
    ; rsi - minute, as a int64_t
    ; rdx - value, in minutes, to be subtracted, as a int64_t
    ; return is a struct of 2 uint8_t in rax

    neg rdx ; value = -value

    ; function fallthrough
    ; execution continues in add_minutes

add_minutes:
    ; rdi - hour, as a int64_t
    ; rsi - minute, as a int64_t
    ; rdx - value, in minutes, to be added, as a int64_t
    ; return is a struct of 2 uint8_t in rax

    add rsi, rdx ; minute += value

    ; function fallthrough
    ; execution continues in create

create:
    ; rdi - hour, as a int64_t
    ; rsi - minute, as a int64_t
    ; return is a struct of 2 uint8_t in rax

    mov rax, rsi

    mov r8, 60
    cqo ; sets rdx bits according to rax sign
    idiv r8 ; signed division of minutes by 60
            ; rax now holds num of hours to be added
            ; rdx holds num of minutes

    add rax, rdi

    mov r10, rdx
    cmp r10, 0
    jge .continue_minute ; if num of minutes is non-negative, continue
    ; otherwise

    add r10, 60 ; adds 60 to it, so it's now positive
    dec rax ; reduces num of hours by 1

.continue_minute:
    mov r8, 24
    cqo ; sets rdx bits according to rax sign
    idiv r8 ; signed division of num of hours by 24
            ; rdx holds num of hours

    mov rax, rdx
    cmp rax, 0
    jge .continue_hour ; if num of hours is non-negative, continue
    ; otherwise

    add rax, 24 ; adds 24 to it, so it's now positive
    ; as the exercises doesn't count num of days or other metric higher than hour
    ; there's no need to decrease anything

.continue_hour:
    ; the first 8 bits of rax already holds num of hours
    ; the number of minutes must be added in the following byte

    shl r10, 8 ; second byte of r10 now holds num of minutes
    or rax, r10 ; rax now holds num of hours in the first byte
                ; num of minutes in the second byte
                ; and 0 in the following higher 6 bytes

    ret

equal:
    ; clock1 is stored in the lowest 2 bytes of rdi
    ; clock2 is stored in the lowest 2 bytes of rsi
    ; return is a boolean in rax

    ; and rdi and rsi with MAX WORD to eliminate any possible garbage value
    ; in the higher 6 bytes

    and rdi, 65535 ; MAX WORD
    and rsi, 65535 ; MAX WORD

    cmp rdi, rsi
    sete al ; sets rax if rdi equals to rsi. Clears otherwise

    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
