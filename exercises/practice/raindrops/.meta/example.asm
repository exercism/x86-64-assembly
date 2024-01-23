default rel

section .rodata
pling: db "Pling"
pling_len: equ $ - pling

plang: db "Plang"
plang_len: equ $ - plang

plong: db "Plong"
plong_len: equ $ - plong

;
; Convert a number into a string that contains raindrop sounds.
;
; Parameters:
;   rdi - number
;   rsi - buffer
;
section .text
global convert
convert:
    push rbp
    mov rbp, rsp

    mov r8d, edi             ; Save number
    mov r9, rsi              ; Save buffer
    mov rdi, rsi             ; Set destination to buffer

    mov eax, r8d             ; Set dividend to number
    cdq                      ; Sign-extend eax into edx
    mov ecx, 3               ; Set divisor
    idiv ecx
    test edx, edx            ; Check if number is divisible by 3
    jne .plang               ; If not, check for "Plang"

    lea rsi, [pling]         ; Set source
    mov rcx, pling_len       ; Set string length
    rep movsb                ; Append string to buffer

.plang:
    mov eax, r8d             ; Set dividend to number
    cdq                      ; Sign-extend eax into edx
    mov ecx, 5               ; Set divisor
    idiv ecx
    test edx, edx            ; Check if number is divisible by 5
    jne .plong               ; If not, check for "Plong"

    lea rsi, [plang]         ; Set source
    mov rcx, plang_len       ; Set string length
    rep movsb                ; Append string to buffer

.plong:
    mov eax, r8d             ; Set dividend to number
    cdq                      ; Sign-extend eax into edx
    mov ecx, 7               ; Set divisor
    idiv ecx
    test edx, edx            ; Check if number is divisible by 7
    jne .sounds_done         ; If not, stop checking for factors

    lea rsi, [plong]         ; Set source
    mov rcx, plong_len       ; Set string length
    rep movsb                ; Append string to buffer

.sounds_done:
    cmp rdi, r9              ; Check if buffer is empty
    jne .return              ; If not empty, return

    mov eax, r8d             ; Set dividend to number
    mov r10d, 10             ; Set divisor
    xor ecx, ecx             ; Initialize digit count

.digit_loop_start:
    cdq                      ; Sign-extend eax into edx
    idiv r10d

    add dl, '0'              ; Convert value to digit
    dec rsp                  ; Push digit on stack
    mov byte [rsp], dl
    inc rcx                  ; Increment digit count

    test eax, eax            ; Check if number is zero
    jne .digit_loop_start    ; If not, loop back

    mov rsi, rsp             ; Set source
    rep movsb                ; Append digits to buffer

.return:
    mov byte [rdi], 0        ; Null-terminate buffer
    leave
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
