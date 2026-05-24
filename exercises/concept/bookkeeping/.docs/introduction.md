# Introduction

## Thunks

In a previous concept, it was mentioned that both local labels and functions are just addresses in a section with executable code, such as `section .text`.

In fact, functions can be manipulated in the same way as any memory address, i.e., they can be loaded into registers, passed around and stored in memory.
It is also possible to use `call` or `jmp` to transfer execution to a function stored in a register or memory:

```x86asm
section .text
sum_op:
    lea rax, [rdi + rsi] ; loads the sum rdi + rsi into rax
    ret

apply_sum:
    lea rax, [rel sum_op]
    jmp rax   ; tail call
```

A function address that is passed around as a value is called a **thunk**.
Thunks are a building block of **higher-order programming** in assembly: code that operates on other code.

### Code as data

Function addresses can also be stored in memory and retrieved later:

```x86asm
section .bss
    cached_fn resq 1

section .text
save_op:
    mov qword [rel cached_fn], rdi
    ret

apply_op:
    ; arguments are already set up according to the ABI
    jmp qword [rel cached_fn] ; tail call
```

`save_op` writes the function address it receives into `cached_fn`.
The value persists after `save_op` returns, so any later call to `apply_op` tail-jumps to whatever address was last stored.
This makes it possible to change which function `apply_op` invokes at runtime.

### Dispatch Tables

Storing function addresses in an array makes it possible to select different functions according to some index, possibly dependent on a runtime condition.
This is called a **dispatch table**:

```x86asm
section .data
    dispatch_table dq add_op, sub_op, mul_op

section .text
dispatch:
    ; this function takes two arguments in rdi and rsi, and an index in rdx
    ; it then applies the function corresponding to the index in rdx to the arguments
    lea rax, [rel dispatch_table]
    jmp qword [rax + 8*rdx]   ; tail-call the function address for the index
```

### Stateful Thunks

A thunk that reads or updates some persistent memory between calls may behave differently depending on what came before.
Its result may depend on more than its arguments alone.

For example, a _counter_ that returns the number of times it has been called:

```x86asm
section .data
    count dq 0

section .text
tick:
    mov rax, [rel count]
    inc qword [rel count]
    ret
```

Each call to `tick` returns the current value of `count` and advances it.
The information about how many calls have been made persists in memory rather than being recomputed each time.

Another example would be a _delayed computation_:

```x86asm
section .bss
    captured_fn resq 1
    argument resq 1

section .text
delay:
    mov qword [rel captured_fn], rdi ; saves the function
    mov qword [rel argument], rsi    ; saves the argument
    lea rax, [rel invoke]            ; returns the `invoke` function
    ret

invoke:
    mov rdi, qword [rel argument]    ; loads the saved argument into `rdi`
    jmp qword [rel captured_fn]      ; tail-calls the saved function
```

`delay` takes a function and a value, stores them, and returns `invoke`.
When `invoke` is called, it runs the captured function with the saved argument.

Many of the patterns common in higher-level languages, such as callbacks, virtual methods, generators, currying, function composition, and many others, build on thunks paired with persistent state.
