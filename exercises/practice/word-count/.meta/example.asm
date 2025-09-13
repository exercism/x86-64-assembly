section .text
global count_words

%define to_lower(x) bts x, 5

%macro is_in_range 3
    xor r11, r11

    cmp %1, %2
    jl %%end

    cmp %1, %3
    jg %%end

    inc r11
%%end:
%endmacro

%define is_alpha(x) is_in_range x, 'a', 'z'
%define is_digit(x) is_in_range x, '0', '9'

count_words:
    ; RDI - buffer of a struct of 50 bytes and a uint64_t
    ; RSI - input string
    ; return is size of buffer, as a uint64_t, in RAX

    ; Algorithm is:
    ;
    ; 1- Parse input string, separating words and storing them in the stack;
    ; 2- Once a separator is found, compare word in the stack with already stored words;
    ; 3- If not found, create new entry in output buffer, set its count to 1
    ; and increment counter for num of elements in buffer;
    ; 4- If a match is found, increments its count;
    ; 5- Continue looping until end of input string.

    ; prologue

    push r12
    push rbp
    mov rbp, rsp
    sub rsp, 48 ; WORD_SIZE

    xor rax, rax
    xor r8, r8 ; counter for num of words
    xor rdx, rdx ; length of a word
.get_words:
    lodsb

    test al, al
    jz .check_end_string ; end of string was found, check if there's a word to store

    cmp al, 39 ; 39 is decimal for apostrophe
    je .check_apostrophe

    is_digit(al)

    cmp r11, 1
    je .store_char ; digits are words

    to_lower(rax)
    is_alpha(al)

    cmp r11, 1
    jne .end_of_word ; if not apostrophe, digit or alpha, it's a separator
    ; otherwise, store it

.store_char:
    mov byte [rsp + rdx], al
    inc rdx
    jmp .get_words

.check_end_string:
    test rdx, rdx
    jz .end_parse ; no word to store, moves to the end
    ; otherwise, handle last word

    jmp .end_of_word

.check_apostrophe:
    cmp r11, 1
    jne .get_words ; if not set, previous char wasn't stored,
                   ; so it's not an apostrophe in a contraction
    ; otherwise, checks next letter

    lodsb

    test al, al
    jz .check_end_string ; if it's NULL, end of string
                         ; and apostrophe isn't part of a word
    ; otherwise checks if letter is alpha, since there's no contraction with digits

    to_lower(rax)
    is_alpha(al)

    cmp r11, 1
    jne .end_of_word ; if letter not alpha, apostrophe is a separator
    ; otherwise, apostrophe is part of a contraction and must be stored alongside current letter

    mov byte [rsp + rdx], 39
    mov byte [rsp + rdx + 1], al
    add rdx, 2
    xor r11, r11

    jmp .get_words ; continue looping

.end_of_word:
    cmp rdx, 0
    je .get_words ; if word length is zero, there's nothing to store
    ; otherwise checks if word is already stored

.check_word:
    mov r9, rdi
    mov r10, rsi

    mov r11, -1
.check_mapped_words:
    inc r11

    cmp r11, r8
    je .insert_new_word ; end of output buffer, no match found

    mov rsi, rsp
    imul rdi, r11, 56 ; each map entry has size 56 (48 for buffer + 8 for counter)
    add rdi, r9

    lea r12, [rdi + 48] ; pointer to counter position
    mov rcx, rdx

    repe cmpsb
    jne .check_mapped_words

    cmp byte [rdi], 0
    jne .check_mapped_words ; if char at end of output buffer is not null,
                            ; this is only a partial match, must check next entry in buffer
    ; otherwise, a match was found

    mov rdi, r12
    inc qword [rdi] ; increments counter

    mov rdi, r9
    mov rsi, r10

    xor r11, r11
    xor rdx, rdx ; resets word length

    test al, al
    jnz .get_words ; if not end of string, continue parsing
    ; otherwise, this was last word

    jmp .end_parse

.insert_new_word:
    mov rsi, rsp
    imul rdi, r11, 56 ; each map entry has size 56 (48 for buffer + 8 for counter)
    add rdi, r9

    lea r12, [rdi + 48] ; pointer to counter position
    mov rcx, rdx

    rep movsb ; copies word
    mov byte [rdi], 0 ; appends NULL

    mov rdi, r12
    mov qword [rdi], 1 ; sets counter for word as 1

    mov rdi, r9
    mov rsi, r10
    inc r8 ; increments size of output buffer

    xor r11, r11
    xor rdx, rdx ; resets word length

    test al, al
    jnz .get_words ; if not end of string, continue parsing
    ; otherwise, this was last word

.end_parse:
    mov rax, r8 ; returns length for output buffer

    ; epilogue

    mov rsp, rbp
    pop rbp
    pop r12
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
