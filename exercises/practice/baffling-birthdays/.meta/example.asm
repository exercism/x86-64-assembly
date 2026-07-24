section .bss
xorshift32_state resd 1
xorshift32_flag resb 1

%macro xorshift32 0
    movzx ecx, byte [rel xorshift32_flag]
    test ecx, ecx
    jnz %%skip

    mov byte [rel xorshift32_flag], 1

    rdtsc
    lea eax, [eax + edx + 1812433253]
    mov dword [rel xorshift32_state], eax
%%skip:
    mov eax, dword [rel xorshift32_state]

    mov ecx, eax
    shl ecx, 13
    xor eax, ecx

    mov ecx, eax
    shr ecx, 17
    xor eax, ecx

    mov ecx, eax
    shl ecx, 5
    xor eax, ecx

    mov [rel xorshift32_state], eax
%endmacro

alignb 16
aes128_keys resb 11 * 16
aes128_result resb 16
aes128_counter resq 1
aes128_flag resb 1

%macro expand_aes 2
    aeskeygenassist xmm2, xmm1, %1
    pshufd xmm2, xmm2, 0xFF

    movdqa xmm3, xmm1
    pslldq xmm3, 4
    pxor xmm1, xmm3
    pslldq xmm3, 4
    pxor xmm1, xmm3
    pslldq xmm3, 4
    pxor xmm1, xmm3

    pxor xmm1, xmm2
    movdqa [rel aes128_keys + %2], xmm1
%endmacro

%macro aes128 0
    movzx ecx, byte [rel aes128_flag]
    test ecx, ecx
    jnz %%skip_setup

    mov byte [rel aes128_flag], 1

    rdtsc
    mov qword [rel aes128_keys], rax
    mov qword [rel aes128_keys + 8], rdx

    movdqa xmm1, [rel aes128_keys]

    expand_aes 1, 16
    expand_aes 2, 32
    expand_aes 4, 48
    expand_aes 8, 64
    expand_aes 16, 80
    expand_aes 32, 96
    expand_aes 64, 112
    expand_aes 128, 128
    expand_aes 27, 144
    expand_aes 54, 160
%%skip_setup:
    mov rcx, qword [rel aes128_counter]
    inc rcx
    mov qword [rel aes128_counter], rcx

    test ecx, 1
    jz %%skip_generation

    movq xmm2, rcx

    movdqa  xmm1, [rel aes128_keys]
    pxor    xmm2, xmm1

    %assign i 16
    %rep 9
        movdqa xmm1, [rel aes128_keys + i]
        aesenc xmm2, xmm1
        %assign i i + 16
    %endrep

    movdqu  xmm1, [rel aes128_keys + 160]
    aesenclast xmm2, xmm1
    movdqa [rel aes128_result], xmm2
%%skip_generation:
    lea rax, [rel aes128_result]
    and ecx, 1
    mov rax, qword [rax + 8*rcx]
%endmacro

section .rodata
valid_years:
%assign i 1600
%rep 529
    %if i % 400 != 0 && (i % 100 = 0 || i % 4 != 0)
        dw i
    %endif
    %assign i i + 1
%endrep

day_map:
%assign i 1
%assign j 31
%rep 12
    %assign k 1
    %rep j
        db i
        db k
        %assign k k + 1
    %endrep
    %assign i i + 1

    %if i = 2
        %assign j 28
    %elif j = 28 || j = 30 || i = 8
        %assign j 31
    %else
        %assign j 30
    %endif
%endrep

hundred: dd 0x42c80000
one_div_10000: dd 0x38d1b717

section .text
global shared_birthday
global random_birthdates
global estimated_probability_of_shared_birthday

%macro _shared_birthday 3
    sub rsp, 264

    pxor xmm0, xmm0
    %assign i 0
    %rep 16
        movdqa [rsp + i], xmm0
        %assign i i + 16
    %endrep
    xor eax, eax
%%loop:
    movzx edx, word [%1 + 2]
    movzx ecx, dl
    shr edx, 5
    or edx, ecx
    movzx ecx, byte [rsp + rdx]
    test ecx, ecx
    cmovnz eax, ecx
    jnz %%done
    mov byte [rsp + rdx], 1
    add %1, %3
    dec %2
    jnz %%loop
%%done:
    add rsp, 264
%endmacro

shared_birthday:
    _shared_birthday rsi, rdi, 4
    ret

random_birthdates:
    test rsi, rsi
    jz .done

    lea r9, [rel valid_years]
    lea r11, [rel day_map]

    mov r8d, 365
    mov r10d, 400
.loop:
    ; macOS does not support rdrand or rdseed
    ; and example solutions are expected to be assembly only, without calling external libraries
    ; so we are left with a PRNG
    ; for a chi-squared test, it suffices that the distribution is uniform
    ;
    ; we use 2 different PRNGs:
    ; 1- xorshift32 is our benchmark for a simpler and weaker PRNG.
    ;    This is the minimum students should aim for if implementing their own PRNG.
    ; 2- aes128 is our benchmark for a sophisticated PRNG.
    ;    It has equivalent quality to rdrand, but is faster and should be supported by macOS.
    ;
    ; we use a simple rdtsc as a measure of a cheaper "PRNG" that must fail

    ; xorshift32
    ; rdtsc
    ; rdrand rax
    aes128

    ; rax now holds a random 64-bit number
    ; we use the low 32 bits for the year and the upper 32 bits for day/month

    mov rcx, rax
    shr rcx, 32

    imul eax, eax, 0xFFFFFFFF / 400 + 1
    mul r10d ; edx now holds random % 400
    mov dx, word [r9 + 2*rdx]
    mov word [rdi], dx

    imul eax, ecx, 0xFFFFFFFF / 365 + 1
    mul r8d  ; edx now holds random % 365
    mov dx, word [r11 + 2*rdx]
    mov word [rdi + 2], dx

    add rdi, 4
    dec rsi
    jnz .loop
.done:
    ret

estimated_probability_of_shared_birthday:
    sub rsp, 56 ; a byte for each day

    mov r8d, 365
    mov r9d, 10000
    xor r10d, r10d
    pxor xmm0, xmm0

    test rdi, rdi
    jz .done
.outer:
    %assign i 0
    %rep 3
        movdqa [rsp + i], xmm0
        %assign i i + 16
    %endrep

    mov rsi, rdi
    xor r11d, r11d
.inner:
    aes128

    mov rcx, rax

%macro _generate_birthday 0
    imul eax, ecx, 0xFFFFFFFF / 365 + 1
    mul r8d
    bts [rsp], edx
    setc r11b
    jc .count_shared
%endmacro

    _generate_birthday

    dec rsi
    jz .count_shared

    shr rcx, 32
    _generate_birthday

    dec rsi
    jnz .inner

.count_shared:
    add r10d, r11d

    dec r9d
    jnz .outer

    cvtsi2ss xmm0, r10d
    mulss xmm0, [rel hundred]
    mulss xmm0, [rel one_div_10000]
.done:
    add rsp, 56
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
