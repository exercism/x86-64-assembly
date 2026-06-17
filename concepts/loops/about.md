# About

A [loop][control] is a sequence of instructions that is potentially executed more than once, until an ending condition is met.

In x86-64 a loop is usually created with a jump to a previous label:

```x86asm
example_loop:
    ...
    jmp example_loop
```

Note that an unconditional jump to a previous label will always transfer execution to this label.
This means the loop will keep repeating forever, unless there is another loop to outside the repeated sequence.

For instance, this loop does not end:

```x86asm
infinite_loop:
    inc rax
    jmp infinite_loop ; always jumps to 'infinite_loop', repeating 'inc rax' forever
```

And this loop may end, depending on the condition being met:

```x86asm
maybe_finite_loop:
    cmp rax, 1
    je out_of_loop ; jumps to 'out_of_loop' if rax == 1, breaking the loop

    inc rax
    jmp maybe_finite_loop ; always jumps to 'maybe_finite_loop'
out_of_loop:
    ...
```

## Micro-Ops

A processor does not run an instruction such as `add` or `jnz` directly.
The front-end of the CPU first _decodes_ each instruction into one or more smaller internal steps, called **micro-operations** (or **micro-ops**).
The processor then schedules and executes these micro-ops, frequently several per cycle and out of their original order.

Most simple instructions decode into a single micro-op, while a more complex instruction may decode into several.
Because the processor's real workload is the stream of micro-ops, producing fewer of them for the same task is one way code becomes faster.

## Macrofusion

A counting loop almost always ends the same way: an instruction that updates a counter or compares two values, immediately followed by a conditional jump that decides whether to go around again.

```x86asm
sum_array:
    xor rax, rax     ; running total
.loop:
    add rax, [rdi]   ; add the current element
    add rdi, 8       ; advance to the next element
    sub rsi, 1       ; one fewer element to process, setting ZF at zero
    jnz .loop        ; repeat while the counter is not yet zero
    ret
```

~~~~exercism/note
`cmp rsi, 0` is not necessary in the code above because `sub rsi, 1` already sets the `zero flag (ZF)` when the result is `0`.

Although `cmp` is the main way conditions are tested in assembly, many instructions update the flags.
For example, many integer arithmetic or bitwise instructions update `ZF` when the result is `0`, and `SF` when the result is negative (i.e., the top bit is set).

You can check a [reference][reference] to see which flags are affected by each instruction.

[reference]: https://www.felixcloutier.com/x86/
~~~~

Modern processors recognize this pattern during decoding.
A flag-setting instruction immediately followed by a conditional jump that reads those flags can be decoded together into a **single** micro-op, rather than one each.
This is called **macrofusion**.

The fused pair behaves as one operation: the counter is updated and the branch decision is made together, in a single micro-op.
The control flow of the loop then costs almost nothing on top of the work the loop actually does.

As a rule of thumb, two kinds of pairs usually fuse this way:

- Arithmetic instructions such as `add` or `sub`, immediately followed by a conditional jump.
- A `cmp`, `test` or `and`, immediately followed by a conditional jump.

```x86asm
    ...
    add rdi, 8       ; advance a pointer
    cmp rdi, rsi     ; compare it against the end address
    jb .loop         ; repeat while still below the end
```

Fusion only happens when the conditional jump comes **immediately** after the flag-setting instruction, with nothing in between.

~~~~exercism/note
Macrofusion depends on the CPU and there is some variation on which instructions fuse with which conditional jump.

A useful reference is [The microarchitecture of Intel, AMD, and VIA CPUs, by Agner Fog][agner-uarch].
Section 3.4.2.2 (Optimizing for Macrofusion) of the [Intel optimization reference manual][intel-opt] also lists fusible pairs for Intel CPUs.

[intel-opt]: https://cdrdv2-public.intel.com/821612/248966-Optimization-Reference-Manual-V1-050.pdf
[agner-uarch]: https://www.agner.org/optimize/microarchitecture.pdf
~~~~

## The `loop` Instruction

There are some instructions which can be used to create loop-like behavior.
One of them is [loop][loop].

Its single operand is a label which has the address to the start of the loop.

The `loop` instruction uses the value in `rcx` as a counter, decrementing it by 1 each time.
Once the value in `rcx` reaches zero, the loop ends and execution continues sequentially:

```x86asm
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
| ----------------- | --------- |
| `loope`/`loopz`   | `ZF` == 1 |
| `loopne`/`loopnz` | `ZF` == 0 |

The `ZF` **is not set** by those instructions.
There must be a `cmp`, `test`, or another instruction that changes `ZF` before them:

```x86asm
section .text
fn:
    mov rax, 0
    mov rcx, 10
.example:
    inc rax
    cmp rax, 3
    loopne .example ; this repeats the sequence starting in .example while rcx > 0 and rax != 3
```

~~~~exercism/caution
Despite their convenience, `loop`, `loope`, and `loopne` are usually much slower on modern processors than the equivalent `sub`/`jnz` or `cmp`/`jnz` sequence.

A good reference on the performance of instructions in many different CPUs is the [Agner's tables][agner-tables].

[agner-tables]: https://www.agner.org/optimize/instruction_tables.pdf
~~~~

[control]: https://en.wikipedia.org/wiki/Control_flow#loop-statement
[loop]: https://www.felixcloutier.com/x86/loop:loopcc
