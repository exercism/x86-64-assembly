section .data
msg: db "Hello, World!", 0

section .text
global hello
hello:
    mov rax, msg
    ret
