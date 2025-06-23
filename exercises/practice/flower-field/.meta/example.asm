section .text
global annotate

; | Register | Usage        | Type    | Description                                   |
; | -------- | ------------ | ------- | --------------------------------------------- |
; | `rdi`    | input/output | address | null-terminated output string                 |
; | `rsi`    | input        | address | null-terminated input string                  |
; | `al`     | temporary    | byte    | input character                               |
; | `rbx`    | temporary    | address | pointer into input                            |
; | `rcx`    | temporary    | integer | number of adjacent flowers                    |
; | `rdx`    | temporary    | address | line length (including newline character)     |
; | `rbp`    | temporary    | address | location of input's null terminator           |
; | `r8`     | temporary    | address | previous row (or current for first row)       |
; | `r9`     | temporary    | address | current row                                   |
; | `r10`    | temporary    | address | next row (or current for last row)            |
; | `r11`    | temporary    | address | row of adjacent square                        |
; | `r12`    | temporary    | integer | previous column (or current for first column) |
; | `r13`    | temporary    | integer | current column                                |
; | `r14`    | temporary    | integer | next column (or current for last column)      |
; | `r15`    | temporary    | integer | column of adjacent square                     |

; extern void annotate(char *buffer, const char *garden);
annotate:
        push    rbx
        push    rbp
        push    r12
        push    r13
        push    r14
        push    r15
        cld
        mov     rbx, rsi
        mov     al, [rbx]               ; read first byte of garden
        test    al, al
        jz      .return

.find_newline:
        lodsb
        cmp     al, 0x0a
        jne     .find_newline

        mov     rdx, rsi
        mov     rsi, rbx
        sub     rdx, rbx                ; line length (including newline character)

.find_null:
        add     rbx, rdx                ; jump ahead by line length
        mov     al, [rbx]
        test    al, al
        jnz     .find_null

        mov     rbp, rbx                ; location of input's null terminator
        mov     r9, rsi
        mov     r10, rsi                ; start of first row

.next_row:
        xor     r13, r13                ; first column
        xor     r14, r14
        mov     r8, r9                  ; current row becomes previous row
        mov     r9, r10                 ; next row becomes current row

        mov     r10, r9
        add     r10, rdx                ; next row
        cmp     r10, rbp
        jne     .first_column

        mov     r10, r9                 ; last row

.first_column:
        cmp     rdx, 1
        je      .write_newline          ; jump ahead if rows contain no squares

.next_column:
        mov     r12, r13                ; current column becomes previous column
        mov     r13, r14                ; next column becomes current column
        mov     rax, r13
        add     r14, 2
        cmp     r14, rdx
        je      .update_next_column     ; no more columns?

        inc     rax

.update_next_column:
        mov     r14, rax                ; next column
        mov     al, [r9 + r13]          ; garden square
        cmp     al, '*'
        je     .write_square            ; jump ahead if we have reached a flower

        xor     rcx, rcx                ; number of adjacent flowers
        mov     r11, r8
        sub     r11, rdx

.adjacent_row:
        add     r11, rdx
        mov     r15, r12
        dec     r15

.adjacent_column:
        inc     r15
        mov     al, [r11 + r15]         ; adjacent square
        cmp     al, '*'
        jne     .next_adjacent

        inc     rcx                     ; update flower count

.next_adjacent:
        cmp     r15, r14
        jne     .adjacent_column

        cmp     r11, r10
        jne     .adjacent_row

        mov     al, ' '
        test    rcx, rcx
        jz      .write_square
        mov     al, '0'
        add     al, cl                  ; flower count, as ASCII digit

.write_square:
        stosb
        cmp     r13, r14
        jne     .next_column

.write_newline:
        mov     al, 0x0a
        stosb                           ; write '\n'
        cmp     r9, r10
        jne     .next_row

.return:
        xor     al, al
        stosb                           ; null terminator
        pop    r15
        pop    r14
        pop    r13
        pop    r12
        pop    rbp
        pop    rbx
        ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
