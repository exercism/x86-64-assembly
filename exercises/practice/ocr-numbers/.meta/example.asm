default rel

success equ 0
invalid_lines equ 1
invalid_columns equ 2

section .data
    zero db " _ ", "| |", "|_|", "   "
    one db "   ", "  |", "  |", "   "
    two db " _ ", " _|", "|_ ", "   "
    three db " _ ", " _|", " _|", "   "
    four db "   ", "|_|", "  |", "   "
    five db " _ ", "|_ ", " _|", "   "
    six db " _ ", "|_ ", "|_|", "   "
    seven db " _ ", "  |", "  |", "   "
    eight db " _ ", "|_|", "|_|", "   "
    nine db " _ ", "|_|", " _|", "   "

section .text
global convert

convert:
    ; RDI - output buffer
    ; RSI - input array of strings
    ; RDX - num of elements in input array
    ; return is an error flag (int32_t) in RAX

    ; Algorithm is:
    ; Loops over lines, going forth and back inside each group
    ; A group is formed of 4 contiguous lines
    ;
    ; Inside each group, loops forth and back repeatedly,
    ; parsing 3 characters of each line at a time,
    ; and checking if the sequence of 12 characters form a digit
    ;
    ; If it doesn't constitute a digit, adds a '?'
    ; otherwise, adds the digit
    ;
    ; Once a digit is added, goes back to the first line in the group
    ; but 3 digits away, so as to check if the lines in the group still
    ; have digits remaining
    ;
    ; This process continues until end of all lines in a group
    ;
    ; Once a group is finished, adds a separator (',') and
    ; moves to next group, if any
    ;
    ; At the end, an extra separator was added and must be removed
    ; before appending NULL character
    ;
    ; If at any point one of the lines in a group finishes
    ; while another still has characters, this is an error of invalid_columns
    ;
    ; At the very beginning of the procedure, there's a check for invalid_lines,
    ; which asserts that the number of lines is divisible by 4

    test rdx, 3
    jnz .invalid_lines ; num of rows must be divisible by 4

    ; prologue
    push rbp
    mov rbp, rsp
    sub rsp, 28

    mov qword [rbp - 8], rsi
    sub qword [rbp - 8], 32
.main_loop:
    add qword [rbp - 8], 32 ; current group
    sub rdx, 4

    cmp rdx, 0
    jl .success ; reached end of input string successfully, no groups remaining

    mov rsi, qword [rbp - 8]
    mov qword [rbp - 16], -3
.sequence_loop:
    add qword [rbp - 16], 3 ; current digit start inside a group

    lea rsp, [rbp - 28] ; sequence for digits will be saved in the stack for comparison
    xor r11, r11 ; flag for end of line in rows inside group
    mov r8, -1
.digit_loop:
    inc r8 ; current row inside a digit

    cmp r8, 4
    je .end_digit ; last row was parsed, entire digit string is in the stack

    mov r9, -1
.row_loop:
    inc r9 ; current char inside current row

    cmp r9, 3
    je .digit_loop ; last char of the row was parsed, go to next row

    lea r10, [rsi + r8*8] ; RSI is a pointer to an array of char pointers
    mov r10, qword [r10]
    add r10, qword [rbp - 16]

    mov al, byte [r10 + r9]

    test al, al
    jz .check_end ; NULL char, must update end line flag

    test r11, r11
    jnz .invalid_columns ; end line flag > 0 -> an empty line was found in the group
                         ; if current char is not NULL, then current line is non-finishing
                         ; and so the column is invalid (all lines must finish at the same time)

    mov byte [rsp], al ; inserts char in the stack
    inc rsp

    jmp .row_loop

.check_end:
    inc r11 ; updates flag for end of line

    jmp .digit_loop

.end_digit:
    cmp r11, 4
    je .add_comma ; if all four lines in the group finished, group is valid
                  ; must insert separator and checks next group

    test r11, r11
    jnz .invalid_columns ; if end of line flag is non-zero
                         ; and num of end lines different than 4
                         ; group is invalid

    mov r10, rdi
    mov r11, rsi

    mov r8, -1
.find_digit:
    inc r8 ; current digit string

    cmp r8, 10
    je .question ; last digit is 9,
                 ; if no digit was found, insert question mark

    lea rdi, [rbp - 28]
    lea rsi, [zero]
    imul r9, r8, 12 ; each digit string has size 12
    add rsi, r9

    mov rcx, 12 ; each digit string has size 12
    repe cmpsb
    jne .find_digit ; if no match was found, check next digit

    mov rdi, r10
    mov rsi, r11

    lea rax, [r8 + '0'] ; found a match which corresponds to the digit at r8
    stosb ; stores digit

    jmp .sequence_loop ; checks next digit inside group
.question:
    mov rdi, r10
    mov rsi, r11

    mov al, '?' ; no digit was found, insert question mark
    stosb

    jmp .sequence_loop ; checks next digit inside group

.add_comma:
    mov al, ',' ; a comma separates numbers of different groups
    stosb

    jmp .main_loop

.success:
    dec rdi ; an extra comma was inserted at the end of the last group
            ; must go back to insert NULL

    mov al, 0 ; insert NULL
    stosb

    mov rax, success ; flags success

    ; epilogue

    mov rsp, rbp
    pop rbp
    ret

.invalid_columns:
    mov rax, invalid_columns ; flags invalid columns

    ; epilogue

    mov rsp, rbp
    pop rbp
    ret

.invalid_lines:
    mov rax, invalid_lines ; flags invalid lines
    ; no epilogue needed, since check occurs before prologue

    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
