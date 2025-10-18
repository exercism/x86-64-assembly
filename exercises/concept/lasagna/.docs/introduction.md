# Introduction

## Basics

### Comments

The x86-64 track in Exercism uses **NASM** (The Netwide Assembler) as its assembler.
In NASM, comments are prefixed by a semicolon (`;`).

Comments may be placed anywhere in the program and everything that comes after a `;` is ignored by the assembler.

### Constants

An assembler-time constant can be defined in NASM using [equ][equ].
For instance, this defines a constant named `UNIVERSE` with the value `42`:

```nasm
UNIVERSE equ 42
```

Constants are evaluated once, when defined, and can *not* be redefined later.

### General Purpose Registers (GPRs)

In assembly, instead of variables, we typically use registers to store values.
A **CPU Register** is a piece of fast memory inside a computer's processor.
Most computations are carried out in the CPU's registers.

Some of the registers are used for a variety of different computations and are called **General Purpose Registers (GPRs)**.
Others have special or dedicated purposes.

In x86-64, there are 16 64-bit General Purpose Registers (GPRs), which can also be accessed as 32-bit, 16-bit, or 8-bit.
The GPRs are described below, where `n` in `rn` ranges from 8 to 15: `r8`, `r9`, `r10`, `r11`, `r12`, `r13`, `r14` and `r15`.

| 64-bit    | 32-bit    | 16-bit    | 8-bit     |
|:---------:|:---------:|:---------:|:---------:|
|   rax     |   eax     |   ax      |   ah/al   |
|   rbx     |   ebx     |   bx      |   bh/bl   |
|   rcx     |   ecx     |   cx      |   ch/cl   |
|   rdx     |   edx     |   dx      |   dh/dl   |
|   rsi     |   esi     |   si      |   sil     |
|   rdi     |   edi     |   di      |   dil     |
|   rbp     |   ebp     |   bp      |   bpl     |
|   rsp     |   esp     |   sp      |   spl     |
|   rn      |   rnd     |   rnw     |   rnb     |

When using less than 64-bits, the bits accessed are usually from the lower portion of the register.
The exception to this rule are `ah`, `bh`, `ch` and `dh`, which access the upper 8-bits from the 16-bits portion of the register.

Illustration of how the bits are accessed for the `rax` register:

```
+--------+---------------------------------------+
| 64-bit |                  rax                  |
+--------+-------------------+-------------------+
| 32-bit |                   |        eax        |
+--------+-------------------+---------+---------+
| 16-bit |                             |    ax   |
+--------+-----------------------------+----+----+
| 8-bit  |                             | ah | al |
+--------+-----------------------------+----+----+
```

Some of those registers must be preserved accross function calls: `rbp`, `rsp`, `rbx`, `r12`, `r13`, `r14` and `r15`.
Failing to preserve them may lead to an error or to undefined behaviour.

The others are not preserved and may be used freely: `rax`, `rcx`, `rdx`, `rdi`, `rsi`, `r8`, `r9`, `r10` and `r11`.

### Instructions

Instructions are pieces of computations a CPU can perform.
They usually have the following form:

```nasm
name destination, source
```

So, the name of the instruction is placed first, then at least one whitespace, followed by the destination operand, a comma (`,`) and finally a source operand.
The source operand isn't typically modified by an instruction, just the destination operand.

Unless otherwise noted, both operands must have the same size.
So, for example, if the source operand has 16-bits, the destination operand must also have 16-bits.

For instance, to store a value in a register, we can use the `mov` instruction:

```nasm
mov rax, 42  ; rax = 42
             ; mov is the name, rax is the destination operand and 42 is the source operand
```

The snippet above stores the value `42` in all 64-bits of the `rax` register, which is the destination operand for the instruction.

Note that writing to a 32-bit register also clears the upper bits, so `mov eax, 42` is the same as `mov rax, 42`.
This is not true for 16-bit and 8-bit registers.

For the arithmetic operations addition, subtraction, and multiplication, we can use the `add`, `sub`, and `imul` instructions:

```nasm
add rax, rsi ; rax = rax + rsi
imul rax, rdi ; rax = rax * rdi
sub rax, r8 ; rax = rax - r8
```
### Functions

Instructions are organized in functions.
All functions are placed in the **section .text** of the source file.

A function declaration consists of:

1. A label with the name of the function, followed by a `:`.
2. The instructions that define the function.
3. The return instruction, `ret`.

This track uses the System V AMD64 ABI calling convention and the six first integers arguments are passed to a function in registers.
They are passed in the following order: `rdi`, `rsi`, `rdx`, `rcx`, `r8`, and `r9`.

An integer value is returned from the function in the `rax` register.

To call a function, we use the `call` instruction.
A function can be called anywhere in the same source file.
In order to make a function visible to other source files, the `global` directive must be used.

For instance, this declares a function `sum`:

```nasm
section .text ; functions are placed here

global sum ; sum is visible to other source files

sum:
    ; first argument is passed in rdi
    ; second argument is passed in rsi
    ; return value is placed in rax

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
