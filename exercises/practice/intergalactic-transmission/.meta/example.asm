WRONG_PARITY equ -1

section .text
global transmit_sequence, decode_message

; extern int transmit_sequence(uint8_t *buffer, const uint8_t *message, int message_length);
transmit_sequence:
        mov     r8, rdi                 ; buffer
        test    rdx, rdx
        jz      .transmit_success

        cld
        add     rdx, rsi                ; end of message
        xor     cl, cl                  ; number of pending bits
        xor     r10, r10                ; value of pending bits

.transmit_read:
        shl     r10, 8
        lodsb                           ; read
        or      r10b, al
        add     cl, 8

.transmit_encode:
        sub     cl, 7
        mov     rax, r10
        shr     rax, cl
        shl     al, 1
        test    al, al
        jp      .transmit_write

        or     al, 1

.transmit_write:
        stosb                           ; write
        cmp     cl, 7
        je     .transmit_encode

        cmp     rsi, rdx
        jne     .transmit_read          ; more to read?

        test    cl, cl
        jz      .transmit_success       ; no more bits to transmit?

        neg     cl
        add     cl, 7                   ; 7 minus number of pending bits
        shl     r10, cl
        mov     cl, 7
        jmp     .transmit_encode

.transmit_success:
        mov     rax, rdi
        sub     rax, r8
        ret


; extern int decode_message(uint8_t *buffer, const uint8_t *message, int message_length);
decode_message:
        mov     r8, rdi                 ; buffer
        xor     cl, cl                  ; number of pending bits
        xor     r10, r10                ; value of pending bits
        cld
        add     rdx, rsi                ; end of message
        jmp     .decode_check_remaining

.decode_without_write:
        mov     cl, 7

.decode_read:
        lodsb                           ; read byte
        test    al, al
        jnp     .decode_failure

        shr     al, 1                   ; discard parity bit
        shl     r10, 7
        or      r10b, al
        test    cl, cl
        jz      .decode_without_write

        dec     cl                      ; we read 7 bits but write 8
        mov     rax, r10
        shr     rax, cl
        stosb                           ; write

.decode_check_remaining:
        cmp     rsi, rdx
        jne     .decode_read

.decode_success:
        mov     rax, rdi
        sub     rax, r8
        ret

.decode_failure:
        mov     rax, WRONG_PARITY
        ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
