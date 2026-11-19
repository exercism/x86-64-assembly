default rel

; Each table entry must be exactly 8 bytes.
%macro entry8 1+
%%start: db %1
%if ($ - %%start) != 8
%error "table entry is not 8 bytes"
%endif
%endmacro

section .rodata

colors:         entry8 "black",       0, 0, 0
                entry8 "brown",       0, 0, 0
                entry8 "red",   0, 0, 0, 0, 0
                entry8 "orange",         0, 0
                entry8 "yellow",         0, 0
                entry8 "green",       0, 0, 0
                entry8 "blue",     0, 0, 0, 0
                entry8 "violet",         0, 0
                entry8 "grey",     0, 0, 0, 0
                entry8 "white",       0, 0, 0
                entry8 "gold",     0, 0, 0, 0
                entry8 "silver",         0, 0

tolerances:     entry8 "0 ohms",         0, 0 ; black (single band)
                entry8 "±1%",      0, 0, 0, 0 ; brown
                entry8 "±2%",      0, 0, 0, 0 ; red
                entry8 0, 0, 0, 0, 0, 0, 0, 0 ; orange
                entry8 0, 0, 0, 0, 0, 0, 0, 0 ; yellow
                entry8 "±0.5%",          0, 0 ; green
                entry8 "±0.25%",            0 ; blue
                entry8 "±0.1%",          0, 0 ; violet
                entry8 "±0.05%",            0 ; grey
                entry8 0, 0, 0, 0, 0, 0, 0, 0 ; white
                entry8 "±5%",      0, 0, 0, 0 ; gold
                entry8 "±10%",        0, 0, 0 ; silver

units:
                entry8 "ohms",     0, 0, 0, 0
                entry8 "kiloohms"
                entry8 "megaohms"
                entry8 "gigaohms"

section .text
global label

; finds the index in the `colors` array of the `rdx` string
lookup:
        lea     rax, [colors]

.compare_word:
        mov     r10, rax
        mov     r11, rdx
        add     rax, 8

.compare_char:
        mov     r8b, byte [r10]
        inc     r10
        mov     r9b, byte [r11]
        inc     r11

        cmp     r8b, r9b
        jne     .compare_word

        test    r8b, r8b
        jnz     .compare_char

        sub     rax, 8
        lea     r10, [colors]
        sub     rax, r10
        shr     rax, 3
        ret

; extern void label(char *buffer, const char **colors);
label:
        push    r12
        push    r13
        push    r14
        push    r15

        mov     rdx, [rsi]
        add     rsi, 8
        call    lookup
        mov     r12, rax                ; first digit

        mov     rdx, [rsi]
        test    rdx, rdx
        cmovz   rsi, rax                ; rsi becomes tolerance
        jz      .write_tolerance        ; One band resistors only have the color black with a value of 0.

        add     rsi, 8
        call    lookup
        mov     r13, rax                ; second digit
        xor     r14d, r14d              ; default third digit

        mov     rdx, [rsi]
        add     rsi, 8
        call    lookup
        mov     r15, rax                ; third band (multiplier or third digit)

        mov     rdx, [rsi]
        add     rsi, 8
        call    lookup
                                        ; rax holds fourth band (tolerance or multiplier)

        mov     rdx, [rsi]
        test    rdx, rdx
        jz      .calculate

        mov     r14, r15                ; third digit
        lea     r15d, [rax + 1]         ; fourth band (multiplier), incremented due to extra digit

        add     rsi, 8
        call    lookup

.calculate:
        mov     rsi, rax                ; tolerance
        add     r12, '0'                ; convert digits to characters
        add     r13, '0'
        add     r14, '0'

        lea     eax, [r15 + 1]
        xor     edx, edx
        mov     ecx, 3
        div     ecx                     ; eax = quotient, edx = remainder

        test    edx, edx
        jz      .one_two

        cmp     edx, 1
        je      .two_one

.three:
        mov     byte [rdi], r12b
        mov     byte [rdi + 1], r13b
        mov     byte [rdi + 2], r14b

        add     rdi, 3
        jmp     .write_units

.two_one:
        mov     byte [rdi], r12b
        mov     byte [rdi + 1], r13b
        add     rdi, 2

        cmp     r14b, '0'
        je      .write_units

        mov     byte [rdi], '.'
        mov     byte [rdi + 1], r14b

        add     rdi, 2
        jmp     .write_units

.one_two:
        mov     byte [rdi], r12b
        inc     rdi

        mov     r12d, r13d
        or      r12d, r14d
        cmp     r12b, '0'
        je      .write_units            ; both digits are '0'

        mov     byte [rdi], '.'
        mov     byte [rdi + 1], r13b
        add     rdi, 2

        cmp     r14b, '0'
        je      .write_units

        mov     byte [rdi], r14b
        inc     rdi

.write_units:
        mov     byte [rdi], ' '
        inc     rdi

        lea     rdx, [units]
        mov     rcx, qword [rdx + 8 * rax]
        mov     qword [rdi], rcx
                                        ; if eax is zero, we increase rdi by 4, otherwise by 8
        lea     rcx, [rdi + 4]
        add     rdi, 8
        test    eax, eax
        cmovz   rdi, rcx

        mov     byte [rdi], ' '
        inc     rdi

.write_tolerance:
                                        ; rsi holds tolerance
        lea     rdx, [tolerances]
        lea     rdx, [rdx + rsi*8]

.copy:
        mov     cl, byte [rdx]
        mov     byte [rdi], cl
        inc     rdx
        inc     rdi
        test    cl, cl
        jnz     .copy

        pop     r15
        pop     r14
        pop     r13
        pop     r12
        ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
