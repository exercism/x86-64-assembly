section .text
global truncate
truncate:
    ; rdi - output char buffer
    ; rsi - input string
    ; output buffer should be modified in place
    ; return is void

    ; UTF-8 Unicode characters may have 1, 2, 3 or 4 bytes
    ; 1 byte UTF-8 are ordinary ASCII chars and have the leading bit off
    ; 2 bytes UTF-8 have the first byte with two leading bits on and the third off
    ; 3 bytes UTF-8 have the first byte with three leading bits on and the fourth off
    ; and 4 bytes UTF-8 have the first byte with four leading bits on and the fifth off
    ;
    ; In every case where there are more than 1 byte,
    ; the non-leading bytes have the leading bit on and the second off
    ;
    ; This is a straightforward implementation which moves all the necessary bytes in the same iteration
    ; after checking for the bits in the leading byte
    ; it'd probably be safer, in case of invalid chars, to process one byte at a time and stop when reaching NULL

    mov rcx, 5
main_loop:
    mov r8b, byte [rsi]

    bt r8, 7
    jnc ASCII ; leading bit off

    bt r8, 5
    jnc two_byte ; just two leading bits on

    bt r8, 4
    jnc three_byte ; just three leading bits on

    ; all four leading bits on

    movsb
three_byte:
    movsb
two_byte:
    movsb
ASCII:
    movsb

    cmp r8b, 0
    loopne main_loop ; loops 5 times or until leading byte is NULL
end:
    mov al, 0
    stosb ; adds NULL to the end, in case it wasn't added in the loop

    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
