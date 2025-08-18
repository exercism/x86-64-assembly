CHOICE equ 0
ONES equ 1
TWOS equ 2
THREES equ 3
FOURS equ 4
FIVES equ 5
SIXES equ 6
LITTLE_STRAIGHT equ 7
BIG_STRAIGHT equ 8
FULL_HOUSE equ 9
FOUR_OF_A_KIND equ 10
YACHT equ 11

section .text
global score

; straight starts from 1 (little) or 2 (big)
%macro straight 1
    mov r8d, %1 ; current die
    mov r9d, %1
    add r9d, 5 ; last die
%%check_straight:
    inc r8
    cmp byte [rsp + r8 - 1], 1
    jne end ; each die in the sequence must have frequency 1, otherwise it's invalid
    cmp r8, r9
    jl %%check_straight

    mov rax, 30
    jmp end
%endmacro

; int score(category_t category, const uint16_t *dice);
score:
    ; edi - category as an enum
    ; rsi - array of int16_t containing 5 elements (dice)
    ; return is an int in eax

    ; This function is basically a dispatch table for many different procedures.
    ; In other languages, the fun resides in finding higher-order patterns to reduce code size.
    ; I initially thought of trying creating many small procedures to pass around as callbacks.
    ; However, things seemed too convoluted and there was too much boilerplate involved.
    ; So, in the end, I just grouped what seemed natural to group, the numbers and the straights,
    ; the other categories were treated individually.
    ; I tried to minimize branching by using SETcc and CMOVcc when it seemed approppriate.
    ; Other than that, the dispatch behaviour remained

    xor rax, rax
    mov rcx, 5 ; number of dice

    cmp edi, CHOICE
    je choice ; dispatch for CHOICE

    cmp edi, ONES
    setge r8b
    cmp edi, SIXES
    setle r9b

    and r8b, r9b
    jne numbers ; dispatch for all numbers

    ; the other categories need a frequency map to check conditions
    ; prologue
    push rbp
    mov rbp, rsp
    sub rsp, 6

    ; the map is small, unrolling the loop seemed easier
    mov byte [rsp], 0
    mov byte [rsp + 1], 0
    mov byte [rsp + 2], 0
    mov byte [rsp + 3], 0
    mov byte [rsp + 4], 0
    mov byte [rsp + 5], 0

get_frequency:
    lodsw
    inc byte [rsp + rax - 1]
    loop get_frequency

    xor rax, rax

    cmp edi, FULL_HOUSE
    je full_house ; dispatch for full house

    cmp edi, FOUR_OF_A_KIND
    je four_of_a_kind ; dispatch for four of a kind

    cmp edi, YACHT
    je yacht ; dispatch for yacht
    ; after that, the category must be one of little straight or big straight

    sub edi, 7
    straight edi ; macro to dispatch straights

full_house:
    mov rcx, 6
    xor r10, r10
    xor r11, r11
full_house_loop:
    cmp byte [rsp + rcx - 1], 2
    cmove r10, rcx ; if number in rcx has frequency 2, it's moved to r10
    cmp byte [rsp + rcx - 1], 3
    cmove r11, rcx ; if number in rcx has frequency 3, it's moved to r11
    loop full_house_loop

    ; both r10 and r11 must be non-zero
    cmp r10, 0
    je end

    cmp r11, 0
    je end

    ; times is a NASM directive which repeats the instruction the specified number of times
    ; it's basically an unroll
    times 2 add rax, r10
    times 3 add rax, r11

    jmp end

four_of_a_kind:
    mov rcx, 6
    xor r10, r10
    xor r11, r11
four_of_a_kind_loop:
    cmp byte [rsp + rcx - 1], 4
    cmovge r10, rcx ; if number in rcx has frequency 4 or 5, it's moved to r10
    loop four_of_a_kind_loop

    shl r10, 2 ; multiply number by 4
    add rax, r10

    jmp end

yacht:
    mov rcx, 6
    mov r8, 50
yacht_loop:
    cmp byte [rsp + rcx - 1], 5
    cmove rax, r8 ; if number in rcx has frequency 5, result is 50
                  ; otherwise it remains 0 (or 50 if set previously)
    loop yacht_loop

end:
    ; epilogue
    mov rsp, rbp
    pop rbp
    ret

choice:
    ; the simplest category, it is valid for everything and just sums everything
    mov r8w, word [rsi + 2*rcx - 2]
    add ax, r8w
    loop choice

    ret

numbers:
    ; loops over dice and adds the corresponding numbers. It's valid for everything
    xor r8, r8
    cmp word [rsi + 2*rcx - 2], di
    cmove r8w, di
    add rax, r8
    loop numbers

    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
