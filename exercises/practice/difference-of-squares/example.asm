;
; Find the square of the sum of the first N natural numbers.
;
; Parameters:
;   rdi - number
; Returns:
;   rax - square of the sum
;
section .text
global square_of_sum
square_of_sum:
    xor eax, eax     ; Initialize sum

    mov ecx, 1       ; Set current number
.loop_start:
    add eax, ecx     ; Add current number to sum
    inc ecx          ; Increment current number
    cmp ecx, edi     ; See if we reached the last number
    jle .loop_start  ; If numbers remain, loop back
    imul eax         ; Square the sum
    ret

;
; Find the sum of the squares of the first N natural numbers.
;
; Parameters:
;   rdi - number
; Returns:
;   rax - sum of the squares
;
global sum_of_squares
sum_of_squares:
    xor eax, eax     ; Initialize sum

    mov ecx, 1       ; Set current number
.loop_start:
    mov edx, ecx     ; Save current number
    imul edx, edx    ; Square it
    add eax, edx     ; Add result to sum
    inc ecx          ; Increment current number
    cmp ecx, edi     ; See if we reached the last number
    jle .loop_start  ; If numbers remain, loop back
    ret

;
; Find the difference between the square of the sum and the sum of the squares
; of the first N natural numbers.
;
; Parameters:
;   rdi - number
; Returns:
;   rax - the difference between the square of the sum and the sum of the
;         squares
;
global difference_of_squares
difference_of_squares:
    push rbx      ; Save caller's rbx
    call sum_of_squares
    mov ebx, eax  ; Save result
    call square_of_sum
    sub eax, ebx  ; Calculate the difference
    pop rbx       ; Restore caller's rbx
    ret
