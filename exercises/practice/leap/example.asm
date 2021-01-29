;
; Given a year, report if it is a leap year.
;
; Parameters:
;   rdi - year
; Returns:
;   rax - true if leap year, else false
;
section .text
global leap_year
leap_year:
    mov eax, edi       ; Set dividend to year
    cdq                ; Sign-extend eax into edx
    mov ecx, 4         ; Set divisor
    idiv ecx
    test edx, edx      ; Check if year is divisible by 4
    jne .return_false  ; If not, return false

    mov eax, edi       ; Set dividend to year
    cdq                ; Sign-extend eax into edx
    mov ecx, 100       ; Set divisor
    idiv ecx
    test edx, edx      ; Check if year is divisible by 100
    jne .return_true   ; If not, return true

    mov eax, edi       ; Set dividend to year
    cdq                ; Sign-extend eax into edx
    mov ecx, 400       ; Set divisor
    idiv ecx
    test edx, edx      ; Check if year is divisible by 400
    je .return_true    ; If so, return true

.return_false:
    xor eax, eax       ; Return false
    ret

.return_true:
    mov eax, 1         ; Return true
    ret
