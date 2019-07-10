;
; Find the square of the sum of the first N natural numbers.
;
; Parameters:
;   rdi - number
;
; Returns:
;   rax - the sum
;
section .text
global square_of_sum
square_of_sum:
    xor eax, eax           ; Set the sum
    xor ecx, ecx           ; Set loop counter
.loop_start:
    add eax, ecx           ; Update the sum
    inc ecx
    cmp ecx, edi           ; Loop counter > number?
    jle .loop_start        ; No => next iteration
    imul eax               ; Square the sum
    ret

;
; Find the sum of the squares of the first N natural numbers.
;
; Parameters:
;   rdi - number
;
; Returns:
;   rax - the sum
;
global sum_of_squares
sum_of_squares:
    xor eax, eax           ; Set the sum
    xor ecx, ecx           ; Set loop counter
.loop_start:
    mov edx, ecx
    imul edx, edx
    add eax, edx           ; Update the sum
    inc ecx
    cmp ecx, edi           ; Loop counter > number?
    jle .loop_start        ; No => next iteration
    ret

;
; Find the difference between the square of the sum and the sum of the squares
; of the first N natural numbers.
;
; Parameters:
;   rdi - number
;
; Returns:
;   rax - the difference
;
global difference_of_squares
difference_of_squares:
    push rbx               ; Save rbx
    call sum_of_squares
    mov ebx, eax           ; Save the sum
    call square_of_sum
    sub eax, ebx           ; Calculate the difference
    pop rbx                ; Restore rbx
    ret
