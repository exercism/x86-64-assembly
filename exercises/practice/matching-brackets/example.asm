;
; Make sure the brackets and braces all match.
;
; Parameters:
;   rdi - str
; Returns:
;   rax - true if paired, else false
;
section .text
global is_paired
is_paired:
    push rbp
    mov rbp, rsp

    xor eax, eax           ; Initialize return value

    cmp byte [rdi], 0      ; Check if input string is empty
    je .loop_end           ; If empty, skip loop
.loop_start:
    movzx ecx, byte [rdi]  ; Read char from input string
    cmp cl, '['
    je .opening
    cmp cl, '{'
    je .opening
    cmp cl, '('
    jne .not_opening
.opening:
    push rcx               ; Push opening bracket or brace on stack
    jmp .next
.not_opening:
    cmp cl, ']'
    je .bracket
    cmp cl, '}'
    je .brace
    cmp cl, ')'
    jne .next
    cmp rsp, rbp           ; Check if stack is empty
    je .return             ; If empty, return false
    pop rcx                ; Pop the stack
    cmp cl, '('            ; Check if matching paren
    jne .return            ; If not, return false
    jmp .next
.bracket:
    cmp rsp, rbp           ; Check if stack is empty
    je .return             ; If empty, return false
    pop rcx                ; Pop the stack
    cmp cl, '['            ; Check if matching bracket
    jne .return            ; If not, return false
    jmp .next
.brace:
    cmp rsp, rbp           ; Check if stack is empty
    je .return             ; If empty, return false
    pop rcx                ; Pop the stack
    cmp cl, '{'            ; Check if matching brace
    jne .return            ; If not, return false
.next:
    inc rdi                ; Advance input string to next char
    cmp byte [rdi], 0      ; See if we reached the end
    jne .loop_start        ; If chars remain, loop back

.loop_end:
    cmp rsp, rbp           ; Check if stack is empty
    sete al                ; If empty, return true
.return:
    leave
    ret
