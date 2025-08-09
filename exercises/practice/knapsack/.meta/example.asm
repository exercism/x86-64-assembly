section .text
global maximumValue

maximumValue:
    ; Argument registers
    ; %rdi - input items array
    ; %esi - number of items
    ; %edx - maximum weight

    cmp esi, 0
    jg .more

    ; this must mean there are no items
    mov rax, 0
    ret

.more:
    ; Check if there is enough space for the item
    mov r10d, dword [rdi + 4]
    mov r11, rdx
    sub r11d, r10d
    js .skip_item

    ; Next step is to find what value in can get with the item
    dec esi
    add rdi, 8

    ; Store the values for the next call
    push rdx
    push rsi
    push rdi

    mov edx, r11d

    ; What value can we get if item was included?
    call maximumValue

    pop rdi
    pop rsi
    pop rdx

    ; Load the item's value to calculate the total value with the item.
    ; Subtract 8 from rdi because we've already moved it forward to next item.
    mov r10d, dword [rdi - 8]
    add eax, r10d

    push rax

    ; What value can we get without the item?
    call maximumValue

    pop r11

    ; Which value is higher?
    cmp rax, r11
    jge .return

    ; Here, the value with the item must be better
    mov rax, r11

.return:
    ret

.skip_item:
    add rdi, 8
    dec esi
    call maximumValue

    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
