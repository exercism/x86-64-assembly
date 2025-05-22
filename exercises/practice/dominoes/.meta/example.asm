section .text
global can_chain


; int root(int number, void*, uint8_t *table);
root:
        mov     eax, edi

.root_loop:
        mov     edi, eax                ; previous
        mov     al, [rdx + rdi]
        cmp     edi, eax
        jne     .root_loop

        ret


; void merge(size_t domino_count, const domino_t *dominoes, uint8_t *table);
merge:
        mov     r8, rdi
        shl     r8, 2                   ; number of bytes occupied by dominoes array
        xor     rdi, rdi

.merge_loop:
        sub     r8, 2
        mov     di, [rsi + r8]          ; number on domino half
        call    root
        mov     r10d, eax

        sub     r8, 2
        mov     di, [rsi + r8]          ; number on domino half
        call    root

        mov     [rdx + r10], al         ; link domino halves in table
        test    r8, r8
        jnz     .merge_loop

        ret


; void tally(size_t domino_count, const domino_t *dominoes, uint8_t *table);
tally:
        mov     r8, rdi
        shl     r8, 2                   ; number of bytes occupied by dominoes array
        xor     rax, rax
        mov     [rdx], rax
        mov     [rdx + 8], rax

.tally_loop:
        sub     r8, 2
        mov     ax, [rsi + r8]          ; number on domino half
        mov     cl, [rdx + rax]
        inc     cl                      ; increment tally
        mov     [rdx + rax], cl
        test    r8, r8
        jnz     .tally_loop

        ret


; bool check(const void *, const void *, uint8_t *table);
check:
        mov     rcx, 16

.check_loop:
        dec     rcx
        mov     al, [rdx + rcx]
        test    al, 1
        jnz     .check_reject

        mov     r8b, 255
        test    al, al
        cmovnz  r8w, cx
        mov     [rdx + rcx], r8b        ; cl, or 255 if tally was 0

        test    cl, cl
        jnz     .check_loop

        mov     rax, 1
        ret

.check_reject:
        xor     rax, rax
        ret


; extern bool can_chain(size_t domino_count, const domino_t *dominoes);
can_chain:
        sub     rsp, 16
        test    rdi, rdi
        jz      .accept

        mov     r11, rdi
        mov     rdx, rsp
        call    tally

        mov     rdi, r11
        call    check

        test    al, al
        jz      .reject

        mov     rdi, r11
        call    merge

        mov     rcx, 16
        xor     r9, r9                  ; number of roots found

.can_chain_loop:
        dec     cl
        mov     al, [rdx + rcx]

        mov     r10, r9
        inc     r10
        cmp     al, cl
        cmovz   r9, r10                 ; conditional increment

        test    cl, cl
        jnz     .can_chain_loop

        cmp     r9, 1
        jne     .reject

.accept:
        mov     rax, 1
        add     rsp, 16                 ; restore stack pointer
        ret

.reject:
        xor     rax, rax
        add     rsp, 16                 ; restore stack pointer
        ret
