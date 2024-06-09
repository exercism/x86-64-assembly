section .text
global encode, decode

;   rdi - buffer
;   rsi - string
;
;   al - byte
decode:
    cld                                 ; rsi/rdi will be incremented with each lodsb/stosb
    jmp .decode_in

.decode_lowercase:
    neg al
    add al, 'a' + 'z'                   ; replace letter

.decode_out:
    stosb                               ; write letter or digit to output string

.decode_in:
    lodsb                               ; read byte from input phrase

    cmp al, '9'
    ja .decode_lowercase

    cmp al, ' '
    je .decode_in                       ; discard space

    test al, al                         ; check if we have reached null terminator
    jnz .decode_out                     ; numeric digits are preserved



; Shared by encode and decode
done:
    stosb                               ; write null terminator
    ret



;   rdi - buffer
;   rsi - string
;
;   al - byte
;   cl - count to next space
encode:
    cld                                 ; rsi/rdi will be incremented with each lodsb/stosb
    mov cl, 6                           ; immediately before the 6th byte, we will insert a space 
    jmp .encode_in


.encode_if_letter:
    or al, 32                           ; force lowercase
    sub al, 'a'
    cmp al, 26
    jae .encode_in                      ; reject if not a letter

    neg al
    add al, 'z'                         ; replace letter

.encode_out:
    dec cl
    jnz .encode_write

    mov cl, al
    mov al, ' '
    stosb                               ; write space to output string
    mov al, cl
    mov cl, 5                           ; immediately before the 11th byte, etc., we will insert a space

.encode_write:
    stosb                               ; write letter or digit to output string

.encode_in:
    lodsb                               ; read byte from input phrase

    cmp al, '9'
    ja .encode_if_letter

    test al, al                         ; check if we have reached null terminator
    jz done

    cmp al, '0'
    jl .encode_in                       ; discard punctuation

    jmp .encode_out                     ; numeric digits are preserved


%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
