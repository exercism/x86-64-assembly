;
; Reverse a string.
;
; Parameters:
;   rdi - value
;
section .text
global reverse
reverse:
    xor eax, eax                 ; Set string length
    cmp byte [rdi], 0            ; Found NUL?
    je .return                   ; Yes => return
.len_loop_start:
    inc eax                      ; Increment string length
    cmp byte [rdi + rax], 0      ; Found NUL?
    jne .len_loop_start          ; No => next iteration

    xor ecx, ecx                 ; Start counter
    dec eax                      ; End counter
.rev_loop_start:
    mov dl, byte [rdi + rcx]     ; Save start byte
    mov r8b, byte [rdi + rax]    ; Save end byte
    mov byte [rdi + rax], dl     ; Set start byte to end
    mov byte [rdi + rcx], r8b    ; Set end byte to start
    inc ecx
    dec eax
    cmp ecx, eax                 ; Swapped every byte?
    jl .rev_loop_start           ; No => next iteration

.return:
    ret
