;
; Given a year, report if it is a leap year.
;
; Parameters:
;   rdi - year
;
; Returns:
;   rax - 1 if leap year, else 0
;
section .text
global leap_year
leap_year:
    mov eax, edi                ; Set dividend to year
    cdq                         ; Sign-extend eax into edx
    mov ecx, 4                  ; Set divisor
    idiv ecx
    test edx, edx               ; Is remainder 0?
    jne .is_divisible_by_400    ; No => check if divisible by 400

    mov eax, edi                ; Set dividend to year
    cdq                         ; Sign-extend eax into edx
    mov ecx, 100                ; Set divisor
    idiv ecx
    test edx, edx               ; Is remainder 0?
    jne .return_true            ; No => return true

.is_divisible_by_400:
    mov eax, edi                ; Set dividend to year
    cdq                         ; Sign-extend eax into edx
    mov ecx, 400                ; Set divisor
    idiv ecx
    test edx, edx               ; Is remainder 0?
    je .return_true             ; Yes => return true

    xor eax, eax                ; Set return value
    ret

.return_true:
    mov eax, 1                  ; Set return value
    ret
