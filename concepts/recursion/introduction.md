# Introduction

A function is **recursive** when it calls itself.

One key difference between a function call and a loop is that calling a function pushes the address to be returned to the stack.
This means that a recursive function usually demands more stack space than an equivalent loop.

As a consequence, a function which keeps calling itself may eventually exhaust all stack space.
This is called a **stack overflow**.

This is why every recursive function must have at least one base case, which is a situation when the function returns without calling itself.
Any recursive call must eventually reach a base case.

For example, the factorial function `n! = n * (n - 1) * ... * 1` can be defined recursively with `1` as the base case:

```x86asm
factorial:
    ; the argument `n` is passed on `rdi`
    ; the factorial will be returned on `rax`

    cmp rdi, 1
    jle .base_case     ; base case -> if rdi <= 1, return 1

    push rdi           ; save n
    dec rdi            ; rdi = n - 1
    call factorial     ; recursive call, rax = (n - 1)!
    pop rdi            ; restore n
    imul rax, rdi      ; rax = n * (n - 1)! = n!
    ret
.base_case:
    mov rax, 1
    ret
```

Note that `factorial` must `push rdi` before recursing and `pop rdi` after.
This is because it still needs `n` once the recursive call returns in order to compute `n * (n-1)!`.

Note also that using a callee-saved register would not solve this problem.

Even though a recursive function is a potential caller of itself, it is itself a callee of some other function.
That means the function must also preserve callee-saved registers before using them, and restore their value after they are used.
This is usually done with a `push`/`pop` sequence, as we have seen in a previous concept.

Since each frame of a recursive function, with the exception of the base case, is also a caller that needs to preserve its own local variables, this `push`/`pop` sequence must be repeated for each frame.
Even storing the variables directly into the stack, without using registers, would still cost the same `8` bytes per frame.

This means each recursive call adds `8` bytes to the stack for the return address pushed by `call`, plus `8` bytes for each local variable it needs to save.
The function will keep adding those bytes to the stack each frame until it reaches its base case.
Only then does it begin to unwind in reverse order, each recursive call using as many `pop` as needed and then a `ret`.

For example, if `factorial` was called with argument `10`, it would call itself nine times before reaching the base case of `1`.
At that point, `144` bytes would have been used to store the `n` (`8` bytes) and the return address (`8` bytes) for each previous frame.

## Tail Call

In some situations, a function does not perform any more work after calling another and before returning.

Consider, for example:

```x86asm
times_three:
    imul rax, rdi, 3
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

Note that no work is done in `triple_of_square` after calling `times_three`, the function simply returns.
In a situation like this, instead of using `call`, a function might use `jmp` and transfer execution to the called function:

```x86asm
times_three:
    imul rax, rdi, 3
    ret

triple_of_square:
    imul rdi, rdi
    jmp times_three
```

This is called a **tail call**.

The main advantage of a tail call is avoiding the extra cost of `call`.
A `call` pushes a return address onto the stack, and for control to come back to that point there must be a matching `ret`.

A tail call skips both: there is no return address to push, and no extra `ret` to pair with, just the called function's own `ret`.

## Tail Recursion

A tail call is particularly useful for recursive functions that may call themselves many times before returning.

However, not every recursive call can be directly translated into a tail call.
As a `jmp` transfers control to the called function, the caller can not perform any more work after the tail call.

For example, the earlier `factorial` function is **not** tail recursive.
After the recursive call, it still needs to multiply the result with the current `n`, using `imul rax, rdi`.

In situations like this, it is sometimes possible to use an accumulator that will collect partial computations and be returned at the end.
For example, we can define a `factorial_helper` that does most of the work and then `factorial` sets up an accumulator and transfers control to `factorial_helper`:

```x86asm
factorial_helper:
    ; the argument `n` is passed on `rdi`
    ; `rax` is used as an accumulator and will be returned at the end

    cmp rdi, 1
    jle .base_case

    imul rax, rdi        ; we accumulate the partial result on `rax`
    dec rdi              ; rdi = n - 1
    jmp factorial_helper ; tail call to accumulate (n - 1)!
.base_case:
    ret                  ; returns the factorial already accumulated on `rax`

factorial:
    mov rax, 1           ; initial value for the accumulator
    jmp factorial_helper ; tail call
```

Since no more work is done after the recursive call, we also do not need to save `rdi` anymore.
There is no `call` or `push rdi` and so each recursive iteration adds `0` bytes to the stack: no additional stack space is used.
This version can handle arbitrarily large `n` without overflowing the stack.
It is both more efficient and safer.

In some cases, with a manipulation of the order of the functions, even the `jmp` to the helper might be avoided.
For example, `factorial` and `triple_of_square` can be rewritten in this way:

```x86asm
factorial:
    mov rax, 1
factorial_helper:
    cmp rdi, 1
    jle .base_case

    imul rax, rdi
    dec rdi
    jmp factorial_helper
.base_case:
    ret

triple_of_square:
    imul rdi, rdi
times_three:
    imul rax, rdi, 3
    ret
```

In the snippet above, execution of `factorial` falls through to `factorial_helper`.
The same happens with `triple_of_square` and `times_three`.
In both cases, execution continues sequentially and it seems that the tail function is just a local label inside the "main" function.

In reality, there's no essential difference between any local label and a function.
x86-64 assembly does not give special treatment to any of them, they are just addresses in a section with executable code, such as `section .text`.

In this way, a tail recursive function can be thought of essentially the same as a loop where the recursive call jumps back to the top, and the base case is the condition that ends the loop.
