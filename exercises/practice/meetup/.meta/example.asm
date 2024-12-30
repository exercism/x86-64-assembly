default rel

FIRST equ 1
SECOND equ 2
THIRD equ 3
FOURTH equ 4
TEENTH equ 5
LAST equ 6

section .rodata
; offset from end February for the start of the specified month
offset_array: dw -1, 307, 338, 1, 32, 62, 93, 123, 154, 185, 215, 246, 276, 307, 338

; day in month for last day in specified week
week_array: db -1, 7, 14, 21, 28, 19

section .text
global meetup

; void print_date(char *buffer, int year, int month, int day)
print_date:
    cld
    mov r10, rdx                        ; month
    mov r11, rcx                        ; day

    mov rax, rsi                        ; year
    mov rdx, 0
    mov rcx, 1000
    div rcx
    add al, '0'
    stosb

    mov rax, rdx
    mov rdx, 0
    mov rcx, 100
    div rcx
    add al, '0'
    stosb

    mov rax, rdx
    mov rdx, 0
    mov rcx, 10
    div rcx
    add al, '0'
    stosb

    mov al, dl
    add al, '0'
    stosb

    mov al, '-'
    stosb

    mov rax, r10                        ; month
    mov rdx, 0
    mov rcx, 10
    div rcx
    add al, '0'
    stosb

    mov al, dl
    add al, '0'
    stosb

    mov al, '-'
    stosb

    mov rax, r11                        ; day
    mov rdx, 0
    mov rcx, 10
    div rcx
    add al, '0'
    stosb

    mov al, dl
    add al, '0'
    stosb

    mov al, 0
    stosb
    ret

; dayofweek_t day_of_week(int year, int month, int day);
day_of_week:
    cmp rsi, 2
    jg .count

    sub rdi, 1
    add rsi, 12

.count:
    mov r10, rdx
    add r10, rdi
    shr rdi, 2
    add r10, rdi

    mov rdx, 0
    mov rax, rdi
    mov rcx, 25
    div rcx
    sub r10, rax
    shr rax, 2
    add r10, rax
    lea rcx, [offset_array]
    mov dx, [rcx + rsi * 2]
    add r10, rdx

    mov rdx, 0
    mov rax, r10
    mov rcx, 7
    div rcx
    mov rax, rdx
    inc rax
    ret

; int week_concludes(int year, int month, week_t week);
week_concludes:
    cmp rdx, LAST
    je .days_in_month

    lea rcx, [week_array]
    xor rax, rax
    mov al, [rcx + rdx]
    ret

.days_in_month:
    cmp rsi, 2
    je .february

    lea rcx, [offset_array]
    xor rdx, rdx
    xor rax, rax
    mov dx, [rcx + rsi * 2]
    mov ax, [rcx + rsi * 2 + 2]
    sub rax, rdx
    ret

.february:
    mov rax, rdi
    and rax, 3
    jnz .nonleap

    ; We have a multiple of 4.
    mov rdx, 0
    mov rax, rdi
    mov rcx, 100
    div rcx
    test rdx, rdx
    jnz .leap

    ; We have a multiple of 100.
    and rax, 3
    jnz .nonleap

    ; We have a multiple of 400.

.leap:
    mov rax, 29
    ret

.nonleap:
    mov rax, 28
    ret

; extern void meetup(char *buffer, int year, int month, week_t week, dayofweek_t dayofweek);
meetup:
    push r12
    push rdi ; buffer
    push rsi ; year
    push rdx ; month
    push r8 ; dayofweek
    push rsi ; year
    push rdx ; month

    ; int day = week_concludes(year, month, week);
    mov rdi, rsi ; year
    mov rsi, rdx ; month
    mov rdx, rcx ; week
    call week_concludes
    mov r12, rax ; day

    ; dayofweek_t dow = day_of_week(year, month, day);
    mov rdx, rax ; day
    pop rsi ; month
    pop rdi ; year
    call day_of_week

    pop rcx ; dayofweek
    sub rcx, rax ; dow
    jle .output

    sub rcx, 7

.output:
    add rcx, r12 ; day
    pop rdx ; month
    pop rsi ; year
    pop rdi ; buffer
    call print_date
    pop r12
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
