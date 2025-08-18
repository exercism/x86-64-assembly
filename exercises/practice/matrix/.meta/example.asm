section .text
global row
global column

%macro store_num 0
    inc r8 ; increments counter

    mov eax, r10d ; eax now holds number

    xor rdx, rdx
    mov r10d, 10
    div r10d ; divide by 10 to account for an extra multiplication in accumulating loop

    cmp r9b, 1
    jne %%store_num ; if sign flag is not set, proceed with storing it
    ; otherwise negate num before storing it

    neg eax

%%store_num:
    stosd ; store number in buffer
%endmacro

; size_t row(int32_t *buffer, const char *input, size_t index);
row:
	; rdi - output int32_t buffer
    ; rsi - input string
    ; rdx - index from the row to be extracted as a uint64_t
    ; return is the size of buffer in rax

    ; The algorithm is:
    ;
    ; The input string is looped over until rdx is 1.
    ; Each newline marks the end of a row and decreases rdx by 1.
    ;
    ; Then the desired row is looped over and each number is accumulated in r10.
    ; Each space marks the end of a num
    ; and a newline or a NULL marks the end of the entire row.
    ;
    ; At the beginning of each number, there's a check for the sign char.
    ;
    ; At the end of each number and of the row, the accumulator is adjusted for sign
    ; and divided by 10 to account for an extra multiplication in the loop
    ; then it's stored in the output buffer.
    ; There's also a counter for the numbers, for returning at the end.
    ;
    ; If it's not the end of the row, the loop continues
    ; It it is, the counter is moved to rax

    xor r8, r8 ; counter
.row_main_loop:
    cmp rdx, 1 ; matrix is 1-indexed
    je .row_copy ; found desired row

.find_next_row:
    lodsb

    cmp al, 10 ; newline
    jne .find_next_row

    dec rdx ; one row less
    jmp .row_main_loop

.row_copy:
    xor r9, r9
    xor r10, r10 ; accumulator for the number
    xor rax, rax
.check_sign:
    lodsb
    cmp al, '-'
    sete r9b ; sign flag
    je .prepare_next_iteration
.row_copy_loop:
    cmp al, 10
    je .end_copy ; newline marks end of the row

    cmp al, 0
    je .end_copy ; NULL marks end of the row

    cmp al, ' '
    je .end_num ; space marks end of the num
    ; otherwise the number continues

    sub al, '0' ; fromEnum

    add r10, rax ; accumulates
    imul r10, r10, 10 ; multiplies by 10 to accumulate in next iteration
                      ; accumulator must be adjusted for an extra multiplication at the end

.prepare_next_iteration:
    lodsb
    jmp .row_copy_loop

.end_num:
    store_num ; macro
    jmp .row_copy

.end_copy:
    store_num ; macro
    mov rax, r8 ; moves counter to rax for returning

	ret

; size_t column(int32_t *buffer, const char *input, size_t index);
column:
	; rdi - output int32_t buffer
    ; rsi - input string
    ; rdx - index from the column to be extracted as a uint64_t
    ; return is the size of buffer in rax

    ; The algorithm is:
    ; The input string is looped over until rdx is 1, which marks the desired column.
    ;
    ; As this process is repeated for each new element, rdx is saved in r11 beforehand.
    ;
    ; Each space marks the end of a number and decreases rdx by 1,
    ; the NULL char marks the end of the string and returns the function.
    ;
    ; Once found the element in the desired column, it's looped over and accumulated in r10.
    ; At the beginning of each number, there's a check for the sign char.
    ;
    ; At the end of each number, the accumulator is adjusted for sign
    ; and divided by 10 to account for an extra multiplication in the loop
    ; then it's stored in the output buffer.
    ; There's also a counter for the numbers, for returning at the end.
    ;
    ; A space, a newline or NULL marks the end of a number.
    ; In case of a NULL, the number is stored and the function returns right away.
    ; In the other cases, the number is stored and rdx is restored to loop over the input string
    ; in search of the next desired element.

    xor r8, r8 ; counter
    mov r11, rdx
.column_main_loop:
    cmp rdx, 1 ; matrix is 1-indexed
    je .elem_copy ; found desired column

.find_next_elem:
    lodsb

    cmp al, 0
    je .return ; NULL marks end of input and function returns right away

    cmp al, ' ' ; num separator
    jne .find_next_elem

    dec rdx ; decreases counter until desired column
    jmp .column_main_loop

.elem_copy:
    xor r10, r10 ; accumulator for the number
    xor rax, rax
.check_sign:
    lodsb
    cmp al, '-'
    sete r9b ; sign flag
    je .prepare_next_iteration
.elem_copy_loop:
    cmp al, 10
    je .end_num ; newline marks end of the number

    cmp al, ' '
    je .end_num ; space marks end of the number

    cmp al, 0
    je .end_copy ; NULL marks end of the string

    sub al, '0' ; fromEnum

    add r10, rax ; accumulates
    imul r10, r10, 10 ; multiplies by 10 to accumulate in next iteration
                      ; accumulator must be adjusted for an extra multiplication at the end

.prepare_next_iteration:
    lodsb
    jmp .elem_copy_loop

.end_num:
    ; here it's end of current number, but not of the string

    store_num ; macro

    mov rdx, r11 ; as the string doesn't end here, there might be another row
    jmp .column_main_loop

.end_copy:
    ; here it's end of the number and of the input string
    ; so the number must be stored and the function should return soon after

    store_num ; macro

.return:
    mov rax, r8 ; moves counter to rax for returning

	ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
