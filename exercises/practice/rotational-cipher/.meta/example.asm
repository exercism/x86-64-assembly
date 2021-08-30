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
    mov rcx, rdx           ; Save buffer

    cmp byte [rdi], 0      ; Check if text is an empty string
    je .loop_end           ; If empty, skip loop
.loop_start:
    movzx eax, byte [rdi]  ; Read char from text
    mov edx, eax           ; Save char
    lea r8d, [rax - 'a']
    cmp r8d, 26            ; Check if char is lowercase
    jae .is_upper          ; If not, check if uppercase
    mov r8d, 'a'           ; Save 'a'
    jmp .rot
.is_upper:
    lea r8d, [rax - 'A']
    cmp r8d, 26            ; Check if char is uppercase
    jae .next              ; If not, process next char
    mov r8d, 'A'           ; Save 'A'
.rot:
    sub eax, r8d           ; Subtract 'a' or 'A' from char
    add eax, esi           ; Add shift_key
    cdq                    ; Sign-extend eax into edx
    mov r9d, 26
    idiv r9d               ; Divide by 26
    add edx, r8d           ; Add 'a' or 'A' to remainder
.next:
    mov byte [rcx], dl     ; Store result in buffer
    inc rcx                ; Advance buffer to next char
    inc rdi                ; Advance text to next char
    cmp byte [rdi], 0      ; See if we reached end of text
    jne .loop_start        ; If chars remain, loop back

.loop_end:
    mov byte [rcx], 0      ; Null-terminate buffer
    ret
