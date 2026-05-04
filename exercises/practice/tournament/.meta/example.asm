default rel

section .rodata

align 16
header db "Team                           | MP |  W |  D |  L |  P"
ROW_SZ equ $ - header
times (16 - (ROW_SZ % 16)) db 0

align 16
comma times 16 db 59

TEAM_COL_SZ equ 31
DIV_10_CONST equ 0xFFFFFFFFFFFFFFFF / 10 + 1

section .text

%define ZERO_SIMD xmm0
%define COMMA_SIMD xmm5
%define MAP_INDEX rbx
%define SAVE_RDI rbp
%define SAVE_RSI r15

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Registers with dedicated use. DO NOT TOUCH!
; RBX - to be used as index for the map
; RBP and R15 - to be used in STRCMP to avoid memory use on hot path
; XMM0 - to clear the stack
; XMM5 - to find separator in input (;)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%macro insert_header 0
    lea r11, [header]
    movdqa xmm1, [r11]
    movdqa xmm2, [r11 + 16]
    movdqa xmm3, [r11 + 32]
    movdqa xmm4, [r11 + 48]
    movdqu [rdi], xmm1
    movdqu [rdi + 16], xmm2
    movdqu [rdi + 32], xmm3
    movdqa [rdi + 48], xmm4
    add rdi, ROW_SZ
%endmacro

; 1. pointer for first string
; 2. length of first string
; 3. pointer for second string
; 4. length of second string
; result in ZF
%macro strcmp 4
    ; save RDI and rsi
    mov SAVE_RDI, rsi
    mov SAVE_RSI, rdi

    movzx rcx, %4
    cmp %2, cx
    cmova cx, %2

    ; compare strings
    lea rdi, [%1]
    lea rsi, [%3]
    repe cmpsb
    ; flags are set by cmpsb

    ; restore RDI and RSI
    mov rsi, SAVE_RDI
    mov rdi, SAVE_RSI
    ; mov does not affect flags
%%endcmp:
%endmacro

; map holds nodes for up to 32 distinct teams
; each node is 16 bytes wide:
; 1. name pointer   - 8 bytes
; 2. length of name - 2 bytes
; 3. matches played - 1 bytes
; 4. wins           - 1 bytes
; 5. draws          - 1 bytes
; 6. losses         - 1 bytes
; 7. score          - 2 bytes
; MAP_INDEX is clobbered to serve as index
%macro build_map 0
    sub rsp, 32 * 16 + 8 ; stack is 16-byte aligned

    xor eax, eax
%%clear_map:
    movdqa [rsp + rax], ZERO_SIMD
    add eax, 16
    cmp eax, 32 * 16
    jnz %%clear_map

    xor ebx, ebx
%endmacro

%macro tear_map 0
    add rsp, 32 * 16 + 8
%endmacro

; arguments:
; 1. pointer to a string
; 2. length of a string
%macro insert_map 2
    mov eax, -16
%%check:
    add eax, 16
    cmp rax, MAP_INDEX
    jae %%insert

    mov r12, [rsp + rax]
    mov r13, [rsp + rax + 8]

    strcmp %1, %2w, r12, r13w
    jnz %%check

    shr %2, 16
    shl %2, 16
    add %2, r13
%%insert:
    mov [rsp + rax], %1
    mov [rsp + rax + 8], %2
    lea r14, [MAP_INDEX + 16]
    cmp rax, MAP_INDEX
    cmove MAP_INDEX, r14
%endmacro

; returns:
; RAX - score
; R8 - length of first team
; R9 - length of second team
%macro parse_line 0
    mov r10, rsi          ; pointer for first team

    mov edx, -16
%%find_first:
    add edx, 16
    pcmpistri COMMA_SIMD, [rsi + rdx], 0b00_00_10_00
    ja %%find_first
    lea r8d, [ecx + edx]  ; length of first team

    lea rsi, [rsi + r8 + 1]
    mov r11, rsi          ; pointer for second team

    mov edx, -16          ; start of second
%%find_second:
    add edx, 16
    pcmpistri COMMA_SIMD, [rsi + rdx], 0b00_00_10_00
    ja %%find_second
    lea r9d, [ecx + edx]  ; length of second team

    lea rsi, [rsi + r9 + 1]

    movzx edx, byte [rsi]

    ; the constants are encoded in registers because they exceed a DWORD
    ; for this same reason, they can't be declared as `equ` constants
    mov r12, (1 << 16) | (1 << 24) | (3 << 48) ; victory
    mov r13, (1 << 16) | (1 << 32) | (1 << 48) ; draw
    mov r14, (1 << 16) | (1 << 40)             ; loss

    ; case 1:
    ; first team wins
    lea rax, [r8 + r12]
    lea rcx, [r9 + r14]
    cmp edx, "w"
    cmove r8, rax
    cmove r9, rcx

    ; case 2:
    ; draw
    lea rax, [r8 + r13]
    lea rcx, [r9 + r13]
    cmp edx, "d"
    cmove r8, rax
    cmove r9, rcx

    ; case 3:
    ; first team loses
    lea rax, [r8 + r14]
    lea rcx, [r9 + r12]
    cmp edx, "l"
    cmove r8, rax
    cmove r9, rcx

    insert_map r10, r8
    insert_map r11, r9

    movzx edx, byte [rsi]

    mov eax, 3
    mov ecx, 4            ; stride
    cmp edx, "w"
    cmove ecx, eax        ; 'win' has only 3 letters

    add rsi, rcx
%endmacro

; by convention, the number is already on RAX
; r10 holds 10
; r14 holds DIV_10_CONST
; the digits will be stored in R12
%macro stringify 0
    xor r12d, r12d
%%loop:
    mul r14
    mov r13, rdx   ; quotient
    mul r10        ; RDX now holds remainder
    add rdx, '0'   ; digit
    and rdx, 0xFF
    shl r12, 8
    or r12, rdx    ; accumulates each digit in a byte of r12
    mov rax, r13   ; RAX holds quotient for next iteration
    test rax, rax
    jnz %%loop     ; keeps iterating until quotient is 0
%endmacro

; arguments are:
; 1. column length
; 2. num of spaces after number
%macro insert_column 2
    mov byte [rdi], '|'
    inc rdi

    stringify

    lzcnt rdx, r12
    shr rdx, 3
    neg rdx
    add rdx, 8      ; number of bytes with digits

    mov rcx, %1
    sub rcx, rdx    ; pad
    sub rcx, %2
    mov eax, ' '    ; space
    rep stosb

    mov [rdi], r12d ; inserts all digits at once
    add rdi, rdx    ; increases buffer point by the number of digits

    mov rcx, %2
    rep stosb       ; insert space after number
%endmacro

; arguments
; 1. team string
; 2. remaining stats for the team, as a qword
%macro format_team 2
    mov byte [rdi], `\n`
    inc rdi

    mov eax, 0xFFFF
    and rax, %2
    shr %2, 16

    mov rcx, rax
    lea rsi, [%1]
    rep movsb

    mov ecx, TEAM_COL_SZ
    sub ecx, eax ; pad
    mov eax, ' ' ; space
    rep stosb

    ; repeats 4 times:
    ; 1. MP
    ; 2. W
    ; 3. D
    ; 4. L
%rep 4
    mov eax, 0xFF
    and rax, %2
    shr %2, 8
    insert_column 4, 1
%endrep

    mov eax, 0xFFFF
    and rax, %2
    insert_column 3, 0 ; score column has 3 of padding and no space after number
%endmacro

%macro insert_teams 0
    mov r10, 10
    mov r14, DIV_10_CONST
    mov r11d, -16
%%main_loop:
    add r11d, 16

    cmp r11, MAP_INDEX
    jae %%end_insert

    mov r8, [rsp + r11]
    mov r9, [rsp + r11 + 8]

    format_team r8, r9

    jmp %%main_loop
%%end_insert:
%endmacro

; clobbers basically everything
%macro selection_sort 0
    xor r11d, r11d
%%insert_loop:
    cmp r11, MAP_INDEX
    jae %%end_sort

    mov rax, [rsp + r11]
    mov rdx, [rsp + r11 + 8]

    movzx r8, word [rsp + r11 + 14]  ; score
    mov rsi, r11                     ; best position

    mov r10, r11
%%inner:
    add r10, 16

    cmp r10, MAP_INDEX
    jae %%swap

    mov r12, [rsp + r10]
    mov r13, [rsp + r10 + 8]

    movzx r9, word [rsp + r10 + 14]   ; score

    cmp r9, r8
    cmova r8, r9
    cmova rax, r12
    cmova rdx, r13
    cmova rsi, r10
    jne %%inner

    strcmp r12, r13w, rax, dx
    cmovg r8, r9
    cmovg rax, r12
    cmovg rdx, r13
    cmovg rsi, r10
    jmp %%inner
%%swap:
    mov r12, [rsp + r11]
    mov r13, [rsp + r11 + 8]
    mov [rsp + r11], rax
    mov [rsp + r11 + 8], rdx
    mov [rsp + rsi], r12
    mov [rsp + rsi + 8], r13
    add r11, 16
    jmp %%insert_loop
%%end_sort:
%endmacro

; extern void tally(char buffer[], const char rows[]);
global tally
tally:
    insert_header

    movzx eax, byte [rsi]
    test eax, eax
    jz .end_tally

    push SAVE_RDI
    push MAP_INDEX
    push SAVE_RSI
    push r12
    push r13
    push r14

    pxor ZERO_SIMD, ZERO_SIMD       ; xmm0 is preserved cleared
    movdqa COMMA_SIMD, [comma]      ; xmm5 is preserved all commas

    build_map
.parse:
    parse_line

    movzx eax, byte [rsi]
    inc rsi

    test eax, eax
    jnz .parse

    selection_sort
    insert_teams

    tear_map

    pop r14
    pop r13
    pop r12
    pop SAVE_RSI
    pop MAP_INDEX
    pop SAVE_RDI
.end_tally:
    mov byte [rdi], 0
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
