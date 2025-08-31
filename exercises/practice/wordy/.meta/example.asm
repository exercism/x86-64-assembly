default rel

SUCCESS equ 0
SYNTAX_ERROR equ 1
UNKNOWN_OPERATION equ 2

section .data
    beginning db "What is"
    beginning_size dq $-beginning

    minus db "minus"
    minus_size dq $-minus

    plus db "plus"
    plus_size dq $-plus

    multiplication db "multiplied by"
    multiplication_size dq $-multiplication

    division db "divided by"
    division_size dq $-division

section .text
global answer

%macro is_between_range 3
    xor rdx, rdx

    cmp %1, %2
    jl %%false

    cmp %1, %3
    jg %%false

    mov rdx, 1
%%false:
    cmp rdx, 1
%endmacro

%define is_digit(x) is_between_range x, '0', '9'

%macro check_separator 0
    lodsb

    cmp al, ' '
    jne .syntax_error
%endmacro

%macro check_operation 2
    mov rsi, rdx ; restores input string for checking next op
    inc r11 ; advances flag to next op
    lea rdi, [%1]
    mov rcx, qword [%2]

    repe cmpsb
    je .found_op ; if found op, checks separator
%endmacro

%macro check_and_accumulate_number 0
    is_digit(al)
    jne .syntax_error ; if no digit, there's a syntax error
    ; otherwise accumulates number

    imul r8, r8, 10
    sub al, '0'
    add r8, rax
%endmacro

%macro process_multiplication 0
    imul r8, qword [r12]
    mov qword [r12], r8 ; moves accumulated product to number
%endmacro

%macro process_division 0
    mov rax, qword [r12]
    cqo
    idiv r8 ; signed division
    mov qword [r12], rax ; moves accumulated quotient to number
%endmacro

answer:
    ; rdi - pointer to a int64_t, where the result of evaluating the question should be stored
    ; rsi - string which represents the question
    ; rax should return an error flag

    ; This exercise is mostly a careful management of states and transitions
    ; However, it seems arbitrary in places (mostly on how it handles exceptions)
    ; I must confess I haven't yet understood the logic of defining "What is?" as syntax error and "Who is the president of the United States?" as unknown operation

    push r12
    mov r12, rdi

    lea rdi, [beginning]
    mov rcx, qword [beginning_size]

    repe cmpsb
    jne .unknown_op ; if question doesn't start with "What is", it's an unknown op and not syntax error
                    ; don't ask me why

    check_separator ; if starts with "What is", but separator is not right, it's a syntax error

    xor r11, r11 ; flag for previous operation
                 ; 0 -> initial state, sets number in memory
                 ; 1 -> number set, waiting op
                 ; 2 -> previous op is subtraction
                 ; 3 -> previous op is addition
                 ; 4 -> previous op is multiplication
                 ; 5 -> previous op is division
                 ; flag is reset to 1 after applying op

    xor r10, r10 ; boolean to check if loop must parse number or op
                 ; 0 -> parses op
                 ; else -> parses number
.main_loop:
    not r10 ; logical not changes boolean between 0 and non-zero

    cmp r10, 0
    jne .parse_num ; if boolean not zero, parses number
    ; otherwise parses op

.parse_op:
    mov rdx, rsi ; saves current point of input string

    ; checks ops in order of op flag
    ; once found, jumps to .found_op

    check_operation minus, minus_size
    check_operation plus, plus_size
    check_operation multiplication, multiplication_size
    check_operation division, division_size

    ; op was not found, checks if it's syntax error or unknown op

    mov rsi, rdx
    lodsb

    is_digit(al)
    je .syntax_error

    cmp al, '?'
    je .syntax_error

    jmp .unknown_op

.found_op:
    ; op was found, must check separator

    check_separator ; if invalid, syntax error
    ; otherwise, continue looping

    jmp .main_loop

.parse_num:
    xor rax, rax
    xor r8, r8 ; number accumulator

    lodsb

    cmp al, '-'
    sete r9b ; flag for negative number
    je .parse_num_loop ; if negative, al is no digit
    ; otherwise digit must be checked and accumulated

    check_and_accumulate_number

.parse_num_loop:
    lodsb

    cmp al, ' '
    je .process_num ; found separator, number must be processed according to op flag

    cmp al, '?'
    je .end_parse ; found end of question, number must be processed and function returns successfully

    check_and_accumulate_number

    jmp .parse_num_loop ; continue accumulating number

.process_num:
    mov rdx, r8
    neg rdx

    cmp r9b, 1
    cmove r8, rdx ; if sign flag is set, moves negated number to accumulator

    ; dispatch according to op flag

    cmp r11, 1
    jl .initial_num ; if flag is 0, initial number must be loaded
    je .syntax_error ; if equal to 1, op was not set and this is a syntax error

    cmp r11, 3
    jl .minus ; flag 2 is subtraction
    je .plus ; flag 3 is addition

    cmp r11, 5
    jl .multiplication ; flag 4 is multiplication
    je .division ; flag 5 is division
    ; otherwise op flag is invalid and there's a syntax error

    jmp .syntax_error

.multiplication:
    process_multiplication
    mov r11, 1 ; sets op flag to "number set" state
    jmp .main_loop

.division:
    process_division
    mov r11, 1 ; sets op flag to "number set" state
    jmp .main_loop

.minus:
    neg r8 ; negates accumulator
    ; execution fallthroughs
.plus:
    add qword [r12], r8 ; adds current number with accumulator
    mov r11, 1 ; sets op flag to "number set" state
    jmp .main_loop

.initial_num:
    mov qword [r12], r8 ; sets initial state for the number
    mov r11, 1 ; sets op flag to "number set" state

    jmp .main_loop

.end_parse:
    mov rdx, r8
    neg rdx

    cmp r9b, 1
    cmove r8, rdx ; if sign flag is set, moves negated number to accumulator

    ; dispatch according to op flag

    cmp r11, 1
    jl .end_initial_num ; if flag is 0, initial number must be loaded
    je .syntax_error ; if equal to 1, op was not set and this is a syntax error

    cmp r11, 3
    jl .end_minus ; flag 2 is subtraction
    je .end_plus ; flag 3 is addition

    cmp r11, 5
    jl .end_multiplication ; flag 4 is multiplication
    je .end_division ; flag 5 is division
    ; otherwise op flag is invalid and there's a syntax error

    jmp .syntax_error

.end_initial_num:
    mov qword [r12], r8
    jmp .success

.end_multiplication:
    process_multiplication
    jmp .success

.end_division:
    process_division
    jmp .success

.end_minus:
    neg r8 ; negates accumulator
    ; execution fallthroughs

.end_plus:
    add qword [r12], r8 ; adds current number with accumulator
    ; execution fallthroughs

.success:
    mov rax, SUCCESS
    pop r12
    ret

.syntax_error:
    mov rax, SYNTAX_ERROR
    pop r12
    ret

.unknown_op:
    mov rax, UNKNOWN_OPERATION
    pop r12
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
