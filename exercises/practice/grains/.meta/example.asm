;
; Calculate the number of grains of wheat on a chessboard given that the number
; on each square doubles.
;
; Parameters:
;   rdi - number
; Returns:
;   rax - number of grains on the square
;
section .text
global square
square:
    xor eax, eax   ; Initialize number of grains

    test edi, edi  ; Compare input number with 0
    jle .return    ; If less or equal, return 0

    cmp edi, 64    ; Compare input number with max number of squares
    jg .return     ; If greater, return 0

    dec edi        ; Decrement input number to represent a bit-position
    bts rax, rdi   ; Return the number of grains on the square

.return:
    ret

;
; Calculate the total number of grains on the chessboard.
;
; Returns:
;   rax - total number of grains on the board
;
global total
total:
    mov rax, -1  ; Return the total number of grains on the board
    ret
