section .text
global combinations

combinations:
    ; RDI - pointer to output buffer of arrays, each with 10 * 1-byte unsigned integers
    ; RSI - desired sum as a uint64_t
    ; RDX - size of combinations as a uint64_t
    ; RCX - array of elements to be excluded from combinations, each a 1-byte unsigned integer
    ; R8 - count of excluded elements, as a 8-byte unsigned integer
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
    ; If it is, combination is saved in the output buffer
    ; Otherwise, it returns
    ;
    ; This repeats up to the first function return
    ;
    ; As each recursive call starts in the subsequent number,
    ; all numbers in a combination are unique
    ;
    ; As the function starts at 1 and is stored in the stack before recursing,
    ; the combinations are saved in ascending order in the buffer

    push rbp
    mov rbp, rsp

    sub rsp, 42
    mov qword [rbp - 42], rsi
    mov qword [rbp - 34], rcx
    mov qword [rbp - 26], r8
    mov word [rbp - 18], 0
    mov qword [rbp - 16], 0
    mov qword [rbp - 8], 0

%define sum qword [rbp - 42]
%define excluded_array qword [rbp - 34]
%define num_excluded qword [rbp - 26]
%define current_combination_count byte [rbp - 18]
%define current_combination rbp - 17
%define num_combinations qword [rbp - 8]

    xor rcx, rcx
    xor rax, rax
    xor r9, r9 ; current_sum
    xor r10, r10 ; current digit

    call recur

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

    mov r11, excluded_array
    mov r8, -1
.check_excluded:
    inc r8 ; index

    cmp r8, num_excluded
    je .not_excluded

    cmp r10b, byte [r11 + r8]
    je .loop

    jmp .check_excluded

.not_excluded:
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
    cmp r9, sum
    jne .no_insert

    inc num_combinations
    lea r11, [rdi + 10]

    lea rsi, [current_combination]
    mov cl, dl
    rep movsb

    mov rdi, r11
.no_insert:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
