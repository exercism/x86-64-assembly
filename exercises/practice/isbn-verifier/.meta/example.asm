section .text
global is_valid

; rdi - address of isbn string
; rax - result (boolean)
; ecx - weight, counts down to 0
; dl - current digit
; r8 - sum
; r9 - weighted sum
is_valid:
    xor rax, rax
    mov ecx, 10
    xor rdx, rdx
    xor r8, r8
    xor r9, r9
    jmp .load_byte

.found_x:
    cmp ecx, 1
    jne .report_invalid       ; X in non-final position
    mov dl, 10

.update_sums:
    add r8, rdx
    add r9, r8                ; Increase weighed sum using sum
    dec ecx

.load_byte:
    mov dl, byte [rdi]        ; Load isbn character
    inc rdi
    test dl, dl
    jz .report                ; Reached end of string
    cmp dl, '-'
    je  .load_byte            ; Ignore hyphens
    test ecx, ecx
    jz .report_invalid        ; Too many characters
    cmp dl, 'X'
    je  .found_x
    cmp dl, '0'
    jl .report_invalid
    cmp dl, '9'
    jg .report_invalid
    sub dl, '0'               ; Convert digit to value
    jmp .update_sums

.report_invalid:
                              ; rax is already 0
    ret

.report:
    test ecx, ecx
    jnz .report_invalid       ; Reject non-zero weight
    mov cx, 11
                              ; dx is already 0
    mov rax, r9
    div cx                    ; Divide weighted sum dx:ax by 11
    cmp dx, 0                 ; Check if remainder is 0
    sete al                   ; If so, return true, else return false
                              ; Other bytes of rax are already 0
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
