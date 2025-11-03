# Introduction

## Loops

A **loop** is a sequence of instructions that is potentially executed more than once, until an ending condition is met.

In x86-64 a loop is usually created with a jump to a previous label:

```nasm
example_loop:
    ...
    jmp example_loop
```

Note that an unconditional jump to a previous label will always transfer execution to this label.
This means the loop will keep repeating forever, unless there is another loop to outside the repeated sequence.

For instance, this loop does not end:

```nasm
infinite_loop:
    inc rax
    jmp infinite_loop ; always jumps to 'infinite_loop', repeating 'inc rax' forever
```

And this loop may end, depending on the condition being met:

```nasm
maybe_finite_loop:
    cmp rax, 1
    je out_of_loop ; jumps to 'out_of_loop' if rax == 1, breaking the loop

    inc rax
    jmp maybe_finite_loop ; always jumps to 'infinite_loop'
out_of_loop:
    ...
```

There are some instructions which can be used to create loop-like behavior.
One of them is **loop**.

Its single operand is a label which has the address to the start of the loop.

The `loop` instruction uses the value in `rcx` as a counter, decrementing it by 1 each time.
Once the value in `rcx` reaches zero, the loop ends and execution continues sequentially:

```nasm
section .text
fn:
    mov rax, 0
    mov rcx, 10
.example:
    inc rax
    loop .example ; this repeats the sequence starting in .example 10 times (the value in rcx)
                  ; at each time, rcx is decremented by 1
```

There are two variants for the `loop` instruction that check for the zero flag (`ZF`) at each iteration.
Apart from stopping the loop once `rcx` reaches zero, they also stop when the condition is _not_ met.

| instruction       | condition |
|-------------------|-----------|
| `loope`/`loopz`   | `ZF` == 1 |
| `loopne`/`loopnz` | `ZF` == 0 |

The `ZF` **is not tested** by those instructions.
There must be a `cmp`, `test`, or another instruction that changes `ZF` before them:

```nasm
section .text
fn:
    mov rax, 0
    mov rcx, 10
.example:
    inc rax
    cmp rax, 3
    loopne .example ; this repeats the sequence starting in .example while rcx > 0 and rax != 3
```
