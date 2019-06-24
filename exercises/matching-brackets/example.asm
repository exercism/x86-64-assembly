;
; Make sure the brackets and braces all match.
;
; Parameters:
;   rdi - value
;
; Returns:
;   rax - 1 if paired, else 0
;
section .text
global is_paired
is_paired:
    push rbp
    mov rbp, rsp

    xor eax, eax             ; Set return value

    cmp byte [rdi], 0        ; Found NUL?
    je .loop_end             ; Yes => skip loop
.loop_start:
    movzx ecx, byte [rdi]    ; Fetch a byte
    cmp cl, '['
    je .opening
    cmp cl, '{'
    je .opening
    cmp cl, '('
    jne .not_opening
.opening:
    push rcx                 ; Push opening bracket or brace
    jmp .skip
.not_opening:
    cmp cl, ']'
    je .bracket
    cmp cl, '}'
    je .brace
    cmp cl, ')'
    jne .skip
    cmp rsp, rbp             ; Is stack empty?
    je .return               ; Yes => return false
    pop rdx
    cmp dl, '('              ; Found matching paren?
    jne .return              ; No => return false
    jmp .skip
.bracket:
    cmp rsp, rbp             ; Is stack empty?
    je .return               ; Yes => return false
    pop rdx
    cmp dl, '['              ; Found matching bracket?
    jne .return              ; No => return false
    jmp .skip
.brace:
    cmp rsp, rbp             ; Is stack empty?
    je .return               ; Yes => return false
    pop rdx
    cmp dl, '{'              ; Found matching brace?
    jne .return              ; No => return false
.skip:
    inc rdi
    cmp byte [rdi], 0        ; Found NUL?
    jne .loop_start          ; No => next iteration

.loop_end:
    cmp rsp, rbp             ; Is stack empty?
    sete al                  ; Yes => return true
.return:
    leave
    ret
