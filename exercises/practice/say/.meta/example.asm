default rel

section .rodata
    zero db "zero", 0
    zero_size dq $-zero
    
    singles db "one", 0, "two", 0, "three", 0, 
            db "four", 0, "five", 0, "six", 0, "seven", 0,
            db "eight", 0, "nine", 0
    teens db "ten", 0, "eleven", 0, "twelve", 0, "thirteen", 0
          db "fourteen", 0, "fifteen", 0, "sixteen", 0,
          db "seventeen", 0, "eighteen", 0, "nineteen", 0
    tens db  "twenty", 0, "thirty", 0, "forty", 0, "fifty", 0,
         db  "sixty", 0, "seventy", 0, "eighty", 0, "ninety", 0
    
    billion db "billion", 0
    billion_size dq $-billion

    million db "million", 0
    million_size dq $-million

    thousand db "thousand", 0
    thousand_size dq $-thousand

    hundred db "hundred", 0
    hundred_size dq $-hundred

    lower_bound dq 0
    upper_bound dq 999_999_999_999

section .text

%macro add_separator 1
    dec rdi ; string ends in 0, must go back to continue
    mov al, %1
    stosb
%endmacro

%macro add_number 0
%%get_value: 
    cmp r10, 0
    je %%move_value ; number corresponds to current rdi position
    dec r10 ; will be decremented until position in rdi corresponds to the number

%%find_number:
    lodsb
    cmp al, 0
    jne %%find_number ; find separator (NULL char)

    jmp %%get_value
%%move_value:
    lodsb
    stosb
    cmp al, 0
    jne %%move_value ; loops until end of string
%endmacro

%macro add_multiple 3
    mov rax, r10
    xor rdx, rdx
    mov r8, %1
    div r8

    ; rax is now number of multiples
    ; rdx is rest of number
    mov rsi, rax
    push rdx ; preserve value before recursion
    call say ; appends number of multiples

    add_separator ' '

    lea rsi, %2
    lea r8, %3
    mov rcx, qword [r8]
    rep movsb ; appends multiple

    pop rdx ; restore remainder
    cmp rdx, 0
    je %%end_multiple ; if remainder null, return right away
    ; otherwise add space and appends rest of string

    add_separator ' '

    mov rsi, rdx
    call say
%%end_multiple:
%endmacro

global say
say:
    ; rdi - output char buffer
    ; rsi - number as a int64_t
    ; return is void

    ; the function divides the number by each multiple, from largest to lowest
    ; then it adds the string corresponding to each quotient
    ; then the relevant multiple
    ; then, if there's a remainder, the relevant separator
    ; and, recursively, the string corresponding to the remainder
    ; base cases are 0 and numbers less than 20
    ; multiples of 10 less than 100 also are handled individually
    ; as each call returns a NULL-ended string, rdi is decremented before concatenation
    ; remainder value is preserved between calls by pushing/popping to the stack

    cld

    cmp rsi, qword [lower_bound]
    jl empty
    je add_zero

    cmp rsi, qword [upper_bound]
    jg empty

    mov r10, rsi

    cmp r10, 10
    jl add_single

    cmp r10, 20
    jl add_teen

    cmp r10, 1_000_000_000
    jge add_billion

    cmp r10, 1_000_000
    jge add_million

    cmp r10, 1_000
    jge add_thousand

    cmp r10, 100
    jge add_hundred
    
    mov rax, r10
    xor rdx, rdx
    mov r8, 10
    div r8
    
    lea rsi, [tens]
    mov r10, rax ; multiple of ten
    sub r10, 2 ; tens array start at twenty, which is quotient 2
    add_number
    
    cmp rdx, 0 ; as there was no recursion, didn't need to push/pop rdx
    je end_say

    add_separator '-'
    
    mov r10, rdx
    jmp add_single

add_billion:
    add_multiple 1_000_000_000, [billion], [billion_size]
    ret

add_million:
    add_multiple 1_000_000, [million], [million_size]
    ret

add_thousand:
    add_multiple 1_000, [thousand], [thousand_size]
    ret

add_hundred:
    add_multiple 100, [hundred], [hundred_size]
    ret

add_zero:
    lea rsi, [zero]
    mov rcx, qword [zero_size]
    rep movsb
    ret

add_single:
    lea rsi, [singles]
    dec r10 ; singles start at one, not zero
    add_number
    ret

add_teen:
    lea rsi, [teens]
    sub r10, 10
    add_number
    ret

empty:
    mov al, 0
    stosb

end_say:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
