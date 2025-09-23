# Introduction

## Basics

### Comments

The x86-64 track in Exercism uses NASM (The Netwide Assembler) as its assembler.

In NASM, comments are prefixed by a semicolon (`;`).

Comments may be placed anywhere in the program and everything that comes after a `;` is ignored by the assembler.

### Constants

An assembler-time constant can be defined using `equ`.

For instance, this defines a constant named `UNIVERSE` with the value `42`:

```nasm
UNIVERSE equ 42
```

Constants are evaluated once, when defined, and can *not* be redefined later.

### General-Purpose Registers

In assembly, there are no variables, instead we typically use registers to store values.
Most computations are performed using registers.

Some of the registers are used for a variety of different computations and are called `general-purpose`.
Others have special or dedicated purposes.

In x86-64 there are 16 64-bit General Purpose Registers (GPRs), which can also be accessed as 32-bit, 16-bit, or 8-bit.

Some of those registers must be preserved accross function calls: `rbp`, `rsp`, `rbx`, `r12`, `r13`, `r14` and `r15`.
Failing to preserve them may lead to an error or to undefined behaviour.

The others are not preserved and may be used freely: `rax`, `rcx`, `rdx`, `rdi`, `rsi`, `r8`, `r9`, `r10` and `r11`.

### Instructions

Instructions are pieces of computations a CPU can perform.

They usually have the following form:

```nasm
opcode destination, source
```

So, the `opcode` is placed first, then at least one whitespace, followed by the destination operand, a comma (`,`) and finally a source operand.

The source operand isn't typically modified by an instruction, just the destination operand.

To store a value in a register, we can use the `mov` instruction:

```nasm
mov rax, 42  ; rax = 42
             ; mov is the opcode, rax is the destination operand and 42 is the source operand
```

For the arithmetic operations addition, subtraction, and multiplication, we can use the `add`, `sub` and `imul` instructions:

```nasm
add rax, rsi ; rax += rsi
sub rax, r8 ; rax -= r8
imul rax, rdi ; rax *= rdi
```

### Functions

Instructions are organized in functions.

A function declaration consists of:

1- a label with the name of the function, followed by a `:`;

2- the instructions that define the function; and

3- the return instruction, `ret`.

To call a function, we use the `call` instruction.

The six first integers arguments are passed to a function in the following registers, in this order: `rdi`, `rsi`, `rdx`, `rcx`, `r8`, and `r9`.

An integer value is returned from the function in the `rax` register.

For instance, this declares a function `sum`:

```nasm
section .text

global sum
sum:
    ; first argument is passed in rdi
    ; second argument is passed in rsi
    ; return is passed in rax

    mov rax, rdi ; rax is now equal to rdi
    add rax, rsi ; rax = rax + rsi

    ret ; function return
```

And this calls our `sum` function with the arguments 3 and 5:

```nasm
mov rdi, 3  ; First argument in rdi
mov rsi, 5  ; Second argument in rsi
call sum

; The rax register now contains the value 8 (3 + 5), after sum returns
```
