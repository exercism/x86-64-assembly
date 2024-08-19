section .text
global rows
rows:
    mov r8, rdi                         ; dest, i,e. start of output
    mov r9, rsi                         ; count, i.e. number of rows
    shl r9, 3                           ; final row length in bytes
    cld                                 ; Each lodsq/stosq will increment rsi/rdi
    xor rcx, rcx                        ; initialize row length
    jmp .check_if_done

.next_row:
    mov r10, rdi                        ; start of current row
    mov r11, rdi
    add r11, rcx                        ; end of current row
    mov rdx, 0
    jmp .check_if_last_column

.next_column:
    lodsq                               ; read from previous row
    add rax, rdx                        ; sum two values from previous row
    stosq
    sub rax, rdx
    mov rdx, rax

.check_if_last_column:
    cmp rdi, r11
    jne .next_column

    mov rax, 1
    stosq                               ; store 1
    mov rsi, r10                        ; start of most recent row
    add rcx, 8                          ; increment row length

.check_if_done:
    cmp rcx, r9                         ; compare row lengths
    jne .next_row

.done:
    mov rax, rdi
    sub rax, r8                         ; subtract start of output
    shr rax, 3                          ; convert to number of qwords
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
