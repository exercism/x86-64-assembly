section .text
global triplets_with_sum

; a + b + c = n,  a**2 + b**2 = c**2
; a**2 = (n - a - b)**2 - b**2
; b = n (n - 2 a) / 2 (n - a)

; rdi - n
; rsi - ptr pa
; rdx - remainder (initially ptr pb)
; rcx - ptr pc
; rax - b (finally triplet count)
; r8 - ptr pb
; r9 - a
; r10 - triplet count
; r11 - denominator, c

; extern size_t triplets_with_sum(uint64_t n, uint64_t *pa, uint64_t *pb, uint64_t *pc);
triplets_with_sum:
    mov r8, rdx ; pb
    xor r10, r10 ; 0 triplets so far
    cmp rdi, 2
    jl .done ; reject n < 2 and reject n >= 2^63

    xor r9, r9 ; a
    jmp .advance

.consider:
    test rdx, rdx
    jnz .advance ; skip if b is not an exact integer

    shr r11, 1
    sub r11, rax ; c = n - a - b
    mov [rsi + r10*8], r9 ; store a
    mov [r8 + r10*8], rax ; store b
    mov [rcx + r10*8], r11 ; store c
    inc r10 ; triplet count

.advance:
    inc r9 ; a
    mov r11, rdi
    sub r11, r9 ; n - a
    mov rax, r11
    shl r11, 1 ; denominator = 2 (n - a)
    sub rax, r9 ; n - 2 a
    mul rdi ; numerator rdx:rax = n (n - 2 a)
    div r11 ; sets rax b, rdx remainder
    cmp r9, rax
    jbe .consider ; while a <= b

.done:
    mov rax, r10 ; triplet count
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
