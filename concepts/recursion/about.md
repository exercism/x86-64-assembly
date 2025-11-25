# About

A function is [recursive][recursion] when it calls itself.

In many ways a recursive function works as a loop.
In both situations, execution is transferred to a label before the current point of execution.

One key difference between them is that calling a function pushes the address to be returned to the stack.
This means that a recursive function usually demands more stack space than an equivalent loop.

As a consequence, a function which keeps calling itself may eventually exhaust all stack space.
This is called a **stack overflow**.

This is why every recursive function must have at least one base case, which is a situation when the function returns without calling itself.
Any recursive call must eventually reach a base case.

## Tail Call

In some situations, a function does not perform any more work after calling another and before returning.

Consider, for example:

```x86asm
times_three:
    imul rdi, rdi, 3
    mov rax, rdi
    ret

triple_of_square:
    imul rdi, rdi
    call times_three
    ret
```

The function `triple_of_square`:

- multiplies the passed argument (in `rdi`) by itself, getting its square;
- then it calls `times_three`, which returns three multiplied by the argument passed.

As a result, `triple_of_square` returns `3*x²`, where `x` is its argument, passed in `rdi`.

Notice that no work is done in `triple_of_square` after calling `times_three`, the function simply returns.

In a situation like this, instead of using `call`, a function might use `jmp` and transfer execution to the called function:

```x86asm
times_three:
    imul rdi, rdi, 3
    mov rax, rdi
    ret

triple_of_square:
    imul rdi, rdi
    jmp times_three
```

This is called [tail call][tail].

The main advantage of a `tail call` is avoiding the extra cost of `call`, i.e., pushing `rip` to the stack.
This is particularly useful on a recursive function, which tends to call itself multiple times before returning.

In some cases, with a manipulation of the order of the functions, even this `jmp` instruction might be avoided:

```x86asm
triple_of_square:
    imul rdi, rdi
times_three:
    imul rdi, rdi, 3
    mov rax, rdi
    ret
```

Note that execution of `triple_of_square` fallthroughs to `times_three`, continuing sequentially.
It seems as if `times_three` is just a local label inside of `triple_of_square`.

In reality, there's no essential difference between any local label and a function.
x86-64 assembly does not give special treatment to any of them, they are just addresses in a section with executable code, such as the `section .text`.

In this way, a tail recursive function can be thought of being similar to a loop, while a base case would be a condition that ends this loop.

~~~~exercism/note
A `tail call` can only be used if a function does not perform any more work after calling another.
Many recursive functions are not naturally tail recursive.

However, in some situations, a tail-recursive helper may be defined, so that the main function does some work before or after this helper and the "recursion" occurs in the helper function.
~~~~

[recursion]: https://en.wikipedia.org/wiki/Recursion_%28computer_science%29
[tail]: https://en.wikipedia.org/wiki/Tail_call
