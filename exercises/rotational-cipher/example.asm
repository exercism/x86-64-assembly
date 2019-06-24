;
; Create an implementation of the rotational cipher, also sometimes called the
; Caesar cipher.
;
; Parameters:
;   rdi - text
;   rsi - shift_key
;   rdx - buffer
;
section .text
global rotate
rotate:
    mov rcx, rdx             ; Save buffer

    cmp byte [rdi], 0        ; Found NUL?
    je .loop_end             ; Yes => skip loop
.loop_start:
    movzx eax, byte [rdi]    ; Fetch a byte
    mov edx, eax             ; Save byte

    lea r8d, [rax - 'a']
    cmp r8d, 26              ; Is lowercase?
    jae .is_upper            ; No => check if uppercase
    mov r8d, 'a'
    jmp .rot
.is_upper:
    lea r8d, [rax - 'A']
    cmp r8d, 26              ; Is uppercase?
    jae .skip                ; No => skip
    mov r8d, 'A'
.rot:
    sub eax, r8d             ; Subtract 'a' or 'A'
    add eax, esi             ; Add shift_key
    cdq
    mov r9d, 26
    idiv r9d                 ; Divide by 26
    add edx, r8d             ; Add 'a' or 'A' to remainder
.skip:
    mov byte [rcx], dl       ; Store result in buffer
    inc rcx
    inc rdi
    cmp byte [rdi], 0        ; Found NUL?
    jne .loop_start          ; No => next iteration

.loop_end:
    mov byte [rcx], 0        ; Null-terminate buffer
    ret
