section .text
global combinations

combinations:
    ; RDI - output buffer of a bitset of combinations, as uint16_t
    ; RSI - desired sum as a uint16_t
    ; RDX - size of combinations as a uint64_t
    ; RCX - elements to be excluded from combinations, as a bitset
    ; return is a count for elements in output buffer as a uint64_t, in RAX

    ; Recursive algorithm
    ;
    ; It starts at 1 and loops until 9
    ; For each iteration, current number is saved in the stack
    ; in an array representing current combination
    ; and the function recurses starting at next num, always looping until 9
    ;
    ; Base case is when current combination length is equal to desired length
    ; The function then checks if the sum is the desired sum
    ; If it is, combination is saved in the output buffer as a bitset
    ; Otherwise, it returns
    ;
    ; This repeats up to the first function return
    ;
    ; As each recursive call starts in the subsequent number,
    ; all numbers in a combination are unique
    ;
    ; After getting all combinations, values are sorted using a simple bubble sort

    push rbp
    mov rbp, rsp

    sub rsp, 30
    mov qword [rbp - 30], rdi
    mov word [rbp - 22], si
    mov word [rbp - 20], cx
    mov qword [rbp - 18], 0
    mov qword [rbp - 10], 0
    mov word [rbp - 2], 0

%define sum word [rbp - 22]
%define excluded word [rbp - 20]
%define current_combination_count byte [rbp - 18]
%define current_combination rbp - 17
%define num_combinations qword [rbp - 8]
%define output qword [rbp - 30]

    xor rcx, rcx
    xor rax, rax
    xor r9, r9 ; current_sum
    xor r10, r10 ; current digit

    call recur

    mov r8, -1
    mov rsi, output
    mov rdi, output
.sort:
    inc r8

    cmp r8, num_combinations
    je .end_sort

    lodsw
    mov r9, -1
.check_values:
    inc r9

    lea r10, [r8 + r9 + 1]

    cmp r10, num_combinations
    je .store

    mov r10w, word [rsi + 2*r9]
    mov r11w, ax

    cmp r10w, ax
    cmovl ax, r10w
    cmovl r10w, r11w

    mov word [rsi + 2*r9], r10w
    jmp .check_values

.store:
    stosw
    jmp .sort

.end_sort:

    mov rax, num_combinations
    mov rsp, rbp
    pop rbp
    ret

recur:
    cmp current_combination_count, dl
    je .check_insert

.loop:
    inc r10

    cmp r10, 10
    jae .no_insert

    xor r8, r8
.check_excluded:
    inc r8 ; index

    cmp r8, 10
    jae .not_excluded

    bt excluded, r10w
    jc .loop

    jmp .check_excluded

.not_excluded:
    xor rax, rax

    mov al, current_combination_count
    inc current_combination_count

    mov byte [current_combination + rax], r10b

    add r9, r10
    push r10

    call recur

    pop r10
    sub r9, r10

    dec current_combination_count

    jmp .loop

.check_insert:
    cmp r9w, sum
    jne .no_insert

    inc num_combinations

    xor r8, r8
    lea rsi, [current_combination]
    mov cl, dl
    xor rax, rax
.accumulate:
    lodsb
    bts r8w, ax
    loop .accumulate

    mov rax, r8
    stosw
.no_insert:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
