# Introduction

## Loops

A **loop** is a sequence of instructions that is potentially executed more than once, until an ending condition is met.

In x86-64 a loop is usually created with a jump to a previous label:

```x86asm
example_loop:
    ...
    jmp example_loop
```

Note that an unconditional jump to a previous label will always transfer execution to this label.
This means the loop will keep repeating forever, unless there is another jump to outside the repeated sequence.

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

### Counting Loops

A counting loop almost always ends the same way: an instruction that updates a counter or compares two values, immediately followed by a conditional jump that decides whether to go around again.

```x86asm
sum_array:
    ; rdi is the memory address of an array
    ; rsi is the number of elements in the array

    mov eax, 0           ; running total
.loop:
    add rax, qword [rdi] ; add the current element
    add rdi, 8           ; advance to the next element
    sub rsi, 1           ; one fewer element to process, setting ZF at zero
    jnz .loop            ; repeat while the counter is not yet zero
    ret
```

~~~~exercism/note
`cmp rsi, 0` is not necessary in the code above because `sub rsi, 1` already sets the `zero flag (ZF)` when the result is `0`.

Although `cmp` is the main way conditions are tested in assembly, many instructions update the flags.
For example, many integer arithmetic or bitwise instructions update `ZF` when the result is `0`, and `SF` when the result is negative (i.e., the top bit is set).

You can check a [reference][reference] to see which flags are affected by each instruction.

[reference]: https://www.felixcloutier.com/x86/
~~~~

Note that in the example above, `rsi` is presumed to be greater than `0`.
If it was `0`, then `sub rsi, 1` would reduce `rsi` to `-1`, which is a very large unsigned number.
It would take `18,446,744,073,709,551,615` more iterations before the loop finally ended.
Also, because the length of the array is `0`, any memory access would be out-of-bounds.

If there are no guarantees about the length of an array, there are two common approaches.

The first is moving the ending condition to the beginning of the loop, and then having an unconditional jump at the end:

```x86asm
sum_array:
    mov eax, 0
.loop:
    cmp rsi, 0
    je .done
    add rax, qword [rdi]
    add rdi, 8
    sub rsi, 1
    jmp .loop
.done:
    ret
```

The second is testing once for a zero-length array before the beginning of the loop:

```x86asm
sum_array:
    mov eax, 0

    cmp rsi, 0
    je .done
.loop:
    add rax, qword [rdi]
    add rdi, 8
    sub rsi, 1
    jnz .loop
.done:
    ret
```

This second approach is usually more efficient than the first, because there are fewer branches in the loop body.
You will learn more about this in a future concept.

~~~~exercism/advanced
In some situations, modern CPUs are able to merge two different instructions in a single operation.
This optimization is called **macrofusion**.

Many arithmetic instructions such as `sub` and `add`, as well as `cmp` and `test`, commonly fuse with a conditional jump that follows just after it.
This means that an instruction such as `cmp rax, rdx` immediately followed by a conditional jump can usually be treated by the CPU as a single operation.

Macrofusion depends on the CPU and there is some variation on which instructions fuse with which conditional jump.

A useful reference is [The microarchitecture of Intel, AMD, and VIA CPUs, by Agner Fog][agner-uarch].
Section 3.4.2.2 (Optimizing for Macrofusion) of the [Intel optimization reference manual][intel-opt] also lists fusible pairs for Intel CPUs.

[agner-uarch]: https://www.agner.org/optimize/microarchitecture.pdf
[intel-opt]: https://cdrdv2-public.intel.com/821612/248966-Optimization-Reference-Manual-V1-050.pdf
~~~~
