default rel

finished_end equ 0
loop_end equ 1

section .bss
    current_pile resb 500

section .text
global simulate_game

%macro parse_cards 4
    xor r10, r10
    mov r12, 1
%%loop:
    cmp %1, %4
    je %%end

    mov r10d, dword [%3 + 4*%2]

    cmp r10d, 10
    cmovle r10, r12

    mov byte [rsp + %1], r10b

    inc %1
    inc %2
    jmp %%loop
%%end:
%endmacro

simulate_game:
    ; RDI - array of an enum (int32_t) card_t, for playerA
    ; RSI - count of cards in playerA array, as a uint64_t
    ; RDX - array of an enum (int32_t) card_t, for playerB
    ; RCX - count of cards in playerB array, as a uint64_t
    ; return is a struct of 3 uint32_t in RAX/RDX

    ; Since the game may loop infinitely,
    ; the previous states must be memorized
    ;
    ; Each initial state for the deck (without a central pile)
    ; is formed of two Nodes, each corresponding to the hand of each player
    ;
    ; Since all cards are at most 14, a byte is enough to store them
    ; Cards are normalized, so all numbers are 1 in value. This is for checking for a loop
    ;
    ; The State is, therefore, a "struct" formed of playerA's hand + playerB's hand
    ; separated by a single NULL and stored in the stack

    ; Algorithm is:
    ;
    ; Alternates between players, adding cards to the pile and paying penalties according to the rules
    ;
    ; Whenever a player doesn't have a card to play in their turn,
    ; or finishes paying a penalty without using a penalty card, there's a trick
    ;
    ; Whenever there's a trick, the current hand of each player is copied to a new State, further in the stack
    ; and the pile is added to the end of the hand of the player who made the trick
    ;
    ; Then, a linear search is made in the stack for previous States. If an equal State is found, this is a loop end
    ; Otherwise, game proceeds until one of the players holds all the cards at the end of a trick

    ; prologue
    push r12
    push r13
    push r14
    push r15

    push rbp
    mov rbp, rsp

    mov r11, rsi
    add r11, rcx ; total number of cards
    inc r11 ; for separator

    sub rsp, 24
    mov qword [rbp - 8], r11 ; num of cards
    mov qword [rbp - 16], rsi ; num of cards with playerA
    mov qword [rbp - 24], rcx ; num of cards with playerB

    sub rsp, r11

    xor r8, r8
    xor r9, r9

    parse_cards r9, r8, rdi, rsi

    mov byte [rsp + r9], 0 ; add separator
    inc r9

    mov r13, rsp
    add r13, r9 ; start of playerB in stack

    xor r8, r8

    parse_cards r9, r8, rdx, r11

    ; now the stack holds normalized cards, each 1 byte in size
    ; and each number has the same value

    xor r8, r8 ; num of cards played
    xor r9, r9 ; num of tricks
    xor r10, r10 ; flag for player turn
                 ; 0 -> playerA starts
                 ; 1 -> playerB starts

.game_loop:
    lea r12, [current_pile]

    xor r14, r14 ; num of cards played by playerA
    xor r15, r15 ; num of cards played by playerB

    cmp r10, 0
    jne .playerB

.playerA:
    cmp r14, qword [rbp - 16]
    je .trickB

    mov al, byte [rsp + r14]
    inc r14

    inc r8
    mov byte [r12], al
    inc r12

    sub al, 10

    cmp al, 0
    jle .playerB

.penaltyB:
    dec al

    cmp al, 0
    jl .trickA

    cmp r15, qword [rbp - 24]
    je .trickA

    mov r11b, byte [r13 + r15]
    inc r15

    inc r8
    mov byte [r12], r11b
    inc r12

    sub r11b, 10

    cmp r11b, 0
    jle .penaltyB

    jmp .penaltyA

.trickA:
    inc r9 ; increments num of tricks

    mov rsi, rsp
    sub rsp, qword [rbp - 8] ; reserve space for new deck

    mov rdi, rsp

    add rsi, r14
    sub qword [rbp - 16], r14
    mov rcx, qword [rbp - 16]

    rep movsb

    lea rsi, [current_pile]
    mov rcx, r12
    sub rcx, rsi
    add qword [rbp - 16], rcx

    rep movsb
    ; playerA now has all cards remaining in their hand + cards in the pile

    mov al, 0
    stosb ; separator

    mov rsi, r13
    add rsi, r15
    mov r13, rdi

    sub qword [rbp - 24], r15
    mov rcx, qword [rbp - 24]

    rep movsb
    ; playerB has only cards remaining in their hand

    xor r10, r10 ; clear flag

    cmp qword [rbp - 24], 0
    je .finish_end ; playerB has no cards, end game

    jmp .check_looping_deck

.playerB:
    cmp r15, qword [rbp - 24]
    je .trickA

    mov r11b, byte [r13 + r15]
    inc r15

    inc r8
    mov byte [r12], r11b
    inc r12

    sub r11b, 10

    cmp r11b, 0
    jle .playerA

.penaltyA:
    dec r11b

    cmp r11b, 0
    jl .trickB

    cmp r14, qword [rbp - 16]
    je .trickB

    mov al, byte [rsp + r14]
    inc r14

    inc r8
    mov byte [r12], al
    inc r12

    sub al, 10

    cmp al, 0
    jle .penaltyA

    jmp .penaltyB

.trickB:
    inc r9 ; increments num of tricks

    mov rsi, rsp
    sub rsp, qword [rbp - 8] ; reserve space for new deck

    mov rdi, rsp

    add rsi, r14
    sub qword [rbp - 16], r14
    mov rcx, qword [rbp - 16]

    rep movsb
    ; player A has only cards remaining in their hand

    mov al, 0
    stosb ; separator

    mov rsi, r13
    add rsi, r15
    mov r13, rdi

    sub qword [rbp - 24], r15
    mov rcx, qword [rbp - 24]

    rep movsb

    lea rsi, [current_pile]
    mov rcx, r12
    sub rcx, rsi
    add qword [rbp - 24], rcx

    rep movsb
    ; playerB now has all cards remaining in their hand + cards in the pile

    mov r10, 1 ; sets flag

    cmp qword [rbp - 16], 0
    je .finish_end ; playerA has no cards in hand, end game

.check_looping_deck:
    xor r14, r14
.loop_check:
    inc r14

    mov rsi, rsp

    mov rdi, qword [rbp - 8] ; each State has the same size
    imul rdi, r14
    add rdi, rsp

    lea r15, [rbp - 24]

    cmp rdi, r15
    je .game_loop ; end of memorized States

    mov rcx, qword [rbp - 8]
    rep cmpsb
    je .loop_end ; current State == memorized State -> loop end

    jmp .loop_check

.loop_end:
    ; RAX holds state enum in lower 4 bytes
    ; and card count in higher 4 bytes
    ;
    ; RDX holds trick count in lower 4 bytes

    shl r8, 32
    mov rax, loop_end
    or rax, r8

    mov edx, r9d
    jmp .epilogue

.finish_end:
    ; RAX holds state enum in lower 4 bytes
    ; and card count in higher 4 bytes
    ;
    ; RDX holds trick count in lower 4 bytes

    shl r8, 32
    mov rax, finished_end
    or rax, r8

    mov edx, r9d

.epilogue:
    mov rsp, rbp
    pop rbp

    pop r15
    pop r14
    pop r13
    pop r12
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
