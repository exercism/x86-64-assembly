section .text

%define tolower(x) add x, 32

global transform
transform:
    ; rdi - buffer output of a struct NewMap formed of a char and a int32_t
    ; rsi - input array of a struct LegacyMap, with a key (int32_t), 
    ; a size for its values array (uint8_t) and the corresponding array of chars
    ; rdx - size of input array as a uint64_t
    ; return is size of the output buffer as a uint64_t in rax

    ; This is a relatively straightforward function
    ; However, two elements of importance should be noted:
    ;
    ; First, elements in output array are tested in order of ascending key
    ;
    ; Second, both structs hold elements of different sizes so alignment is a factor
    ;
    ; Sizeof LegacyMap is 32. Offsets are 0 (key), 4 (values_size) and 5 (values)
    ; Sizeof NewMap is 8. Offsets are 0 (key) and 4 (value)

    push r12 ; extra register needed

    xor rcx, rcx
    mov r10, rsi ; saves pointer to input array
    mov r8b, 'A' ; current letter
    xor r12, r12 ; counter of elements in output array
map_letters:
    mov r9, -1 ; index of input array
mapping_loop:
    inc r9
    cmp r9, rdx
    jge finish_mapping ; end of input array

    mov rsi, r10
    imul r11, r9, 32 ; sizeof LegacyMap is 32
    add rsi, r11

    lodsd ; loads key
    mov r11d, eax ; saves key  

    lodsb ; loads values_size
    mov cl, al
find_current_letter:
    lodsb ; loads current value
    cmp al, r8b
    je add_to_output ; found letter

    loop find_current_letter

    jmp mapping_loop ; letter is not associated to current key
add_to_output:
    tolower(al)
    stosb ; saves letter as key in NewMap

    add rdi, 3 ; padding due to alignment of NewMap

    mov eax, r11d
    stosd ; saves int32_t as value in NewMap

    inc r12 ; increments output array length
finish_mapping:
    inc r8b
    cmp r8b, 'Z'
    jle map_letters

    mov rax, r12
    pop r12
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
