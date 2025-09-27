# Introduction

A `loop` is a sequence of instructions that is potentially executed more than once, until an ending condition is met.

In x86-64 a loop is usually created with a jump to a previous label:

```nasm
example_loop:
    ...
    jmp example_loop
```

Notice that an unconditional jump to a previous label will always transfer execution to this label.
So, the loop will keep repeating forever, unless there's another jump in the repeated sequence to a label out of the loop.

For instance, this loop does not end:

```nasm
infinite_loop:
    inc rax
    jmp infinite_loop ; always jumps to 'infinite_loop', repeating 'inc rax' forever
```

And this loop may end, depending on the condition being met:

```nasm
maybe_finite_loop:
    cmp rax, 0
    je out_of_loop ; jumps to 'out_of_loop' if rax == 0, breaking the loop

    inc rax
    jmp maybe_finite_loop ; always jumps to 'infinite_loop'
out_of_loop:
    ...
```

There are some instructions which can be used to create loop-like behavior.
One of them is `loop`.

Its single operand is a label which has the address to the start of the loop.

The `loop` instruction uses the value in `rcx` as a counter.
Once the value in `rcx` reaches zero, the loop ends and execution continues sequentially.

There are two variants for the `loop` instruction, `loope` and `loopne`.

Apart from stopping the loop once `rcx` reaches zero, they also stop it if the `ZF` is set or cleared, respectively.

The `ZF` **is not tested** by those instructions.
There must be a `cmp`, `test`, or another instruction that changes `ZF` before them.
