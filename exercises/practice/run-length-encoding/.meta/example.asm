section .text
global encode, decode


;   rdi - buffer
;   rsi - string
;
;   r8b - previous byte
;   r9b - current byte
;   r10 - 10
;   r11 - input pointer at byte after start of run
encode:
    mov r8b, byte [rsi]                 ; read first byte from input string
    inc rsi
    mov r11, rsi
    mov r10, 10
    test r8b, r8b                       ; check if we have reached null terminator
    jz done

.encode_in:
    mov r9b, byte [rsi]                 ; read next byte from input string
    inc rsi
    cmp r9b, r8b
    jz .encode_in                       ; repeat while run continues

    mov rax, rsi
    sub rax, r11                        ; length of run
    cmp rax, 1
    jz .encode_out

    mov r11, rdi                        ; address where first digit will be written

.digit_out:
    xor rdx, rdx
    div r10                             ; divide by 10
    add dl, '0'                         ; convert remainder from number 0..9 to ASCII digit '0'..'9'
    mov byte [rdi], dl                  ; write digit to output string
    inc rdi
    test rax, rax                       ; check if quotient is 0
    jnz .digit_out

    mov rcx, rdi
    dec rcx                             ; address where last digit was written

.reverse:
    mov al, byte [r11]
    mov dl, byte [rcx]
    mov byte [rcx], al
    mov byte [r11], dl
    inc r11
    dec rcx
    cmp r11, rcx
    jl .reverse

.encode_out:
    mov byte [rdi], r8b                 ; write previous byte to output string
    inc rdi
    test r9b, r9b                       ; check if we have reached null terminator
    jz done

    mov r8b, r9b
    mov r11, rsi                        ; start a new run
    jmp .encode_in


; Shared by encode and decode
done:
    mov byte [rdi], 0
    ret


;   rdi - buffer
;   rsi - string
;
;   rax - count
;   r8b - byte
;   r10 - 10
;   r11 - digit value
decode:
    xor r11, r11                        ; clear digit value
    xor rax, rax                        ; clear count
    mov r10, 10
    jmp .decode_in

                                        ; If rax is 0 or 1, the byte will be output once.
.decode_out:
    mov byte [rdi], r8b                 ; write byte to output buffer
    inc rdi
    dec rax
    jg .decode_out                      ; repeat rax times 

    xor rax, rax

.decode_in:
    mov r8b, byte [rsi]                 ; read byte from input string
    inc rsi

    cmp r8b, '9'
    ja .decode_out                      ; output character that is not a digit or null

    test r8b, r8b                       ; check if we have reached null terminator
    jz done

    mov r11b, r8b
    sub r11b, '0'
    jl .decode_out                      ; output character if it is not a digit

    mul r10                             ; multiply count by 10
    add rax, r11                        ; increase count by current digit
    jmp .decode_in


%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
