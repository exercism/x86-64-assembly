section .text
triangle_equality:
        movsd   xmm2, QWORD [rsp+16]
        movsd   xmm1, QWORD [rsp+24]
        movsd   xmm0, QWORD [rsp+8]
        movapd  xmm3, xmm2
        addsd   xmm3, xmm1
        comisd  xmm3, xmm0
        jbe     .false
        movapd  xmm3, xmm0
        addsd   xmm3, xmm1
        comisd  xmm3, xmm2
        jbe     .false
        addsd   xmm0, xmm2
        comisd  xmm0, xmm1
        seta    al
        ret
.false:
        xor     eax, eax
        ret

global is_equilateral:
is_equilateral:
        push    QWORD [rsp+24]
        push    QWORD [rsp+24]
        push    QWORD [rsp+24]
        call    triangle_equality
        add     rsp, 24
        test    al, al
        je      .ret
        movsd   xmm0, QWORD [rsp+16]
        movsd   xmm1, QWORD [rsp+8]
        ucomisd xmm0, xmm1
        jp      .false
        jne     .false
        movsd   xmm1, QWORD [rsp+24]
        ucomisd xmm0, xmm1
        mov     dl, 0
        setnp   al
        cmovne  eax, edx
        ret
.false:
        xor     eax, eax
.ret:
        ret
global is_isosceles:
is_isosceles:
        movsd   xmm5, QWORD [rsp+8]
        movsd   xmm6, QWORD [rsp+16]
        movsd   xmm4, QWORD [rsp+24]
        push    QWORD [rsp+24]
        push    QWORD [rsp+24]
        push    QWORD [rsp+24]
        call    triangle_equality
        add     rsp, 24
        test    al, al
        je      .ret
        ucomisd xmm6, xmm4
        mov     cl, 0
        setnp   al
        cmovne  eax, ecx
        ucomisd xmm5, xmm6
        setnp   dl
        cmovne  edx, ecx
        or      eax, edx
        ucomisd xmm5, xmm4
        setnp   dl
        cmovne  edx, ecx
        or      eax, edx
.ret:
        ret

global is_scalene
is_scalene:
        push    QWORD [rsp+24]
        push    QWORD [rsp+24]
        push    QWORD [rsp+24]
        call    is_equilateral
        add     rsp, 24
        test    al, al
        jne     .false
        push    QWORD [rsp+24]
        push    QWORD [rsp+24]
        push    QWORD [rsp+24]
        call    is_isosceles
        add     rsp, 24
        test    al, al
        jne     .false
        jmp     triangle_equality
.false:
        xor     eax, eax
        ret


%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif