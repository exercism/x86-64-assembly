extern printf

section .data
fmtd: db "%d", 10, 0
fmtzd: db "%zd", 10, 0
fmtu: db "%u", 10, 0
fmtzu: db "%zu", 10, 0

%macro debug_entry 0

    ; Function prologue
    push rbp
    mov rbp, rsp

    ; Align stack pointer
    ; and rsp, -8

    ; Preserve caller-saved registers
    push rax
    push rcx
    push rdx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11

    ; Preserve floating point registers
    sub rsp, 120
    movsd [rsp], xmm0
    movsd [rsp + 8], xmm1
    movsd [rsp + 16], xmm2
    movsd [rsp + 24], xmm3
    movsd [rsp + 32], xmm4
    movsd [rsp + 40], xmm5
    movsd [rsp + 48], xmm6
    movsd [rsp + 56], xmm7
    movsd [rsp + 64], xmm8
    movsd [rsp + 72], xmm9
    movsd [rsp + 80], xmm10
    movsd [rsp + 88], xmm11
    movsd [rsp + 96], xmm12
    movsd [rsp + 104], xmm13
    movsd [rsp + 112], xmm14
    movsd [rsp + 120], xmm15

%endmacro

%macro debug_leave 0

    ; Restore floating point registers
    add rsp, 120
    movsd xmm15, [rsp + 120]
    movsd xmm14, [rsp + 112]
    movsd xmm13, [rsp + 104]
    movsd xmm12, [rsp + 96]
    movsd xmm11, [rsp + 88]
    movsd xmm10, [rsp + 80]
    movsd xmm9, [rsp + 72]
    movsd xmm8, [rsp + 64]
    movsd xmm7, [rsp + 56]
    movsd xmm6, [rsp + 48]
    movsd xmm5, [rsp + 40]
    movsd xmm4, [rsp + 32]
    movsd xmm3, [rsp + 24]
    movsd xmm2, [rsp + 16]
    movsd xmm1, [rsp + 8]
    movsd xmm0, [rsp]

    ; Restore caller-saved registers
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rax

    ; Function epilogue
    mov rsp, rbp
    pop rbp

%endmacro

%macro debugd8 1

    debug_entry
    movsx rsi, %1
    lea rdi, [rel fmtd]
    xor eax, eax
    call printf wrt ..plt
    debug_leave

%endmacro

%macro debugd16 1

    debugd8 %1

%endmacro

%macro debugd32 1

    debugd8 %1

%endmacro

%macro debugd64 1

    debug_entry
    mov rsi, %1
    lea rdi, [rel fmtzd]
    xor eax, eax
    call printf wrt ..plt
    debug_leave

%endmacro

%macro debugu8 1

    debug_entry
    movzx esi, %1
    lea rdi, [rel fmtu]
    xor eax, eax
    call printf wrt ..plt
    debug_leave

%endmacro

%macro debugu16 1

    debugu8 %1

%endmacro

%macro debugu32 1

    debug_entry
    mov esi, %1
    lea rdi, [rel fmtu]
    xor eax, eax
    call printf wrt ..plt
    debug_leave

%endmacro

%macro debugu64 1

    debug_entry
    mov rsi, %1
    lea rdi, [rel fmtzu]
    xor eax, eax
    call printf wrt ..plt
    debug_leave

%endmacro
