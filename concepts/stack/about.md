# About

The [call stack][stack], or just **stack**, is a special data structure that starts at the highest point in memory and grows downward.

## Push and Pop

The stack supports at least two operations, with instructions of the same name:

| Instruction | Operation performed                                 |
|-------------|-----------------------------------------------------|
| `push`      | adds an element to the stack                        |
| `pop`       | removes and returns the most recently added element |

This means that the stack is a **last in, first out (LIFO)** data structure.

In order to keep track of the current point of the stack, where the most recent element is located, the register `rsp` is used.

So, a [push][push] instruction takes one operand and stores the contents of this operand in the stack.
As the stack grows downward, the value in `rsp` is reduced by the size of the stored value.

Similarly, a [pop][pop] instruction takes one operand and stores the most recent value in the stack (the one pointed by `rsp`) into it.
The value in `rsp` is then increased by the size of the retrieved value.

## Local Variables

It is also possible to manipulate the value of `rsp` directly.
This is often used to create local variables for a function.

```nasm
sub rsp, 24 ; this reserves 24 bytes of space in the stack
add rsp, 24 ; this restores the previous value of rsp, "reducing" the stack by 24 bytes
```

Note that, at the moment space is reserved in stack, the value stored in that space is _undefined_.

~~~~exercism/note
Neither `pop` nor direct manipulation of `rsp` actually remove the contents stored in memory.
The "removal" of the stack is abstracted from the new address in `rsp`.

In some contexts, this may cause security concerns by exposing internal values to external sources.
One way to deal with that is by zeroing-out the contents of any stack space used by the function.
~~~~

## Call and Ret

The main purpose of the stack is to keep track of the return address for called functions.

As it was mentioned in a previous concept, there is a special register called `rip` that points to the next instruction to be executed.
This register is used to control the flow of a program, being modified by instructions such as `jmp` and `call`.

Whenever a `call` instruction is used, the current value in `rip` is implicitly pushed to the stack.
Subsequently, the operand for the instruction is moved into `rip`, so that execution continues in the called function.

A `ret` instruction does the opposite operation.
It pops from the stack into `rip`, so execution returns to the calling function.

So, at point of entry, `rsp` points to the address to be returned.
This is the address `ret` must pop from the stack.

So, any change in the value of `rsp` inside a function, either directly or with `push`, must be reversed before the function returns.

## Callee-Saved and Caller-Saved Registers

Apart from `rsp`, there are other registers that must be preserved across function calls: `rbp`, `rbx`, `r12`, `r13`, `r14` and `r15`.
In general, the calling function expects to be able to use those registers without them being changed by a called function.

This means the _called_ function must save the values in those registers before using them and restore them to their original values before returning.
This is why they are called **callee-saved registers**.

Other general-purpose registers are directly available for use by the called function.

This means that the _caller_ function must save the values in those registers before calling any function, in case they are modified by the called function.
This is why they are called **caller-saved registers**.

_The most common way for saving the contents of a register is by storing it into the stack._

## Prologue and Epilogue

In some cases, the stack might be heavily used, with many modifications before the function returns.
So, keeping track of all those changes to reverse them may be complex.

In those cases, a common strategy is saving the address of `rsp` in another register that remains otherwise unchanged inside the function.
And then, the value of `rsp` might be restored with a simple `mov` instruction at the end, before the function returns.

Although any register may be used for this purpose, it is conventional to use `rbp` as a base pointer.
Since `rbp` is itself a callee-saved register, this is often preceded by a `push rbp`.
This sequence is usually called **prologue**.

At the end, the restoration of `rsp` is made with a `mov rsp, rbp` and then `rbp` is also restored with a `pop` from the stack.
This sequence is usually called **epilogue**.

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

In the [System V ABI][SystemV] calling convention, arguments are usually passed to functions in registers.
However, when there are too many arguments, or they need more than the size of a register, the stack may be used.

In those cases, values are added to the stack in reversed order, so that the first argument is closer to `rsp`.
Since at point of entry, `rsp` points to the return address, which is a 8-byte value in x86-64, the first argument on the stack, if any, can be accessed in `rsp + 8`:

```nasm
mov rdi, 4   ; first argument
mov rsi, 8   ; second argument
mov rdx, 15  ; third argument
mov rcx, 16  ; fourth argument
mov r8, 23   ; fifth argument
mov r9, 42   ; sixth argument
; any remaining integer argument goes on the stack in reversed order
sub rsp, 16
mov qword [rsp], 100      ; seventh argument
mov qword [rsp + 8], 300  ; eigth argument

call many_arguments_fn ; call implicitly pushes `rdi` on the stack
; so, at point of entry, 'many_arguments_fn' finds the first six integer arguments in the usual registers
; the seventh argument is found in rsp + 8
; and the eight argument is found in rsp + 16
```

## Stack Alignment

The System V ABI states that the stack needs to be 16 byte aligned immediately _before_ the call instruction is executed.
As `call` pushes `rdi` into the stack, at point of entry the stack for the called function is **not** 16-byte aligned.

This means that a function that calls another (and, in special, external functions) needs to align the stack before using `call`.

This can be done by subtracting a suitable value from `rsp`.
This value must be 8 more than a multiple of 16: 8, 24, 40, etc.
Since a `push` instruction subtracts from `rsp`, a dummy `push` may be used to the same effect.

[stack]: https://en.wikipedia.org/wiki/Call_stack
[push]: https://www.felixcloutier.com/x86/push
[pop]: https://www.felixcloutier.com/x86/pop
[SystemV]: https://www.uclibc.org/docs/psABI-x86_64.pdf
