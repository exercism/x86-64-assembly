section .text
global flatten
flatten:
    xor eax, eax
check:
    mov edx, dword [rsi] ; tag
    cmp edx, 1
    jb end
    je value

    mov rcx, qword [rsi + 8]  ; num elements in array

    test ecx, ecx
    jz end

    mov rsi, qword [rsi + 16] ; array pointer

    ; sizeof(box_t) == 24
    ; tag      -> 4 bytes
    ; padding  -> 4 bytes
    ; contents -> 16 bytes (sizeof(array_t))

    lea rcx, [rcx + 2*rcx]
    lea rcx, [rsi + 8*rcx]    ; end pointer = start pointer + 24 * length
    push rcx                  ; save end pointer
visit:
    push rsi                  ; save crt pointer

    call check

    pop rsi                   ; restore crt pointer
    add rsi, 24               ; move to next pointer

    cmp rsi, qword [rsp]
    jb visit                  ; do... while (crt != end);

    add rsp, 8
    ret

value:
    mov rdx, qword [rsi + 8]
    mov [rdi + 8*rax], rdx
    inc eax
end:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
