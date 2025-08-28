section .text
global find_anagrams

%macro is_in_range 3 ; result is a boolean in r11
    xor r11, r11

    cmp %1, %2
    jl %%false

    cmp %1, %3
    jg %%false

    mov r11, 1
%%false:
%endmacro

%define is_lower(char) is_in_range char, 'a', 'z'
%define is_upper(char) is_in_range char, 'A', 'Z'
%define to_lower(char) add char, ('a' - 'A')

%macro initialize_map 0
    xor r8, r8
%%zero_initialize_map:
    mov byte [rsp + r8], 0
    inc r8

    cmp r8, 26
    jl %%zero_initialize_map
%endmacro

%macro map_word 0
    xor rax, rax
%%map_loop:
    lodsb

    is_lower(al)

    cmp r11, 1
    je %%handle_lower

    is_upper(al)

    cmp r11, 1
    je %%handle_upper

    cmp al, 0
    jne %%map_loop

    jmp %%end

%%handle_upper:
    to_lower(al)
%%handle_lower:
    sub al, 'a'
    inc byte [rsp + rax]

    jmp %%map_loop
%%end:
%endmacro

%macro check_if_not_equal 0 ; result is a boolean in r12
    mov r8, -1
    mov r12, 1
%%loop:
    inc r8

    mov al, byte [rcx + r8]

    cmp al, 0
    je %%end

    is_lower(al)

    cmp r11, 1
    je %%handle_lower_comparing

    to_lower(al)

%%handle_lower_comparing:
    mov r10b, byte [rsi + r8]

    cmp r10b, 0
    je %%end

    is_lower(r10b)

    cmp r11, 1
    je %%handle_lower_candidate

    to_lower(r10b)

%%handle_lower_candidate:
    cmp al, r10b
    sete al

    and r12b, al
    jmp %%loop

%%end:
    cmp al, byte [rsi + r8]
    sete al

    and r12b, al
%endmacro

find_anagrams:
    ; rdi - boolean array, with result for each word in input array
    ; rsi - input array of words
    ; rdx - number of words in input array
    ; rcx - word to be compared with ones in input array
    ; return is void

    ; The algorithm is:
    ;
    ; creates a frequency map in the stack for normalized (lowered) letters in comparing string
    ; reduces the stack frame pointer for a second map, for each word
    ;
    ; loops over words in input array until its end
    ;
    ; checks if input word is equal to comparing string. If it is, store negative result in output array
    ;
    ; if it's not, creates a frequency map in the stack for normalized letters in the word
    ; and compares both maps, storing the result in output array

    ; prologue
    push r12
    push rbp
    mov rbp, rsp
    sub rsp, 26 ; 26 for ASCII letters (normalized to lower case)
                ; frequency map for comparing word

    initialize_map ; zero-initialize

    mov r9, rsi
    mov rsi, rcx

    map_word ; creates frequency map for comparing string

    sub rsp, 26 ; 26 for ASCII letters (normalized to lower case)
                ; frequency map for candidate words

.comparing_loop:
    dec rdx

    cmp rdx, 0
    jl .end_find_anagram ; reached end of input array

    mov rsi, [r9] ; current input word
    add r9, 8

    check_if_not_equal
    je .continue_comparing ; if it's not equal, continue the comparison
    ; otherwise, store false and moves to next iteration

    mov rax, 0 ; rax is false
    stosd ; stores false
    jmp .comparing_loop

.continue_comparing:

    initialize_map ; zero-initialize map for current word
    map_word ; create frequency map for current word

    mov r11, rcx
    mov rcx, 26 ; size of frequency maps

    mov rax, 1 ; flag for equality
.check_if_anagram:
    mov r8b, byte [rsp + rcx - 1]
    cmp r8b, byte [rsp + 26 + rcx - 1]
    sete r12b ; r12b is 1 if equivalent letters in both maps are equal, and 0 otherwise

    and al, r12b ; rax remains set if r12b is set. Once rax is cleared, it remains cleared

    loop .check_if_anagram ; loops until the end of both maps

    mov rcx, r11
    stosd ; rax already holds a boolean

    jmp .comparing_loop ; moves to next iteration

.end_find_anagram:
    ; epilogue
    mov rsp, rbp
    pop rbp
    pop r12
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
