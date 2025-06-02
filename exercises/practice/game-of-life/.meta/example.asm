section .text
global tick

; extern void tick(uint64_t *buffer, const uint64_t *matrix, size_t row_count, size_t column_count);
tick:
        push    rbx                     ; preserve registers
        push    r12
        push    r13
        push    r14
        push    r15
        mov     rbx, rcx                ; number of columns
        cld

        test    rdx, rdx
        jz      .return                 ; 0 rows?

        lodsq                           ; read first matrix row into rax
        xor     r11, r11                ; previous row
        mov     r12, rax                ; current row

.outer:
        xor     r13, r13
        sub     rdx, 1                  ; remaining rows
        jz      .process_row

        lodsq                           ; read next matrix row into rax
        mov     r13, rax                ; next row

.process_row:
        xor     rax, rax                ; result row
        test    rcx, rcx
        jz      .write

        xor     r9, r9                  ; total for "previous" column across 3 rows
        mov     r10, r11
        and     r10, 1
        mov     r15, r13
        and     r15, 1
        add     r10, r15
        mov     r15, r12
        and     r15, 1                  ; first cell
        add     r10, r15                ; total for first column across 3 rows

.inner:
        ror     r11, 1                  ; previous row, rotated
        ror     r12, 1                  ; current row, rotated
        ror     r13, 1                  ; next row, rotated

        mov     r14, r15                ; current cell
        mov     r8, r9                  ; total for previous column across 3 rows
        mov     r9, r10                 ; total for current column across 3 rows

        mov     r10, r11
        and     r10, 1
        mov     r15, r13
        and     r15, 1
        add     r10, r15
        mov     r15, r12
        and     r15, 1                  ; next cell
        add     r10, r15                ; total for next column across 3 rows

        add     r8, r9
        add     r8, r10
        sub     r8, r14                 ; total of 8 neighbours
        or      r8, r14                 ; if current cell is alive, treat 2 alive neighbours as 3
        cmp     r8, 3
        jne     .rotate

        inc     rax

.rotate:
        ror     rax, 1                  ; rotate right
        loop    .inner                  ; remaining columns?

.write:
        mov     rcx, rbx                ; number of columns
        rol     rax, cl
        stosq                           ; write matrix row

        rol     r12, cl
        rol     r13, cl
        mov     r11, r12                ; previous row
        mov     r12, r13                ; current row
        test    rdx, rdx
        jnz     .outer                  ; remaining rows?

.return:
        pop    r15                      ; restore registers
        pop    r14
        pop    r13
        pop    r12
        pop    rbx
        ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
