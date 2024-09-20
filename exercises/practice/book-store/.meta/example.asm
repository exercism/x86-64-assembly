default rel

section .rodata
price: dq 0, 3000, 2560, 2160, 1520, 800

section .text
global total
total:
    cld
    sub rsp, 48 ; reserve stack space
    xor rax, rax
    mov rcx, 5

.zero:
    mov [rsp + 8*rcx], rax ; set book tally to 0
    loop .zero

    mov rcx, rdi
    jrcxz .sort ; skip read loop if there are no books

.read:
    lodsw
    inc qword [rsp + 8*rax] ; increment book tally
    loop .read


.sort:
    ; Bubble sort
    xor r8, r8 ; number of swaps during scan
    mov rcx, 4

.scan:
    mov r9, qword [rsp + 8*rcx]
    mov r10, qword [rsp + 8*rcx + 8]
    cmp r9, r10
    jbe .next_pair

    mov qword [rsp + 8*rcx], r10
    mov qword [rsp + 8*rcx + 8], r9
    inc r8 ; count swap

.next_pair:
    loop .scan

    test r8, r8
    jnz .sort ; repeat until a scan has no swaps

.differences:
    ; Compute group counts
    mov rdx, qword [rsp + 8] ; groups of 5
    mov r8, qword [rsp + 16]
    mov r9, qword [rsp + 24]
    mov r10, qword [rsp + 32]
    mov r11, qword [rsp + 40]
    sub r11, r10
    sub r10, r9
    sub r9, r8
    sub r8, rdx
    mov qword [rsp + 16], r8 ; groups of 4
    mov qword [rsp + 24], r9 ; groups of 3
    mov qword [rsp + 32], r10 ; groups of 2
    mov qword [rsp + 40], r11 ; groups of 1


    ; Two groups of 4 books are cheaper than a group of 5 books and a group of 4 books
    mov r8, qword [rsp + 8] ; groups of 5 books
    mov r9, qword [rsp + 16] ; groups of 4 books
    mov r10, qword [rsp + 24] ; groups of 3 books
    mov r11, r10
    cmp r8, r10
    cmovb r11, r8 ; r11 now has min(groups of 5 books, groups of 3 books)
    sub r8, r11
    sub r10, r11
    shl r11, 1
    add r9, r11
    mov qword [rsp + 8], r8
    mov qword [rsp + 16], r9
    mov qword [rsp + 24], r10

    xor r10, r10
    lea r11, [price]
    mov rcx, 5

.multiply:
    mov rax, qword [rsp + rcx*8] ; number of groups
    mov rdx, qword [r11 + rcx*8] ; price of each group
    mul rdx
    add r10, rax ; accumulate total price
    loop .multiply

    mov rax, r10
    add rsp, 48 ; restore original stack pointer
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
