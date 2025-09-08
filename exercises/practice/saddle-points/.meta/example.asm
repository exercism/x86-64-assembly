section .text

global saddle_points

saddle_points:
    ; RDI - output buffer of a struct of 2 uint64_t,
    ; representing 1-indexed positions for saddle points
    ; RSI - input array of a struct of one counter (uint64_t)
    ; and one array of 15 int64_t
    ; RDX - num of elements in input array
    ; return is size of output buffer in RAX

    ; A saddle point is the largest in the row
    ; and the smallest in the column

    ; The algorithm is:
    ; 1- Loops over all rows, checking for the max element, storing its value in an accumulator,
    ; and its indexes in the stack;
    ; 2- For each index saved in the stack, loops over all elements in the corresponding column,
    ; to check if the accumulator is the lesser value;
    ; 3- If the indexes correspond to a saddle point, stores them in the output buffer and increments counter;
    ;
    ; Points of attention:
    ; A- All indexes start at 1 (not 0);
    ; B- The tests expect indexes sorted by row index and, in equal rows, by col index,
    ; both in ascending order.
    ;
    ; Because of that, the outer loop proceeds in ascending order of row index,
    ; so elements in a lesser row index are stored before;
    ;
    ; Whenever checking individual elements of a row, the loop proceeds from end to start,
    ; so greater column indexes are stored first in the stack;
    ;
    ; As the stack grows backward, column indexes are consumed in ascending order of the stack,
    ; which means the column indexes stored last (the lesser indexes) are consumed first.
    ;
    ; This ensures a sorted order, as expected by the tests

    xor rax, rax ; counter

    ; NULL array, may return
    cmp rdx, 0
    je .end

    ; prologue
    push r12
    push r13
    push rbp
    mov rbp, rsp

    mov r8, -1 ; row
.outer:
    inc r8

    cmp r8, rdx
    je .end_outer ; end of input array

    lea r11, [r8*8]
    shl r11, 4 ; each row has 128 bytes:
               ; -> 8 bytes for counter at the beginning
               ; -> 8 * 15 bytes for the buffer

    mov rcx, qword [rsi + r11] ; length of row
    lea r9, [rsi + r11 + 8] ; beginning of row buffer

    cmp rcx, 0
    je .outer ; if row empty, continue outer loop
    ; otherwise proceed with algorithm

    xor r10, r10 ; accumulator
.check_row:
    mov r11, qword [r9 + 8*rcx - 8]

    cmp r11, r10
    jl .continue_check_row
    jg .reset_accumulator ; element is greater than current current max, stack must be reset
    ; element is equal to current max, so its col index is stored

    sub rsp, 8
    mov qword [rsp], rcx ; stores col index, starting at 1
    jmp .continue_check_row

.reset_accumulator:
    mov rsp, rbp
    sub rsp, 8
    mov qword [rsp], rcx
    mov r10, r11

.continue_check_row:
    loop .check_row

    mov r11, rbp
    sub r11, rsp
    shr r11, 3  ; length of array of indexes

    mov r9, -1 ; counter for array of indexes
.check_col:
    inc r9

    cmp r9, r11
    je .prepare_outer ; end of array, reset stack for new iteration of outer loop

    mov r12, qword [rsp + 8*r9] ; col index
    mov rcx, rdx ; num of rows
.check_col_loop:
    lea r13, [8*rcx - 8]
    shl r13, 4
    add r13, rsi ; r13 now points to beginning of row struct

    lea r13, [r13 + 8*r12] ; as each element is 8-bytes long, element in the col is in
                           ; start + 8*col
                           ; however, r12 is 1-indexed, so 8 must be subtracted from this:
                           ; start + 8*col - 8
                           ; but, there's a counter at the beginning of the row, so 8 must be added
                           ; Result is, finally: start + 8*col - 8 + 8 = start + 8*col

    cmp qword [r13], r10
    jl .check_col ; if element in the column is lesser than accumulator, no index is a saddle point

    loop .check_col_loop

    ; if no lesser element was found, stores indexes and increments counter

    inc rax ; increments counter

    mov qword [rdi], r8 ; r8 is row index, starting at 0
    inc qword [rdi] ; now row index is correctly 1-indexed

    mov qword [rdi + 8], r12 ; r12 is col index, starting at 1
    add rdi, 16 ; increments RDI to next struct

    jmp .check_col ; checks if next col index is a saddle point

.prepare_outer:
    mov rsp, rbp ; resets stack for next iteration
    jmp .outer

.end_outer:
    ; epilogue
    mov rsp, rbp
    pop rbp
    pop r13
    pop r12
.end:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
