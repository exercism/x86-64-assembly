default rel

%assign s 1_000_000_000
%assign m s / 60 ; minute
%assign h m / 60 ; hour
%assign d h / 24 ; days

%assign rem_s s - (m * 60)
%assign rem_m m - (h * 60)
%assign rem_h h - (d * 24)

section .data
    acc_days dq 0,
             dq 31,
             dq 31 + 28,
             dq 31 + 28 + 31,
             dq 31 + 28 + 31 + 30,
             dq 31 + 28 + 31 + 30 + 31,
             dq 31 + 28 + 31 + 30 + 31 + 30,
             dq 31 + 28 + 31 + 30 + 31 + 30 + 31,
             dq 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31,
             dq 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
             dq 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
             dq 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30

section .text
global add_seconds

%define year qword [rbp - 8]
%define month qword [rbp - 16]
%define day qword [rbp - 24]
%define hour qword [rbp - 32]
%define minute qword [rbp - 40]
%define second qword [rbp - 48]

%macro stringify_num 2
    mov rax, %1
    sub rsp, %2
    mov r11, %2
%%loop:
    dec r11

    xor rdx, rdx
    mov r10, 10
    div r10

    add rdx, '0'
    mov byte [rsp + r11], dl

    test rax, rax
    jnz %%loop

%%pad_start:
    dec r11

    cmp r11, 0
    jl %%end

    mov byte [rsp + r11], '0'

    jmp %%pad_start
%%end:
%endmacro

%macro insert_string 2
    mov rcx, %1
    mov rsi, rsp

    rep movsb

    mov al, %2
    stosb
%endmacro

%macro is_leap 1
    xor r11, r11

    mov rax, %1
    xor rdx, rdx
    mov rcx, 400
    div rcx

    test rdx, rdx
    jz %%leap

    mov rax, %1
    xor rdx, rdx
    mov rcx, 100
    div rcx

    test rdx, rdx
    jz %%non_leap

    test %1, 3
    jnz %%non_leap
%%leap:
    mov r11, 1
%%non_leap:
%endmacro

%macro parse_num 2
    xor rax, rax
    xor r10, r10
    mov r11, %2
%%loop:
    dec r11

    lodsb
    sub al, '0'
    imul r10, r10, 10
    add r10, rax

    test r11, r11
    jnz %%loop

    mov %1, r10
    lodsb
%endmacro

%macro handle_time 0
    mov rax, second
    add rax, rem_s
    xor rdx, rdx
    mov r10, 60
    div r10

    mov second, rdx

    add rax, minute
    add rax, rem_m
    xor rdx, rdx
    div r10

    mov minute, rdx

    add rax, hour
    add rax, rem_h
    xor rdx, rdx
    mov r10, 24
    div r10

    mov hour, rdx
    add day, rax
%endmacro

%macro accumulate_days 0
    is_leap year

    cmp month, 3
    setge r10b

    and r11b, r10b ; if starting year is leap, but month is march or beyond
                   ; leap day was already counted, so r11 serves as flag for adding it again
                   ; in adjust_days_for_leap_years

    add day, d

    mov r8, month
    lea r9, [acc_days]
    mov r10, qword [r9 + 8*r8 - 8] ; r10 holds accumulated number of days in year,
                                   ; corresponding to previous months

    add day, r10
%endmacro

%macro adjust_days_for_leap_years 0
    add day, r11 ; flag in case year is leap but leap day was already counter
%%loop:
    cmp day, 365
    jl %%check_current ; loops until days fit in an year

    is_leap year ; sets r11 if year is leap

    inc year ; increments current year
    sub day, 365 ; reduces days by an year length
    sub day, r11 ; if year is leap, must reduce for an extra day

    jmp %%loop
%%check_current:
    cmp day, 59 ; 31 days in January + 28 days in February
    setg r10b

    is_leap year ; sets r11 if year is leap

    and r11b, r10b ; sets r11 if year is leap and day is after February, 28
    sub day, r11 ; reduce for leap day, if any
%endmacro

%macro get_month 0
    lea r8, [acc_days]
    mov r9, 12
%%loop:
    dec r9

    mov r10, qword [r8 + 8*r9]

    cmp r10, day
    jge %%loop ; loops until num of day is larger than accumulator for month

    sub day, r10 ; reduces num of days by accumulated num of days in previous months
    mov month, r9
    inc month ; month starts at 1
%endmacro

add_seconds:
    ; RDI - output buffer
    ; RSI - input string
    ; return is void

    ; The output should be a 20-byte string (including NULL at the end)
    ; with the format YYYY-MM-DDTHH:MM:SS

    ; The input string might have the same format, or just YYYY-MM-DD

    ; Algorithm is:
    ;
    ; 1 - Parse the input string, storing in the stack year, month, day, hour, minute and second
    ;
    ; 2 - Handles time, by adding offsets corresponding to a gigasecond and taking modulus of each unit,
    ; accumulating the result in the stack;
    ;
    ; 3 - Accumulates months in days and incrementally adds years, subtracting 365 days each year,
    ; or 366 in a leap year;
    ;
    ; 4 - From the remaining days, check table to get the corresponding month and the final day in the month;
    ;
    ; 5 - Checks if the current year is leap and month is march or beyond, to account for an unaccounted leap day;
    ;
    ; 6 - Stringify and inserts all those numbers in the order, with the corresponding separator.

    push rbp
    mov rbp, rsp
    sub rsp, 48

    mov hour, 0
    mov minute, 0
    mov second, 0

    parse_num year, 4
    parse_num month, 2
    parse_num day, 2

    test al, al
    jz .skip_time_parsing

    parse_num hour, 2
    parse_num minute, 2
    parse_num second, 2

.skip_time_parsing:

    handle_time
    accumulate_days
    adjust_days_for_leap_years
    get_month

    stringify_num year, 4
    insert_string 4, '-'

    stringify_num month, 2
    insert_string 2, '-'

    stringify_num day, 2
    insert_string 2, 'T'

    stringify_num hour, 2
    insert_string 2, ':'

    stringify_num minute, 2
    insert_string 2, ':'

    stringify_num second, 2
    insert_string 2, 0

    mov rsp, rbp
    pop rbp
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
