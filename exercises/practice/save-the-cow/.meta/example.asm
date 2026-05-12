section .text

; extern result_t guess(const char word[], const char guesses[], size_t num_guesses);
global guess
guess:
    ; a pointer to the struct is passed as an implicit first argument
    ; this is the underlying organization of bytes
    ; 4 bytes  -> state_t enum (initial state is 0)
    ; 27 bytes -> masked_word (initial state is as many '_' as letters in the original word)
    ; 1 byte -> remaining_guesses (initial state is 9)

    mov r11, rcx            ; save number of guesses

    pxor xmm0, xmm0

    push r12
    sub rsp, 112            ; space for a bitmap for the location of each letter in the input string
                            ; since the maximum number of letters is 27, a DWORD is enough to store the location
                            ; since the number of letters is 26 and we are using 1-indexes, we need 27 * 4 DWORDS
                            ; we round to the nearest bigger multiple of 16 to simplify clearing it

    ; vectorized string length loop
    mov r8d, -16
.find_length:
    add r8d, 16
    movdqa xmm1, [rsi + r8]  ; string is 16-byte aligned
    pcmpeqb xmm1, xmm0
    pmovmskb eax, xmm1
    test eax, eax
    jz .find_length

    tzcnt eax, eax
    lea ecx, [r8d + eax]     ; length of input word

    movdqu [rdi], xmm0
    movdqu [rdi + 16], xmm0  ; the struct is all zeros now

    mov byte [rdi + 31], 9   ; remaining_guesses initial state

    test ecx, ecx
    jz .ret                  ; if input string has no letters, return straight away
    ; otherwise, build bitmap and process guesses

    ; clear bitmap
    %assign i 0
    %rep 7
        movdqu [rsp + i], xmm0
        %assign i i + 16
    %endrep

    xor r8d, r8d
    xor r9d, r9d             ; bitset for letters in input string
    mov r10d, 1
.input_string_pass:
    mov byte [rdi + r8 + 4], '_'
    movzx eax, byte [rsi + r8]
    and eax, 0b0001_1111     ; letter index
    bts r9d, eax             ; set the letter in the bitset
    or [rsp + 4*rax], r10d   ; indicate letter location in bitmap
    shl r10d, 1              ; bit for letter location keeps moving to the left
    inc r8
    cmp r8d, ecx
    jb .input_string_pass   ; safe to use a do...while because we tested for empty strings already

    ; now initial state is set

    test r11, r11
    jz .ret                  ; if there are no guesses, return initial state

    xor r12d, r12d
.process_guesses:
    cmp r12d, r11d
    jae .ret                 ; no more guesses

    movzx eax, byte [rdx + r12]
    inc r12d
    and eax, 0b0001_1111     ; letter index
    btr r9d, eax             ; is the letter present in the word? If yes, reset it (guessing twice the same letter is a failure)
    jnc .not_present

    mov r10d, [rsp + 4*rax]  ; bitmap for word
.set_in_masked_word:
    tzcnt eax, r10d          ; index of the first position

    movzx r8d, byte [rsi + rax]   ; letter
    mov [rdi + rax + 4], r8b ; unmask letter

    dec ecx                  ; one less letter remaining to unmask

    blsr r10d, r10d          ; reset lowest bit and sets ZF in bitmap
    jnz .set_in_masked_word  ; keep unmasking until there is no bit set

    test ecx, ecx
    jnz .process_guesses     ; there are still letters to unmask, state remains ongoing

    ; otherwise, state is win

    mov dword [rdi], 2
    cmp r12d, r11d
    jae .ret                  ; no remaining guess, clean win
    jmp .error                ; otherwise, it is an error

.not_present:
    cmp byte [rdi + 31], 0    ; remaining number of guesses
    jz .lose                  ; no remaining guess, lose
    dec byte [rdi + 31]       ; one less remaining guess
    jmp .process_guesses      ; go to next guess

.lose:
    mov dword [rdi], 1
    cmp r12d, r11d
    jae .ret                   ; no remaining guess, clean loss
    ; otherwise, fall throughs to error
.error:
    mov dword [rdi], -1
.ret:
    ; epilogue
    add rsp, 112
    pop r12

    ; struct's address should be returned in rax
    mov rax, rdi
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
