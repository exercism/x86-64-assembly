section .text
global ciphertext

%macro is_in_range 3
    xor r11, r11

    cmp %1, %2
    jl %%end

    cmp %1, %3
    jg %%end

    mov r11, 1
%%end:
%endmacro

%define is_lower(x) is_in_range x, 'a', 'z'
%define is_upper(x) is_in_range x, 'A', 'Z'
%define is_digit(x) is_in_range x, '0', '9'
%define to_lower(x) add x, ('a' - 'A')

%macro hash_index 0
    mov rax, rdx
    imul rax, r10
    add rax, rcx

    lea r11, [r8 - 1]
    sub r11, rax
%endmacro

ciphertext:
    ; RDI - output buffer
    ; RSI - input text
    ; return is void

    ; prologue

    push rbp
    mov rbp, rsp

    ; Normalized text will be stored in the stack in reversed order

    xor r8, r8 ; counter
.normalize_text:
    lodsb

    cmp al, 0
    je .end_normalization

    is_upper(al)

    cmp r11, 1
    je .handle_upper

    is_lower(al)

    mov r10, r11

    is_digit(al)

    or r11, r10
    jnz .store_char

    jmp .normalize_text

.handle_upper:
    to_lower(al)
.store_char:
    dec rsp
    mov byte [rsp], al

    inc r8

    jmp .normalize_text

.end_normalization:
    ; r8 now holds total size of the string

    cmp r8, 0
    je .return

    cvtsi2sd xmm0, r8
    sqrtsd xmm0, xmm0
    cvtsd2si r10, xmm0 ; cast rounds down
                       ; r10 now holds floor(sqrt(length(string)))

    mov r11, r10
    imul r11, r11

    xor rdx, rdx

    cmp r11, r8
    setl dl ; sets if c² < length(string), clears otherwise

    mov r9, r10 ; r == c
    add r10, rdx ; increases c if c² < length(string)

    add r11, r9 ; to consider the increment in c

    cmp r11, r8
    setl dl ; sets if c² < length(string), clears otherwise

    add r9, rdx ; as c - r <= 1 and now c == r + 1 -> r++
                ; no further adjust is needed, since both r and c are now
                ; floor(sqrt(length(string))) + 1 and, therefore, r*c >= length(string)

    ; r9 now holds r
    ; r10 now holds c

    mov rcx, -1 ; counter for num of chunks
.cipher:
    inc rcx

    cmp rcx, r10
    je .end_cipher ; num of chunks == c -> all digits were stored

    mov rdx, -1 ; index inside chunk
.fill_chunk:
    inc rdx

    cmp rdx, r9
    je .add_separator ; length(chunk) == r -> chunk is filled, must add space

    hash_index ; gets index of the relevant char in the stack
               ; considering the chars are stored in reversed order

    cmp r11, 0
    jl .pad ; if index < 0, reached end of the string, must pad until loop end

    mov al, byte [rsp + r11]
    stosb

    jmp .fill_chunk

.pad:
    mov al, ' '
    stosb ; add padding space inside a chunk

    jmp .fill_chunk ; loops until end of chunk

.add_separator:
    mov al, ' '
    stosb ; add space between chunks

    jmp .cipher ; moves to next chunk

.end_cipher:
    dec rdi ; an extra separator was added, must be trimmed
.return:
    mov al, 0
    stosb ; adds NULL at the end of the string

    ; epilogue

    mov rsp, rbp
    pop rbp
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
