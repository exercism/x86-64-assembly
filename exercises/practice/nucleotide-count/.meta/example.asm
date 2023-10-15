section .text
global nucleotide_counts

; rdi - address of strand string
; rsi - address of counts array
; cl - current character
; r8 - adenine count
; r9 - cytosine count
; r10 - guanine count
; r11 - thymine count
nucleotide_counts:
    xor r8, r8                ; Current adenine count is 0
    xor r9, r9                ; Current cytosine count is 0
    xor r10, r10              ; Current guanine count is 0
    xor r11, r11              ; Current thymine count is 0
    jmp .read

.adenine:
    inc r8
    jmp .read

.cytosine:
    inc r9
    jmp .read

.guanine:
    inc r10
    jmp .read

.thymine:
    inc r11

.read:
    mov cl, byte [rdi]        ; Load strand character
    inc rdi
    cmp cl, 'A'
    je .adenine
    cmp cl, 'C'
    je .cytosine
    cmp cl, 'G'
    je .guanine
    cmp cl, 'T'
    je .thymine
    cmp cl, 0
    je .report                ; Check if we have reached end of string
    mov r8, -1
    mov r9, -1
    mov r10, -1
    mov r11, -1

.report:
    mov rax, r8               ; Report adenine count
    mov dword [rsi], eax
    mov rax, r9               ; Report cytosine count
    mov dword [rsi + 4], eax
    mov rax, r10              ; Report guanine count
    mov dword [rsi + 8], eax
    mov rax, r11              ; Report thymine count
    mov dword [rsi + 12], eax
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
