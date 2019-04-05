section .data
msg: db "", 0

section .text
global hello
hello:
    mov rax, msg
    ret
