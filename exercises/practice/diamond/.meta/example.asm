BUFFER_SIZE equ 52

section .text
global rows

%macro add_A_line 0
    mov rax, ' '
    mov rcx, r9
    rep stosb

    mov rax, 'A'
    stosb

    mov rax, ' '
    mov rcx, r9
    rep stosb

    mov rax, 0
    stosb
%endmacro

%macro add_two_letter_line 0
    mov rax, ' '
    mov rcx, r10
    rep stosb

    mov rax, rdx
    stosb

    mov rax, ' '
    mov rcx, r11
    rep stosb

    mov rax, rdx
    stosb

    mov rax, ' '
    mov rcx, r10
    rep stosb

    mov rax, 0
    stosb
%endmacro

%macro update_buffer_pointer 0
    add r12, BUFFER_SIZE
    mov rdi, r12
%endmacro

rows:
    ; RDI - pointer to the output array of char buffers, where to add strings
    ; SIL - letter
    ; return is the size of the output buffer, in RAX

    ; Algorithm is:
    ; 1- Gets size of line, which is also the size of ouput buffer, since buffer is a squared matrix;
    ; 2- Gets num of padding spaces before and after the first letter in the row, which is half size of the line;
    ; 3- Gets num of padding spaces between letters in the row, which starts at 1 in letter 'B';
    ; 4- Adds first row, with letter 'A';
    ; 5- If size > 1, iterates increasing letter, adjusting spaces for padding, until reaching half the matrix;
    ; 6- Then, iterates decreasing letter up to letter 'B'
    ; 7- Inserts last row, with letter 'A';
    ; 8- Moves size of buffer to RAX and returns;

    push r12
    mov r12, rdi

    xor r8, r8
    mov r8b, sil
    sub r8b, 'A'
    shl r8b, 1
    inc r8b ; size of each row and of output buffer

    mov r9, r8
    shr r9, 1 ; num of padding before and after letters
              ; also marks end of increasing sequence and start of decrease

    add_A_line ; adds first line

    cmp r8, 1
    je .return

    mov r10, r9
    mov rdx, 'A'
    mov r11, -1
.increase_letter:
    dec r10
    inc rdx
    add r11, 2

    update_buffer_pointer
    add_two_letter_line

    cmp r10, 0
    jg .increase_letter

.decrease_letter:
    cmp rdx, 'B'
    je .add_last_line

    inc r10
    dec rdx
    sub r11, 2

    update_buffer_pointer
    add_two_letter_line

    jmp .decrease_letter

.add_last_line:
    update_buffer_pointer
    add_A_line

.return:
    mov rax, r8
    pop r12
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
