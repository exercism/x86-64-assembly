# Introduction

## Macros

Hand-written assembly is full of repetition.
The same short run of instructions appears again and again, with little variation, and there are few abstractions to reduce boilerplate.
Not only that, coding in assembly requires managing values with no obvious semantics.
There are no named parameters and most details of the underlying machinery must be handled manually by the programmer.

NASM, the assembler used by the track, offers some tools which can help the programmer with both issues.
These tools run at _assemble time_, before any instruction reaches the processor.
They guide the assembler in how to rewrite the source text before it is even translated into machine code.

The most important of these tools are **macros**, which can be thought of as a recipe for the assembler.
They are expanded at the location where used, as if the code had been written there by hand.

Macros can take a number of literal tokens as parameters, making them reusable in different contexts.
However, they are not functions: there is no `call`, no `ret`, no transfer of control to another point in the code.

### Single-Line Macros

The simplest definition gives a name to a value or a short expression with `%define`:

```x86asm
%define WIDTH 8
%define BUFFER_SIZE (WIDTH * 16)
```

Every later occurrence of `WIDTH` is replaced by `8` before assembly.
The replacement is textual, so the name is substituted anywhere it appears, whether in an operand or inside another definition.

~~~~exercism/note
For numeric _constants_, prefer `equ` instead of `%define`.

A single-line macro declared with `%define` only expands when used, and may be reassigned or undefined.
An `equ` constant, on the other hand, is evaluated at the point of definition and is never modified.
~~~~

A `%define` can also take _named_ parameters, behaving like a small inline function:

```x86asm
%define double(x) ((x) + (x))

    mov eax, double(WIDTH)   ; assembled as mov eax, ((8) + (8))
```

~~~~exercism/caution
Wrap both the whole body and each parameter in parentheses.
With `%define square(x) x*x`, the call `square(1+1)` expands to `1+1*1+1`, which is `3`.
Written as `%define square(x) ((x)*(x))`, the same call expands to `((1+1)*(1+1))`, which is `4`.
~~~~

Names defined with `%define` are case sensitive.
The variant `%idefine` makes the name case insensitive, should that be wanted.

Single-line macros are useful to give meaning to various parts of the code.
If used with care, this improves readability and reduces the chance of typos.
For example, a register that has a dedicated purpose inside a function may be defined by its purpose:

```x86asm
%define COUNTER rcx
    ...
.loop:
    ...
    dec COUNTER
    jnz .loop
    ...
```

### Multi-Line Macros

A whole sequence of code, with any number of lines, is captured with `%macro`, closed by `%endmacro`.
A number after the name indicates how many arguments the macro takes, which can be zero.
When arguments are passed, they are separated by a comma (`,`):

```x86asm
%macro example_macro 0
...
%endmacro
```

Arguments in multi-line macros are not named.
They are referred to as `%1`, `%2`, and so on, in the order they are passed:

```x86asm
; Multiplies two values, returning the result in the first argument
%macro mult_two 2        ; %1 = accumulator, %2 = value
    imul %1, %2
%endmacro

    mult_two eax, ecx    ; multiplies eax and ecx and returns the result into eax
    mult_two r8, r9      ; multiplies r8 and r9 and returns the result into r8
```

Note that the arguments must be valid syntax for the operations performed in the body of the macro.
Here `mult_two eax, ecx` and `mult_two r8, r9` both assemble, but `mult_two eax, cl` would not, since `imul eax, cl` is not defined.

#### Labels Inside a Macro

A macro that defines an ordinary label breaks the moment it is used twice, because the label would then also be defined twice.
To use labels inside a macro that may be called more than once, it is necessary to prefix such a label with `%%`.
This instructs the assembler to give this label a different, unique name on each expansion:

```x86asm
; clobbers rcx
%macro clear_n 2         ; %1 = base address, %2 = count of dwords to clear
    xor ecx, ecx
%%loop:
    mov dword [%1 + rcx*4], 0
    inc ecx
    cmp ecx, %2          ; %2 is compared with ecx: it is an immediate or a 32-bit operand
    jb %%loop
%endmacro

    clear_n rdi, 4       ; gets its own %%loop
    clear_n rsi, 8       ; a different %%loop, no clash
```

### Repeating at Assemble Time

It is possible to repeat a one-line block of code using `times`.
This is particularly useful when declaring repeated values in memory:

```x86asm
section .data
negative_block: times 16 db -1
; this assembles to 16 db -1 in sequence, i.e., an array of 16 bytes, all equal to -1
```

For multi-line code repetition, we may use `%rep` instead:

```x86asm
%rep 2          ; number of repetitions: 2
    add rcx, 32
    mov dword [rsi + rcx], 0
%endrep
```

Note that the number of repetitions is specified just after `%rep` and there is an `%endrep` to close the repeated block.

It is common to use an assemble-time counter inside a `%rep` block, much as a run-time loop uses a counter.
While an assemble-time integer constant may be declared with `equ`, for assemble-time integer _variables_ we use `%assign` instead.
Unlike `%define`, `%assign` is evaluated immediately to a number and may be reassigned:

```x86asm
    xor eax, eax
%assign i 0
%rep 4
    add eax, i           ; add 0, then 1, then 2, then 3
%assign i i + 1
%endrep
```

After the preprocessor runs, the loop is gone and four `add` instructions remain, with the immediates `0`, `1`, `2`, and `3` baked in.
This is loop unrolling done by the assembler: no counter register and no branch, just straight-line code.

### Conditional Assembly

There are various conditionals available to the preprocessor.
They select between a number of different paths, expanding their body in-place, but only when their condition holds true.

`%if` ... `%elif` ... `%else` ... `%endif` select a branch from a numeric test:

```x86asm
%if WIDTH > 4
    mov eax, 2
%elif WIDTH > 2
    mov eax, 1
%else
    mov eax, 0
%endif
```

### Splitting Into Files

Macros are often kept in a file of their own and pulled into each source that needs them with `%include`:

```x86asm
%include "patterns.mac"
```

The named file is inserted verbatim at that point, before assembly, exactly as if its contents had been typed in place.
This keeps the definitions in one location and lets several source files share them.

If the macro file may be assembled as a standalone, it should have an `.asm` file extension.
Note that macros have no linkage.
Even if the macro file is assembled, its macros are only visible to another file that `%include`s it.

Otherwise, an `%include`-only may have any file extension.
The use of either `.asm` or `.mac` is a common convention.
