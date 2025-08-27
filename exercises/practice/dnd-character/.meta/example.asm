default rel

SEED equ 1812433253 ; Borosh-Niederreiter multiplier for modulus 2^32
                    ; in line with: https://github.com/cslarsen/mersenne-twister/blob/master/mersenne-twister.cpp

section .bss
    mt_state resd 624 ; array to hold the state of the generator
    index resd 1 ; current index
    is_init resb 1 ; flag for lazy initialization of state array

section .text

global modifier
global ability
global make_dnd_character

; The algorithm for the 32-bit Mersenne Twister PRNG (mt19937) was taken from:
; https://en.wikipedia.org/wiki/Mersenne_Twister#C_code
;
; The seed chosen was the "Borosh-Niederreiter multiplier for modulus 2^32"
; in line with: https://github.com/cslarsen/mersenne-twister/blob/master/mersenne-twister.cpp
; This seed is xor-ed with the CPU timestamp
;
; This exercise was a good opportunity to see how GCC handles the "translation" between C and x86-64 assembly
; Here's the godbolt for the wikipedia implementation mentioned above: https://godbolt.org/z/acEoj15xz
; I've taken the "magic numbers" from there
;
; One nice thing I've learned with this was to use more of the stack as a fallback to store local variables,
; especially when there's a lot of them and handling the state of all the registers become too complex.
;
; Another interesting thing of note is the number of unnecessary instructions GCC sometimes generates,
; mostly on this passage between register and stack-based local variables

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

modifier:
    ; dil - score as a uint8_t
    ; return is a int8_t in al

    sub rdi, 10 ; score - 10
    sar rdi, 1 ; signed shift by 1 -> ((score - 10) / 2) rounded down
    mov rax, rdi

    ret

ability:
    ; no arguments
    ; return is a uint8_t in al

    lea r11, [is_init] ; flag

    cmp byte [r11], 1
    je .generate ; flag set, can skip initialization of mt_state
    ; otherwise, initialize it

    mov rdi, SEED
    call mt_init

    mov byte [r11], 1 ; sets flag
.generate:
    ; prologue
    push rbp
    mov rbp, rsp
    sub rsp, 4

    mov dword [rsp], 0 ; zero-initializes all 4 bytes
    mov r9, 6

    ; 4 random numbers are generated and normalized to [1-6]
    ; each valid result is stored in the stack

    ; rdtsc
    call mt_rand
    ;; rdrand rax
    xor rdx, rdx
    div r9d

    inc rdx
    mov byte [rsp], dl

    ; rdtsc
    call mt_rand
    ;; rdrand rax
    xor rdx, rdx
    div r9d

    inc rdx
    mov byte [rsp + 1], dl

    ; rdtsc
    call mt_rand
    ;; rdrand rax
    xor rdx, rdx
    div r9d

    inc rdx
    mov byte [rsp + 2], dl

    ; rdtsc
    call mt_rand
    ;; rdrand rax
    xor rdx, rdx
    div r9d

    inc rdx
    mov byte [rsp + 3], dl

    ; right now, all 4 valid die results are in the stack
    ; to get the better 3 results, a partial bubble sort is used
    ; by comparing only one of the registers with the other 3
    ; and exchanging whenever it's greater
    ; so that in the end this register holds the lesser number
    ; and the other 3 are then summed for the final result

    xor rax, rax
    mov r9b, byte [rbp - 4]

    cmp r9b, byte [rbp - 1]
    jle .comp1

    xchg r9b, byte [rbp - 1]

.comp1:
    cmp r9b, byte [rbp - 2]
    jle .comp2

    xchg r9b, byte [rbp - 2]

.comp2:
    cmp r9b, byte [rbp - 3]
    jle .get_res

    xchg r9b, byte [rbp - 3]

.get_res:
    mov al, byte [rbp - 1]
    add al, byte [rbp - 2]
    add al, byte [rbp - 3]

    ; epilogue
    mov rsp, rbp
    pop rbp
    ret

make_dnd_character:
    ; no arguments
    ; return is a struct dnd_character_t which has 8 bytes
    ; the first 6 are abilities (uint8_t) ranging between 3 - 18
    ; the last 2 are a hitpoint score (uint16_t)

    xor r8, r8
    mov rcx, 6 ; six scores
.fill_char:
    call ability ; generates one
    shl r8, 8 ; shifts previous scores
    or r8, rax ; accumulates current score
    loop .fill_char

    ; now r8 holds 6 scores in each of the lowest 6 bytes
    ; the last 2 bytes must be filled with hitpoint

    mov rdi, 255 ; mask
    shl rdi, 16 ; constitution in is the 3 byte
    and rdi, r8 ; extracts constitution score
    shr rdi, 16 ; returns to valid range

    call modifier ; gets constitution modifier in rax
    add rax, 10 ; hitpoints = 10 + modifier(constitution)

    shl rax, 48 ; shifts to accumulate
    or rax, r8 ; rax has hitpoints and abilities

    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
