;
; Calculate integer square root
;
; Parameter:
;   rdi - radicand
; Returns:
;   rax - square root
;
section .text
global square_root
square_root:
                             ; rdx - current square number, n*n
                             ; rax - current odd number, 2n+1
    xor rdx, rdx             ; Current square number is 0
    mov rax, 1               ; Current odd number is 1
    jmp .compare

.advance:
    add rdx, rax             ; n*n+2n+1 == (n+1)*(n+1)
    add rax, 2               ; 2n+1+2 == 2(n+1)+1

.compare:
    cmp rdx, rdi             ; Compare current square with radicand
    jb .advance

    shr rax, 1               ; Halve rax (rounding down) to find n
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
