# About

## RFLAGs

There's a special register called `rflags`.
Its bits act like flags for various conditions.

Some of those are listed below:

| name     | symbol | bit |
|:---------|:------:|:---:|
| carry    | CF     | 0   |
| zero     | ZF     | 6   |
| sign     | SF     | 7   |
| overflow | OF     | 11  |

For a full list, refer to [Intel's Manual][manual].

## Comparison Instructions

The flags in `rflags` are set by many different instructions.

For instance, `ZF` is set by many arithmetic or bitwise operations when the result is zero.

Two of the most common instructions used to test conditions are `cmp` and `test`.
They both take two operands and update the flags, but **do not modify their operands**.

### CMP Instruction

The `cmp` instruction subtracts the second operand from the first and sets flags according to the result.

If A is the first operand and B, the second:

| flag | set when                       |
|:----:|:-------------------------------|
| CF   | A < B (unsigned)               |
| ZF   | A == B                         |
| SF   | A < B (signed)                 |
| OF   | overflow in signed subtraction |

### TEST Instruction

The `test` instruction makes a bitwise AND between both operands and sets flags according to the result.

If A is the first operand and B, the second:

| flag | set when             |
|:----:|:---------------------|
| CF   | always cleared       |
| ZF   | A AND B == 0         |
| SF   | A AND B < 0 (signed) |
| OF   | always cleared       |

## Branching

As a default, code in x86-64 executes sequentially from top to bottom.

But there are many situations where it's necessary to modify this behavior.
For instance, to execute a different set of instructions in response to a condition.

In higher-level languages, this is usually done with abstractions such as `if...else` conditionals.
However, those do not exist in x86-64.

Instead, x86-64 provides instructions that effectively transfer execution to another location of the code.
This is called `branching`.

~~~~exercism/note

We've already seen two such instructions: `call` and `ret`.

When a function is called, execution is transferred from the caller to the called function.
And, on return, execution is transferred back to the caller.

If no `ret` is found, execution fallthroughs from one function to the next.
This can sometimes be used to optimize code flow.

~~~~

### Unconditional Jump

The instruction [jmp][jump] unconditionally transfers execution of the program to another point of the code.
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

The family of instructions [jcc][jcc] transfers execution of the program to another point only if a specific condition is met.
Otherwise, execution continues sequentially.

Each condition maps to one or more flags in `rflags`.
Some `jcc` variants test that a flag is set, others test that it is cleared.

The `cc` in `jcc` is not literal, but refers to the specific suffix associated with the flag tested.

There are many suffixes and many of them test the same condition as another.
This is because many of them are chosen in order to refer to their meaning in a `cmp` instruction.

For example, `jz` (suffix `z`, for `ZF`) and `je` (suffix `e`, for equal) both jump when `ZF` is set.
This is because, with `cmp`, `ZF` is set when the subtraction yields zero, which corresponds to the two operands being equal.

The following table shows some of the possible suffixes and their meaning.
Consider that A is the first operand, and B the second, in a `cmp` instruction.

| suffix | meaning          |
|:------:|:-----------------|
| e      | A == B           |
| l      | A < B (signed)   |
| b      | A < B (unsigned) |
| g      | A > B (signed)   |
| a      | A > B (unsigned) |

It's possible to add `e` after `l`, `b`, `g` or `a` to include the equality in the condition.

For instance, `jge` jumps when A >= B (A and B interpreted as signed integers).

There are also suffixes which refer directly to the flag being tested:

| suffix | flag |
|:------:|:----:|
| z      | ZF   |
| c      | CF   |
| s      | SF   |
| o      | OF   |

For all suffixes, there are variants which check the opposite behavior.
They have the same syntax, but with a `n` before the suffix.

For instance, `jnz` jumps when `ZF` is **not** set.
Similarly, `jnae` jumps when A is **not** >= B (A and B interpreted as unsigned integers).

## Local Labels

Labels are visible in the entire source file, they are not local to a function.
So it is impossible to reuse a label name.

In order to mimic the behavior of a local label, NASM has a special notation for a label declared with a period (`.`) before it.
This notation defines a label which implicitly includes the name of the previous non-dotted label:

```nasm
section .text
fn1:
    ...
.example: ; this is fn1.example
    ...
    ret

fn2:
    ...
.example: ; this is fn2.example
    ...
    ret
```

It is still possible to jump to this label from anywhere in the code by using the full label name, for instance, `jmp fn1.example`.

However, a jump that uses the part of the label starting at the dot will be made to the label _inside_ the upper function.
So, `.example` behaves as if it was local to the function, either `fn1` or `fn2`.

Notice that a non-dotted label inside a function in practice defines another function:

```nasm
section .text
fn1:
    ...
.example: ; this is 'fn1.example'
    ...
non_dotted:
    ...
.example: ; this is 'non_dotted.example'
    ...
    ret
```

[manual]: https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-1-manual.pdf#page=78
[jmp]: https://www.felixcloutier.com/x86/jmp
[jcc]: https://www.felixcloutier.com/x86/jcc
