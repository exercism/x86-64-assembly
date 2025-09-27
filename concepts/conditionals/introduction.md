# Introduction

## RFLAGs

There's a special register called `rflags`.
Its bits act like flags for various conditions.

Some of those are listed below:

```
+--------------+----------+-------+
|     name     |  symbol  |  bit  |
+--------------+----------+-------+
|   carry      |    CF    |   0   |
+--------------+----------+-------+
|   zero       |    ZF    |   6   |
+--------------+----------+-------+
|   sign       |    SF    |   7   |
+--------------+----------+-------+
|   overflow   |    OF    |   11  |
+--------------+----------+-------+
```

## Comparison Instructions

The flags in `rflags` are set by many different instructions.

Two of the most common instructions used to test conditions are `cmp` and `test`.
They both take two operands and update the flags, but **do not modify their operands**.

### CMP Instruction

The `cmp` instruction subtracts the second operand from the first and sets flags according to the result.

If the first operand is less than the second, when both are interpreted as unsigned numbers, `CF` is set.
Otherwise, it's cleared.

If the result is 0, `ZF` is set.
Otherwise, it's cleared.

If the result is less than 0 in a signed subtraction, ie, a negative number, `SF` is set.
Otherwise, it's cleared.

If there's an overflow in a signed division, `OF` is set.
Otherwise, it's cleared.

### TEST Instruction

The `test` instruction makes a logical AND between both operands and sets flags according to the result.
Both `OF` and `CF` are always cleared.

If the result, interpreted as a signed integer, is less than 0, `SF` is set.
Otherwise, it's cleared.

If the result is 0, `ZF` is set.
Otherwise, it's cleared.

## Branching

As a default, code in x86-64 executes sequentially from top to bottom.

But there are many situations where it's necessary to modify this behavior.
For instance, to execute a different set of instructions in response to a condition.

In higher-level languages, this is usually done with abstractions such as `if...else` conditionals.
However, those do not exist in x86-64.

Instead, x86-64 provides instructions that effectively transfer execution to another location of the code.
This is called `branching`.

### Unconditional Jump

The instruction `jmp` unconditionally transfers execution of the program to another point of the code.
Its single operand is a label which has the address to the point where execution will continue.

Consider, for instance, the following function:

```nasm
fn:
    mov rax, 5
    jmp end

    add rax, 10
end:
    ret
```

When `fn` is called, execution starts at `mov rax, 5`.
This sets the value in `rax` to be 5 at that point.

The next instruction is `jmp end`, which transfers execution to the label `end`.

After `end`, the next instruction is `ret`, which transfers execution back to the caller function.

Notice that, since `add rax, 10` is located after `jmp end` and before `end`, it is never executed.
The value of `rax` when `fn` returns is 5.

### Conditional Jump

The family of instructions `jcc` transfers execution of the program to another point only if a specific condition is met.
Otherwise, execution continues sequentially.

Each condition maps to one or more flags in `rflags`.
Some `jcc` variants test that a flag is set, others test that it is clear.

The `cc` in `jcc` is not literal, but refers to the specific suffix associated with the flag tested.

There are many suffixes and many of them test the same condition as another.
This is because many of them are chosen in order to refer to their meaning in a `cmp` instruction.

For example, `jz` (suffix `z`, for `ZF`) and `je` (suffix `e`, for equal) both jump when `ZF` i set.
This is because, with `cmp`, `ZF` is set when the subtraction yields zero, which corresponds to the two operands being equal.

The following table shows some of the possible suffixes and their meaning.
Consider that A is the first operand, and B the second, in a `cmp` instruction.

```
+------------+----------------------+
|   suffix   |       meaning        |
+------------+----------------------+
|     e      |       A == B         |
+------------+----------------------+
|     l      |    A < B (signed)    |
+------------+----------------------+
|     b      |    A < B (unsigned)  |
+------------+----------------------+
|     g      |    A > B (signed)    |
+------------+----------------------+
|     a      |    A > B (unsigned)  |
+------------+----------------------+
```

It's possible to add `e` after `l`, `b`, `g` or `a` to include the equality in the condition.

For instance, `jge` jumps when A >= B, when interpreted as signed integers.

There are also suffixes which refer directly to the flag being tested:

```
+------------+----------------------+
|   suffix   |        flag          |
+------------+----------------------+
|     z      |         ZF           |
+------------+----------------------+
|     c      |         CF           |
+------------+----------------------+
|     s      |         SF           |
+------------+----------------------+
|     o      |         OF           |
+------------+----------------------+
```

For all suffixes, there are variants which check the opposite behavior.
They have the same syntax, but with a `n` before the suffix.

For instance, `jnz` jumps when `ZF` is **not** set.
Similarly, `jnae` jumps when A >= B is false, when A and B are interpreted as unsigned integers.
