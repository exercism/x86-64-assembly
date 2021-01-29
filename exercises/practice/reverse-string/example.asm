;
; Reverse a string.
;
; Parameters:
;   rdi - str
;
section .text
global reverse
reverse:
    xor eax, eax               ; Initialize string length
    cmp byte [rdi], 0          ; Check if input string is empty
    je .return                 ; If empty, return
.len_loop_start:
    inc eax                    ; Increment string length
    cmp byte [rdi + rax], 0    ; See if we reached end of input string
    jne .len_loop_start        ; If chars remain, loop back

    xor ecx, ecx               ; Set start index to 0
    dec eax                    ; Set end index to string length - 1
.rev_loop_start:
    mov dl, byte [rdi + rcx]   ; Save char at start index
    mov sil, byte [rdi + rax]  ; Save char at end index
    mov byte [rdi + rax], dl   ; Set char at start to end
    mov byte [rdi + rcx], sil  ; Set char at end to start
    inc ecx                    ; Increment start index
    dec eax                    ; Decrement end index
    cmp ecx, eax               ; See if we swapped every char
    jl .rev_loop_start         ; If chars remain, loop back

.return:
    ret
