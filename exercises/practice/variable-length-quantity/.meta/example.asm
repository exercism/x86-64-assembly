section .text
global encode
global decode

; size_t encode(uint8_t *buffer, const uint32_t *integers, size_t integer_count)
encode:
    ; rdi - output buffer of uint8_t
    ; rsi - input array of uint32_t integers
    ; rdx - size of input array as size_t (uint64_t)
    ; return is size of output buffer as a uint64_t in rax

    ; This is the translation to assembly of my solution for JS
    ;
    ; I mask each integer with max significant byte (all bits set, save the last)
    ; The result is pushed to the stack and the integer is shifted 7 bits to the right
    ; Then, while the integer is non-zero, this process is repeated
    ; but setting the last bit on each resulting byte
    ; At the end, the resulting array is moved to the buffer in reverse order (LIFO)
    ; There's a counter for the num of resulting bytes for the integer, so as to set boundaries for this transfer
    ; This process is repeated for each integer in the input array
    ; The returning size is rbp - rsp (since rsp is continuosly reduced with all resulting bytes)

    ; prologue
    push rbp
    mov rbp, rsp

    mov r11, 1
    shl r11, 7 ; last bit set

    mov r10, r11
    dec r10 ; mask

    xor rax, rax
    mov rcx, rdx ; for using LOOP
.main_loop:
    xor r8, r8 ; counter of resulting bytes for each iteration

    lodsd ; current integer

    mov r9, r10
    and r9, rax ; byte filled only with significant bits

    dec rsp
    inc r8
    mov byte [rsp], r9b ; adds byte

    shr rax, 7 ; shifts integer for processing remaining bits
.inner_loop:
    cmp rax, 0
    je .break_inner ; iterates while integer is non-zero

    mov r9, r10
    and r9, rax ; significant bits after mask
    or r9, r11 ; sets most significant bit

    dec rsp
    inc r8
    mov byte [rsp], r9b ; adds byte

    shr rax, 7
    jmp .inner_loop

.break_inner:
    ; integer is zero now, the bytes must be moved to buffer

    mov rax, rsi
    mov rsi, rsp

    xchg r8, rcx ; rcx now holds num of bytes, for using REP

    rep movsb

    mov rsi, rax
    xchg r8, rcx ; restore rcx, for using LOOP

    loop .main_loop ; continues until end of input array

    ; sets rax with the difference between rbp and rsp,
    ; which is the total num of bytes added to the buffer

    mov rax, rbp
    sub rax, rsp

    mov rsp, rbp
    pop rbp
    ret

; size_t decode(uint32_t *buffer, const uint8_t *integers, size_t integer_count)
decode:
    ; rdi - output buffer of uint32_t
    ; rsi - input array of uint8_t integers
    ; rdx - size of input array as size_t (uint64_t)
    ; return is size of output buffer as a uint64_t in rax

    ; This is the translation to assembly of my solution for JS
    ;
    ; I continuosly extract bytes from input array until its end
    ; While this byte has the last bit set, I remove its last bit (using XOR)
    ; and shift it left 7 bits
    ; before accumulating the result using OR
    ; Once the last bit is not set, the accumulating result is added to output
    ; and a new byte is extracted from input
    ; There's no need for using a stack array because the processing order
    ; is the same as the inserting order in the buffer

    mov r11, 1
    shl r11, 7 ; max

    xor r8, r8 ; counter for elements in buffer
.main_loop:
    cmp rdx, 0
    je .end_main_loop ; end of input aray

    xor rax, rax
    lodsb
    dec rdx ; extracts a value from input and decrements size counter

    xor r9, r9 ; accumulator
.inner_loop:
    mov r10, r11
    and r10, rax

    cmp r10, 0
    je .end_inner_loop ; if last bit is not set, result is ready to push to buffer

    mov r10, r11
    xor r10, rax ; removes last bit
    or r9, r10 ; accumulates in r9
    shl r9, 7 ; shifts for next iteration

    lodsb
    dec rdx ; extracts a value from input and decrements size counter

    jmp .inner_loop

.end_inner_loop:
    or rax, r9 ; accumulates the remaining byte
    stosd ; stores in buffer
    inc r8 ; increases counter of elements in buffer

    jmp .main_loop

.end_main_loop:
    mov rax, r8 ; moves counter to rax, for returning
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
