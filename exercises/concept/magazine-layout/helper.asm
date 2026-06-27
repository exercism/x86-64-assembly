%include "magazine_layout.asm"

section .bss
align 8
global reg_before
global reg_after
reg_before: resq 16        ; rax,rbx,rcx,rdx,rsi,rdi,rbp,rsp,r8..r15
reg_after:  resq 16
scratchbuf: resb 128

section .text

%macro snapshot 1
    mov [rel %1 + 8*0],  rax
    mov [rel %1 + 8*1],  rbx
    mov [rel %1 + 8*2],  rcx
    mov [rel %1 + 8*3],  rdx
    mov [rel %1 + 8*4],  rsi
    mov [rel %1 + 8*5],  rdi
    mov [rel %1 + 8*6],  rbp
    mov [rel %1 + 8*8],  r8
    mov [rel %1 + 8*9],  r9
    mov [rel %1 + 8*10], r10
    mov [rel %1 + 8*11], r11
    mov [rel %1 + 8*12], r12
    mov [rel %1 + 8*13], r13
    mov [rel %1 + 8*14], r14
    mov [rel %1 + 8*15], r15
%endmacro

%macro load_sentinels 0
    mov rax, 0xA1A1A1A1A1A1A1A1
    mov rbx, 0xB2B2B2B2B2B2B2B2
    mov rcx, 0xC3C3C3C3C3C3C3C3
    mov rdx, 0xD4D4D4D4D4D4D4D4
    mov rsi, 0x5151515151515151
    mov rdi, 0x6161616161616161
    mov rbp, 0x7171717171717171
    mov r10, 0xAAAAAAAAAAAAAAAA
    mov r11, 0xBBBBBBBBBBBBBBBB
    mov r12, 0xCCCCCCCCCCCCCCCC
    mov r13, 0xDDDDDDDDDDDDDDDD
    mov r14, 0xEEEEEEEEEEEEEEEE
    mov r15, 0x1F1F1F1F1F1F1F1F
%endmacro

%macro save_callee 0
    push rbx
    push rbp
    push r12
    push r13
    push r14
    push r15
%endmacro
%macro restore_callee 0
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbp
    pop rbx
%endmacro

global format_metrics
format_metrics:
    mov qword [rdi + 0],  COLUMN_COUNT
    mov qword [rdi + 8],  COLUMN_STRIDE
    mov qword [rdi + 16], SPACE
    mov qword [rdi + 24], RULE
    mov qword [rdi + 32], RULE_WIDTH
    mov qword [rdi + 40], PLAIN
    mov qword [rdi + 48], RULED
    mov qword [rdi + 56], BOXED
    ret

global reset_galley
reset_galley:
    fill_run rdi, rsi, SPACE
    ret

global column_offsets
column_offsets:
    lay_columns rdi, rsi
    ret

global standing_headers
standing_headers:
    set_header rdi, 0
    set_header rdi + rsi, 1
    set_header rdi + rsi*2, 2
    ret

global frame_page
frame_page:
    fill_run rdi, rsi, SPACE
    fill_run rdi, RULE_WIDTH, RULE
    ret

global probe_fill_run
probe_fill_run:
    save_callee
    load_sentinels
    lea r8, [rel scratchbuf]
    mov r9, 5
    snapshot reg_before
    fill_run r8, r9, SPACE
    snapshot reg_after
    restore_callee
    ret

global probe_lay_columns
probe_lay_columns:
    save_callee
    load_sentinels
    lea r8, [rel scratchbuf]
    mov r9, 3
    snapshot reg_before
    lay_columns r8, r9
    snapshot reg_after
    restore_callee
    ret

global probe_set_header
probe_set_header:
    save_callee
    load_sentinels
    lea r8, [rel scratchbuf]
    snapshot reg_before
    set_header r8, 1
    snapshot reg_after
    restore_callee
    ret

global counter_is_rcx
counter_is_rcx:
    save_callee
    mov rax, 0xFEDCBA0987654321
    mov rbx, 0xFEDCBA0987654321
    mov rdx, 0xFEDCBA0987654321
    mov rsi, 0xFEDCBA0987654321
    mov rdi, 0xFEDCBA0987654321
    mov rbp, 0xFEDCBA0987654321
    mov r8,  0xFEDCBA0987654321
    mov r9,  0xFEDCBA0987654321
    mov r10, 0xFEDCBA0987654321
    mov r11, 0xFEDCBA0987654321
    mov r12, 0xFEDCBA0987654321
    mov r13, 0xFEDCBA0987654321
    mov r14, 0xFEDCBA0987654321
    mov r15, 0xFEDCBA0987654321
    mov rcx, 0x1234567890ABCDEF
    mov rax, COUNTER
    restore_callee
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
