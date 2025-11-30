section .text

global transpose
transpose:
    xor eax, eax       ; length of largest string
    test rdx, rdx
    jz .ret

    ; each col in a transposed matrix should be at least as large as any following col
    ; if a col is smaller than a subsequent col, padding space must be added

    ; prologue
    push rbx
    sub rsp, 32              ; map for length of each row in transposed matrix

    pxor xmm1, xmm1          ; xmm1 is all 0s
    movdqu [rsp], xmm1
    movdqu [rsp + 16], xmm1  ; map is now cleared

    xor r8d, r8d
.find_longest_string_length:
    mov rbx, qword [rsi + 8*r8]
    xor r9d, r9d
.find_length:
    pcmpistri xmm1, [rbx + r9], 0b00_00_10_00   ; finds the index of first char equal to its corresponding byte in xmm1, and returns it in ecx
                                                ; since xmm1 is empty, it returns the index of NUL, or 16 if NUL was not found
    add r9d, ecx
    cmp ecx, 16
    jz .find_length

    cmp r9d, eax
    cmova eax, r9d                              ; eax is now the length of the largest row

    xor r10d, r10d
.fill_map:
    movzx r11d, byte [rsp + r10]
    cmp r11d, r9d
    cmovb r11d, r9d                            ; if length of a previous row is smaller, it should be equal to length for current row
    mov byte [rsp + r10], r11b

    inc r10d
    cmp r10d, r8d
    jbe .fill_map

    inc r8
    cmp r8, rdx
    jne .find_longest_string_length

    xor ecx, ecx
    xor r8d, r8d             ; col
    xor r10d, r10d           ; bitmap for end of row
.transpose:
    xor r11d, r11d           ; row
.inner:
    bt r10, r11
    jc .ended                ; row already ended, should add either ' ' or NUL

    mov rbx, qword [rsi + 8*r11]
    mov cl, byte [rbx + r8]
    test cl, cl
    jnz .store_letter        ; still has letter

    bts r10, r11             ; otherwise, flag end of row in bitmap
.ended:
    xor ecx, ecx             ; row has ended, add NUL by default
    mov ebx, ' '
    cmp r8b, byte [rsp + r11]
    cmovb ecx, ebx           ; if row has ended and col index is lesser than mapped length, pad
.store_letter:
    mov ebx, r8d             ; col becomes row in transposed matrix
    shl ebx, 5               ; each row in buffer is 32 bytes long
    lea rbx, [rdi + rbx]
    mov byte [rbx + r11], cl ; add value to buffer
.continue:
    inc r11
    cmp r11, rdx
    jb .inner

    mov byte [rbx + r11], 0  ; end of col (corresponding to row in transposed), add NUL

    inc r8
    cmp r8, rax
    jbe .transpose

    ; epilogue

    add rsp, 32
    pop rbx
.ret:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
