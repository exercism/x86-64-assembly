;
; Calculate the number of grains of wheat on a chessboard given that the number
; on each square doubles.
;
; Parameters:
;   rdi - square
;
; Returns:
;   rax - The number of grains on the square
;
section .text
global square
square:
    xor eax, eax     ; Set return value
    test edi, edi    ; Is square <= 0?
    jle .return      ; Yes => return 0
    cmp edi, 64      ; Is square > 64?
    jg .return       ; Yes => return 0
    dec edi
    bts rax, rdi     ; Set return value
.return:
    ret

;
; Calculate the total number of grains on the chessboard.
;
; Returns:
;   rax - The total number of grains on the board
;
global total
total:
    mov rax, -1      ; Set return value
    ret
