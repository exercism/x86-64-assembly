default rel

section .rodata
m_numeral: db "M", 0
cm_numeral: db "CM", 0
d_numeral: db "D", 0
cd_numeral: db "CD", 0
c_numeral: db "C", 0
xc_numeral: db "XC", 0
l_numeral: db "L", 0
xl_numeral: db "XL", 0
x_numeral: db "X", 0
ix_numeral: db "IX", 0
v_numeral: db "V", 0
iv_numeral: db "IV", 0
i_numeral: db "I", 0

section .data
numeral_array:
dd 1000
dq m_numeral
dd 900
dq cm_numeral
dd 500
dq d_numeral
dd 400
dq cd_numeral
dd 100
dq c_numeral
dd 90
dq xc_numeral
dd 50
dq l_numeral
dd 40
dq xl_numeral
dd 10
dq x_numeral
dd 9
dq ix_numeral
dd 5
dq v_numeral
dd 4
dq iv_numeral
dd 1
dq i_numeral
dd 0  ; Sentinel value to indicate end of array
dq 0

;
; Convert a number to its representation as Roman Numerals.
;
; Parameters:
;   rdi - number
;   rsi - buffer
;
section .text
global roman
roman:
    lea rax, [numeral_array]      ; Load numeral array
    xor rcx, rcx                  ; Initialize array index

.arr_loop_start:
    mov r8d, dword [rax + rcx]    ; Read value from array
    test r8d, r8d                 ; See if we reached end of array
    je .arr_loop_end              ; If so, exit loop

.num_loop_start:
    cmp edi, r8d                  ; Compare with value from array
    jl .num_loop_end              ; If less, exit loop
    mov r9, [rax + rcx + 4]       ; Read numeral from array

.str_loop_start:
    mov dl, byte [r9]             ; Read char from numeral
    test dl, dl                   ; See if we reached end of numeral
    je .str_loop_end              ; If so, exit loop
    mov byte [rsi], dl            ; Write char to buffer
    inc r9                        ; Advance numeral to next char
    inc rsi                       ; Advance buffer to next char
    jmp .str_loop_start           ; Loop back

.str_loop_end:
    sub edi, r8d                  ; Subtract converted value from number
    jmp .num_loop_start           ; Loop back

.num_loop_end:
    add rcx, 12                   ; Increment array index
    jmp .arr_loop_start           ; Loop back

.arr_loop_end:
    mov byte [rsi], 0             ; Null-terminate buffer
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
