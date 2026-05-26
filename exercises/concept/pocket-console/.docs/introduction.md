# Introduction

## Branchless Code

The conditionals concept introduces `jcc`, the family of instructions for branching based on a condition.
A `jcc` transfers execution to another point in the program only if its condition is met.

However, modern CPUs are fast and capable of executing many instructions in parallel.
It would be too costly to stall all work while the CPU waits for a runtime check of a condition.

This is why, internally, the CPU does not wait.
It uses a **branch-predictor** to guess the outcome of a condition and starts _speculatively_ executing the predicted path.

If the prediction is correct, execution proceeds as if there was no branch.
However, if the prediction is wrong, the CPU must _discard the work done_ on the predicted path and restart on the correct one.

This is called a **branch misprediction** and it is expensive, incurring a delay.

When a branch is hard to predict, those mispredictions add up.
In those cases, it is sometimes preferable to avoid the branch entirely, so the same instructions execute regardless of the condition.
Code that selects between values without a `jcc` is called **branchless**.

There are several ways to structure code so that it branches less often, or so that the branches it does have are more predictable.
In particular, x86-64 provides two instruction families that are commonly used for writing branchless code.

### Conditional Moves

The family of instructions `cmovcc` copies the source operand into the destination only if a specific condition is met.
Otherwise, the destination is left unchanged.

The `cc` suffix follows the same naming as in `jcc`, with the same meaning:

| instruction | move if                              |
|-------------|--------------------------------------|
| `cmove`     | A == B after `cmp A, B`              |
| `cmovne`    | A != B after `cmp A, B`              |
| `cmovl`     | A < B (signed) after `cmp A, B`      |
| `cmovb`     | A < B (unsigned) after `cmp A, B`    |
| `cmovg`     | A > B (signed) after `cmp A, B`      |
| `cmova`     | A > B (unsigned) after `cmp A, B`    |

The rules are similar to `jcc`:

1. `l` and `g` are used for signed comparisons, and `b` and `a`, for unsigned.
2. Adding `e` to a suffix includes equality.
3. Adding `n` negates the condition.
4. There are also variants that refer to the flag being set.
   For example, `cmovz` and `cmovc`.

Consider the absolute value of a signed integer in `rdi`, returned in `rax`.
Written with `jcc`, the function selects one of two paths:

```x86asm
abs_branch:
    mov rax, rdi
    cmp rax, 0
    jge .done
    neg rax
.done:
    ret
```

Written with `cmovcc`, both candidate values are computed unconditionally and the conditional move picks one:

```x86asm
abs_branchless:
    mov rax, rdi
    neg rax            ; rax = -rdi
    cmp rdi, 0
    cmovge rax, rdi    ; the value in `rdi` is moved to `rax` if rdi >= 0
                       ; otherwise, it stays the same, i.e., -rdi
    ; now rax = abs(rdi)
    ret
```

The branchless version always executes the same instructions.
There is no `jcc` for the predictor to guess.

The destination of a `cmovcc` must be a register.
The source may be a register or a memory location, but not an immediate.

~~~~exercism/note
In the code above, the `neg` instruction sets several flags according to the result, including the sign flag (SF).
This means the `cmp rdi, 0` can be dropped entirely:

```x86asm
abs_branchless:
    mov rax, rdi
    neg rax            ; rax = -rdi. `neg` sets SF = 1 if the result is negative
    cmovs rax, rdi     ; if SF == 1 (i.e., rax < 0), replace rax with rdi
                       ; otherwise rax stays = -rdi, which is non-negative
    ; now rax = abs(rdi)
    ret
```

For positive `rdi`, `neg` produces a negative result and SF == 1, so `cmovs` restores `rdi`.
For zero or negative `rdi`, `neg` produces a non-negative result and SF == 0, so `rax` keeps the negated value (which is the correct absolute value).

Although `cmp` is the main way to compare values in assembly code, many instructions also set flags according to their result.
The full list of flags an instruction affects is usually listed in its [reference][reference].
For `neg` specifically, those are SF, ZF, CF, OF, and PF.

[reference]: https://www.felixcloutier.com/x86/
~~~~

### Conditional Set

The family of instructions `setcc` sets the destination operand to `1` if a specific condition is met, and to `0` otherwise.
The destination is always an _8-bit operand_.

The `cc` suffix follows the same naming as in `jcc` and `cmovcc`.
For example, `setz` sets the destination to `1` if `ZF == 1` and to `0` otherwise.

Since the destination is 8-bit, it is common to follow `setcc` with a `movzx` when a wider value is needed:

```x86asm
cmp rdi, rsi
setg al             ; al = 1 if rdi > rsi (signed), 0 otherwise
movzx eax, al       ; eax (and rax) = 1 or 0, with the upper bits cleared
```

This is a common idiom for turning a comparison result into an integer `0` or `1`.
