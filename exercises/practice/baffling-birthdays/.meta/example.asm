default rel

SEED equ 1812433253 ; Borosh-Niederreiter multiplier for modulus 2^32
                    ; in line with: https://github.com/cslarsen/mersenne-twister/blob/master/mersenne-twister.cpp

section .bss
    mt_state resd 624 ; array to hold the state of the generator
    index resd 1 ; current index
    is_init resb 1 ; flag for lazy initialization of state array

section .text

global shared_birthday
global random_birthdates
global estimated_probability_of_shared_birthday

; The mt19937 algorithm is being reused from DND-CHARACTER solution
;
; The algorithm for the 32-bit Mersenne Twister PRNG (mt19937) was taken from:
; https://en.wikipedia.org/wiki/Mersenne_Twister#C_code
;
; The seed chosen was the "Borosh-Niederreiter multiplier for modulus 2^32"
; in line with: https://github.com/cslarsen/mersenne-twister/blob/master/mersenne-twister.cpp
; This seed is xor-ed with the CPU timestamp
;
; Here's the godbolt for the wikipedia implementation mentioned above: https://godbolt.org/z/acEoj15xz
; I've taken the "magic numbers" from there
;
;
;

mt_init:
    ; prologue
    push rbp
    mov rbp, rsp
    sub rsp, 4 ; seed

    lea r11, [mt_state]

    rdtsc
    xor rdi, rax

    mov dword [rsp], edi  ; seed
    mov dword [r11], edi

    mov r10, 1 ; i
.mt_init_loop:
    cmp r10, 624
    jge .end_mt_init_loop ; for (int i = 1; i < n; ++i)

    mov eax, dword [rsp] ; seed

    shr eax, 30 ; seed >> (w - 2)
    xor eax, dword [rsp] ; seed ^ (seed >> (w - 2))
    imul edx, eax, 1812433253 ; f * seed ^ (seed >> (w - 2))
    mov eax, r10d
    add eax, edx ; f * seed ^ (seed >> (w - 2)) + i

    mov dword [rsp], eax ; seed = f * seed ^ (seed >> (w - 2))
    mov dword [r11 + 4*r10], eax ; mt_state[i] = seed

    inc r10 ; i++
    jmp .mt_init_loop

.end_mt_init_loop:
    mov dword [index], 0 ; index = 0

    ; epilogue
    mov rsp, rbp
    pop rbp
    ret

mt_rand:
    ; prologue
    push rbp
    mov rbp, rsp
    sub rsp, 20

    lea r10, [mt_state]

    mov eax, [index]
    mov dword [rsp], eax ; k

    sub eax, 623
    mov dword [rsp + 4], eax ; j

    cmp eax, 0
    jge .skip_circular_sum1

    add dword [rsp + 4], 624 ; j remains modulus 624

.skip_circular_sum1:
    xor rax, rax
    mov eax, dword [rsp]
    mov eax, dword [r10 + 4*rax] ; mt_state[k]

    and eax, -2147483648 ; mt_state[k] & UMASK
    mov edx, eax

    xor rax, rax
    mov eax, dword [rsp + 4]
    mov eax, dword [r10 + 4*rax] ; mt_state[j]

    and eax, 2147483647 ; mt_state[j] & LMASK

    or eax, edx
    mov dword [rsp + 8], eax ; x

    shr eax, 1
    mov dword [rsp + 12], eax ; xA

    bt dword [rsp + 8], 0
    jnc .even

    xor dword [rsp + 12], -1727483681 ; xA ^= a

.even:
    mov eax, dword [rsp]
    sub eax, 227
    mov dword [rsp + 4], eax ; j = k - (n - m)

    cmp eax, 0
    jge .skip_circular_sum2

    add dword [rsp + 4], 624 ; j remains modulus 624

.skip_circular_sum2:
    xor rax, rax
    mov eax, dword [rsp + 4]

    mov eax, dword [r10 + 4*rax] ; mt_state[j]
    xor eax, dword [rsp + 12] ; mt_state[j] ^ xA
    mov dword [rsp + 8], eax ; x = mt_state[j] ^ xA

    xor rdx, rdx
    mov edx, dword [rsp]
    mov dword [r10 + 4*rdx], eax ; mt_state[k] = x

    inc dword [rsp] ; k++

    cmp dword [rsp], 624
    jl .set_new_index

    mov dword [rsp], 0 ; if (k >= 624) k = 0

.set_new_index:
    mov eax, dword [rsp]
    mov [index], eax ; index = k

    mov eax, dword [rsp + 8]
    shr eax, 11 ; x >> u
    xor eax, dword [rsp + 8] ; x ^ (x >> u)
    mov dword [rsp + 16], eax ; y = x ^ (x >> u)

    shl eax, 7 ; y << s
    and eax, -1658038656 ; (y << s) & b
    xor dword [rsp + 16], eax ; y = y ^ ((y << s) & b)

    mov eax, dword [rsp + 16]
    shl eax, 15 ; y << t
    and eax, -272236544 ; (y << t) & c
    xor dword [rsp + 16], eax ; y = ((y << t) & c)

    mov eax, dword [rsp + 16]
    shr eax, 18 ; y >> l
    xor eax, dword [rsp + 16] ; z = y ^ (y >> l)
    ; returns z

    ; epilogue
    mov rsp, rbp
    pop rbp
    ret

shared_birthday:
    ; RDI - number of elements in input array
    ; RSI - input array of date_t (struct of 1 uint16_t and 2 uint8_t == 4 bytes)
    ; return is a boolean in RAX

    ; prologue
    push rbp
    mov rbp, rsp

    mov rdx, 0xFFFF0000 ; mask that gets only day and month,
                        ; since year is irrelevant for sharing birthday

    xor rax, rax
    xor r8, r8 ; flag
    mov rcx, rdi
.accumulate:
    lodsd

    and rax, rdx ; apply mask

    mov r10, rsp
.compare_loop:
    cmp r10, rbp
    jge .end_compare

    mov r9d, dword [r10]
    cmp r9d, eax
    sete r11b

    or r8b, r11b

    add r10, 4
    jmp .compare_loop

.end_compare:
    sub rsp, 4
    mov dword [rsp], eax

    cmp r8, 0
    loope .accumulate

    mov rax, r8

    ; epilogue
    mov rsp, rbp
    pop rbp
    ret

%macro generate_year 1
%%leap:
    call mt_rand
    and rax, 65535
    mov r10, rax ; stores normalized random year

    xor rdx, rdx
    mov r11, 400
    div r11

    cmp rdx, 0
    je %%leap ; divisible by 400 is leap, repeats

    mov rax, r10
    xor rdx, rdx
    mov r11, 100
    div r11

    cmp rdx, 0
    je %%non_leap ; divisible by 100 is non-leap, returns

    mov rax, r10
    and rax, 3
    cmp rax, 0
    je %%leap ; divisible by 4 is leap, repeats

%%non_leap:
    mov %1, r10
%endmacro

%macro generate_month 1
    call mt_rand
    xor rdx, rdx
    mov r11, 12
    div r11 ; RDX is in the range 0 - 11
    mov %1, rdx
    inc %1 ; month is in the range 1 - 12
%endmacro

%macro generate_day 2
    call mt_rand

    ; by default, day is in the range 1 - 30
    mov r11, 30

    ; if month is january, march, may, july, august, october or december
    ; then day might be in the range 1 - 31
    mov r10, 31
    cmp %1, 1
    cmove r11, r10
    cmp %1, 3
    cmove r11, r10
    cmp %1, 5
    cmove r11, r10
    cmp %1, 7
    cmove r11, r10
    cmp %1, 8
    cmove r11, r10
    cmp %1, 10
    cmove r11, r10
    cmp %1, 12
    cmove r11, r10

    mov r10, 28
    cmp %1, 2 ; if month is february, day is in the range 1 - 28
    cmove r11, r10

    xor rdx, rdx
    div r11 ; RDX is in the range 0 - DAY_MAX - 1
    mov %2, rdx
    inc %2 ; day is in the range 1 - DAY_MAX
%endmacro

random_birthdates:
    ; RDI - output buffer
    ; RSI - number of date_t to be stored
    ; return is void

    ; prologue
    push rbp
    mov rbp, rsp
    sub rsp, 48

    ; Since mt_rand and possibly mt_init is being called
    ; Registers may be modified
    ; So relevant values are saved in the stack

    mov qword [rsp], rdi
    mov qword [rsp + 8], rsi

    cmp byte [is_init], 1
    je .generate_dates ; if mt_state was initialized, proceed with generation
    ; otherwise, initializes it

    call mt_init
    mov byte [is_init], 1 ; sets flag to avoid reinitialization

.generate_dates:
    mov qword [rsp + 16], -1

.generation_loop:
    inc qword [rsp + 16]
    mov rcx, qword [rsp + 16]

    cmp rcx, qword [rsp + 8]
    jge .end_loop ; loops until end of array

    generate_year qword [rsp + 24]
    generate_month qword [rsp + 32]
    generate_day qword [rsp + 32], qword [rsp + 40]

    mov rax, qword [rsp + 24] ; first 2 bytes are year
    shl qword [rsp + 32], 16
    or rax, qword [rsp + 32] ; following byte is month
    shl qword [rsp + 40], 24
    or rax, qword [rsp + 40] ; last byte of 4 is day

    mov rdi, qword [rsp]
    stosd
    mov qword [rsp], rdi

    jmp .generation_loop

.end_loop:

    ; epilogue
    mov rsp, rbp
    pop rbp

    ret

estimated_probability_of_shared_birthday:
    ; RDI - number of people in group size
    ; return is the probability as a float in xmm0

    ; Algorithm is:
    ;
    ; Reserve space in the stack for group size and two counters
    ; The first for the number of iterations
    ; The second for the number of results where shared birthdays were found
    ;
    ; After that, reserve space in the stack for a number of time_t nodes equal to the group size
    ; And iterates 10000 times, filling this array each time with random birthdates
    ; Then checking if a match was found
    ; And accumulating this value in the second counter in the stack
    ;
    ; After the loop, divides the number of matches by 100 to get the estimated probability for the group size
    ; And returns it

    ; prologue
    push rbp
    mov rbp, rsp
    sub rsp, 24

    ; Variables are saved in the stack, since multiple functions are being called in the loop,
    ; and there's no guarantee that register values are being maintained

    mov qword [rbp - 24], rdi ; saves group size
    mov qword [rbp - 16], 0 ; loop counter
    mov qword [rbp - 8], 0 ; matches counter

    ; Each time_t node occupies 4 bytes

    shl rdi, 2
    sub rsp, rdi ; RSP now points to an array of time_t whose length == group size

.counting_loop:
    inc qword [rbp - 16]

    mov rdi, rsp ; moves array pointer to RDI
    mov rsi, qword [rbp - 24] ; moves group size to RSI

    call random_birthdates ; fills the array with random values

    mov rdi, qword [rbp - 24] ; moves group size to RDI
    mov rsi, rsp ; moves array pointer to RSI

    call shared_birthday ; checks if there's a match

    add qword [rbp - 8], rax ; RAX is 1 if match found, 0 otherwise

    cmp qword [rbp - 16], 10000
    jl .counting_loop ; loops 10000 times

    cvtsi2ss xmm0, qword [rbp - 8] ; moves num of matches to XMM0
    mov r10, 100
    cvtsi2ss xmm1, r10
    divss xmm0, xmm1 ; divides num of matches by LOOP_COUNT / 100 to get a percentage

    ; epilogue
    mov rsp, rbp
    pop rbp

    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
