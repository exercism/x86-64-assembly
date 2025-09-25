# About

Memory is usually allocated for the program by the OS in a general layout:

```
+-----------------+
| high |  stack   |
|      |   ...    |
|      |  heap    |
|      |  .bss    |
|      |  .data   |
|      |  .text   |
| low  | reserved |
+------+----------+
```

The [stack][stack] is a special data structure that starts at the highest point in memory and grows downward.

## Push and Pop

A stack supports two operations: **push** and **pop**:

- a push operation adds an element to the stack; and
- a pop operation removes and returns the most recently added element.

This means that the `stack` is a **last in, first out (LIFO)** data structure.

In order to keep track of the current point of the `stack`, where the most recent element is located, the register `rsp` is used.

In x86-64, the instructions [push][push] and [pop][pop] implement their homonimous operations.

So, a `push` instruction takes one operand and stores the contents of this operand in the stack.
As the stack grows downward, the value in `rsp` is reduced by the size of the stored value.

Similarly, a `pop` instruction takes one operand and stores the most recent value in the stack (the one pointed by `rsp`) into it.
The value in `rsp` is, therefore, increased by the size of the retrieved value.

## Local Variables

It's also possible to manipulate the value of `rsp` directly:

```nasm
sub rsp, 24 ; this reserves 24 bytes of space in the stack
add rsp, 24 ; this restores the previous value of rsp, "reducing" the stack by 24 bytes
```

This is often used to create local variables for a function.

Notice that, at the moment space is reserved in stack, the value stored in that space is undefined.

~~~~exercism/note

Neither `pop` nor direct manipulation of `rsp` actually remove the contents stored in memory.
The "removal" of the stack is abstracted from the new address in `rsp`.

In some contexts, this may cause security concerns by exposing internal values to external sources.
One way to deal with that is zeroing-out the contents of stack space used by the function.

~~~~

## Callee-Saved and Caller-Saved Registers

In a previous lecture, it was informed that some registers must be preserved across function calls: `rbp`, `rsp`, `rbx`, `r12`, `r13`, `r14` and `r15`.
In general, the calling function expects to be able to use those registers without modification by any called function.

So, the called function must save the values in those registers before using them, so as to restore the original values before the end of the function.
This is why they are called **callee-saved registers**.

The other registers are directly available for use by the called function.

This means that the caller function must save the values in those registers before calling any function, in case they are modified by the called function.
This is why they are called **caller-saved registers**.

The most common way for saving the contents of a register is by storing it into the stack.

## Call and Ret

The main function of the stack is keeping track of the return address for called functions.

Whenever a `call` instruction is used, the current value in `rip` is implicitly pushed to the stack.
Subsequently, the operand for the instruction is moved into `rip`, so that execution continues in the called function.

A `ret` function does the opposite operation.
It pops from the stack into `rip`, so execution returns to the calling function.

So, at point of entry, `rsp` points to the address to be returned.
This is the address `ret` must pop from the stack.

This is why `rsp` is a callee-saved register.
Any manipulation of `rsp` inside a function, either directly or with `push`, must be reversed before the function returns.

## Prologue and Epilogue

In some functions, the stack might be used heavily, with many modifications before returning.
So, keeping track of all those changes to reverse them may be complex.

In those cases, it's conventional to use `rbp` as a base pointer to store the contents of `rsp`.
Since `rbp` is itself a callee-saved register, this is often preceded by a `push rbp`.
This sequence is usually called `prologue`.

At the end, the value in `rsp` is restored by a `mov rsp, rbp` and the value in `rbp` is restored with a `pop`.
This sequence is usually called `epilogue`.

```nasm
section .text
fn:
    ; prologue
    push rbp
    mov rbp, rsp
    ...
    ; epilogue
    mov rsp, rbp
    pop rbp
    ret
```

~~~~exercism/note

The main purpose of the prologue/epilogue sequences is to help the programmer in keeping track of changes to `rsp`.
This is, of course, much easier for a compiler to do.

This is why many compilers emit an optimization to omit the frame pointer and remove prologues/epilogues entirely from code.

~~~~

## Passing and Returning Arguments with the Stack

In the [System V ABI][SystemV] calling convention, arguments are usually passed to functions into registers.
However, when there are too many arguments, or they need more than the size of a register, the stack may be used.

In those cases, values are added to the stack in reverse order, so that the first argument is closer to `rsp`.

Since at point of entry, `rsp` points to the return address, which is a 8-byte value in x86-64, the first argument can be accessed in `rsp + 8`.

As with argument passing, values are usually returned from functions into registers.
In case of an integer value, the first 8 bytes are returned in `rax` and the next 8 bytes are returned in `rdx`.

However, when the size of the returned value can not be accomodated in the conventional registers, the caller function must reserve space for the returned value.
The address of this space is implicitly passed as a hidden first integer argument (in `rdi`).

In this case, the return of the function, in `rax`, is this address which was originally passed in `rdi`.

This space does not need to be reserved in the stack, although this is common.

## Stack Alignment

The System V ABI states that the stack needs to be 16 byte aligned immediately before the call instruction is executed.
As the call instruction pushes `rdi` into the stack, at point of entry the stack is *not* 16-byte aligned.

This means that a function that calls another (and, in special, external functions) needs to align the stack before using `call`.

This can be done by subtracting a suitable value from `rsp`.
This value must be 8 more than a multiple of 16: 8, 24, 40, etc.

Since a `push` instruction has the effect of subtracting 8 bytes from `rsp`, a dummy `push` may be used for the same effect.

[stack]: https://en.wikipedia.org/wiki/Call_stack
[push]: https://www.felixcloutier.com/x86/push
[pop]: https://www.felixcloutier.com/x86/pop
[SystemV]: https://www.uclibc.org/docs/psABI-x86_64.pdf
