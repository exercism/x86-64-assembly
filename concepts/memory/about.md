# About

Memory is usually mapped for a program by the Operating System (OS) in a general layout:

| address | memory region          |
|:-------:|:-----------------------|
| high    | stack                  |
|         | ...                    |
|         | heap                   |
|         | read-and-write segment |
|         | code/read-only segment |
| low     | reserved               |

Memory in segments is organized in sections, with different permissions.

The functions we have defined until now were all in **section .text**.
This section holds read-only executable data.
Other sections are used to declare data variables, that may be read-only or read-and-write, but are not executable.

## Section .data

The initialized data is declared in the **[section .data][data]**.

In NASM (The Netwide Assembler - the assembler used by this track), an initialized variable has a name, a directive that indicates the data size, and a list of values separated by comma.
Each of these is separated with a space from the other and the label might optionally be followed by a `:`.

The main directives and their related data sizes are:

| directive | size    |
|:---------:|:--------|
| db        | 1 byte  |
| dw        | 2 bytes |
| dd        | 4 bytes |
| dq        | 8 bytes |

For instance, this declares a byte variable named `space` with the value `10`:

```nasm
section .data
    space db 10
```

Variables declared in `section .data` are mutable, i.e., they are read-and-write.
They also have _static_ storage duration, which means they exist for the entire program runtime.

## Section .rodata

The **section .rodata** is similar to `section .data`.
Both sections contain initialized data, which is declared in the same way and have the same storage duration.

The main difference between them is that data in `section .rodata` is immutable, i.e., read-only.

~~~~exercism/note
Constants defined with `equ` are different than those defined in `section .rodata`.

A constant defined with `equ` does not occupy space in memory and is directly substituted for its value by the assembler.
It is in fact a placeholder for that value.

On the other hand, constants defined in `section .rodata` are actually stored in memory, having an address.
~~~~

## Accessing data

### Labels and Indirection

Declared data must have a name associated with it.
This name is called a **label**.

A label is a symbol that encodes the specific address of data in memory.
**Addresses in x86-64 are 64-bit values**.

In NASM, trying to access data directly with its label does not yield the memory allocated, but its address:

```nasm
section .data
    example dq 27 ; this declares a 8-byte variable initialized with 27

section .text
fn:
    mov rax, example ; this stores the address of the declared variable in rax, not its contents
    ...
```

In order to access the contents of a memory address, it is necessary to _dereference_ it.
This is called **indirection**.

In NASM, this is done with `[]`:

```nasm
section .data
    example dq -27 ; this declares a 8-byte variable initialized with -27

section .text
fn:
    mov rax, [example] ; this dereferences example and access the value stored in memory (-27)
    ...
```

However, there are some situations when there might be an ambiguity regarding the size of the memory dereferenced.
In those cases, a prefix specifying this size must be used.

These are the most important prefixes and their sizes in a typical x86-64 program:

| prefix | size    |
|:-------|:--------|
| byte   | 1 byte  |
| word   | 2 bytes |
| dword  | 4 bytes |
| qword  | 8 bytes |

The last example can be rewritten with the size prefix:

```nasm
section .data
    example dq 27 ; this declares a 8-byte variable initialized with 27

section .text
fn:
    mov rax, qword [example] ; this dereferences example and access the value stored in memory (27)
    ...
```

It is good practice to always use a prefix when dereferencing memory.

### Writing to memory

Writing to memory is done in the same way, by dereferencing an address:

```nasm
section .data
    example1 db 10            ; example1 is a 1-byte memory location initialized with value 10
    example2 dq -456          ; example2 is a 8-byte memory location initialized with value -456
    example3 dd 54            ; example3 is a 4-byte memory location initialized with value 54

section .text
fn:
    mov byte [example1], 20   ; example1 now has value 20
    mov qword [example2], rdx ; example2 now has value equal to the contents in rdx
    mov dword [example3], eax ; example3 now has value equal to the contents in eax
```

Note that you can use memory operands in most instructions without first loading the contents in a register.
However, it is not usually possible to use them in both source and destination operand, only one of the two:

```nasm
section .data
    example4 dw 4
    example5 dq -8
    example6 dd 15

section .text
fn:
    add word [example4], 5     ; example4 is now a 2-byte memory location with the value 4 + 5 = 9
    imul rax, qword [example5] ; rax = rax * (-8)
    ; this is not possible -> sub dword [example6], dword [example6]
```

### The LEA instruction

Although a `mov` can be used to store the address of a variable in a register, there is an instruction with this specific purpose: **[lea][lea]**.

This instruction uses a memory-form operand, but it does _not_ read memory.
Instead, it computes the effective address expression and writes the result in the destination operand:

```nasm
lea rax, [example] ; this stores the address of 'example' in rax
```

It is more idiomatic to use `lea` to compute and store memory addresses in registers.

### Relative Addressing

When accessing memory locations, the default behavior in NASM is to generate **absolute addresses**.
This means that the assembler usually produces a fixed memory address.

However, this can sometimes introduce security concerns, by making addresses predictable to an attacker.

One possible mitigation for this involves randomizing locations of memory regions, so that an attacker can't reliably predict addresses.
In order to do that, executables must be built as **PIE (Position Independent Executable)**.

However, in a `PIE`, the final address of a variable is not known at link time.
So, code instead computes addresses as an offset from the value in a special register called `rip`, which points to the next instruction to be executed.

This is usually called **RIP-relative addressing**.

In NASM you can request RIP-relative access with the **[rel operator][rel]**:

```nasm
mov rax, qword [rel variable]
```

Relative addressing can also be made the default for a source file with `default rel` at the top.

All exercises in this track are compiled and linked as `PIE`, so `rel` should be used to generate relative addresses.

### Visibility

Labels (functions and data) defined in any section (e.g., `.text`, `.data`, `.rodata`) are visible within the same source file.
If declared `global`, they are visible to other source files as well.

Conversely, labels defined in other source files are visible to the current source file if declared `extern`.
In this case, there is no indication of data size in assembly, this must be known in advance.

```nasm
default rel

section .data

global number1 ; 'number1' is a variable visible to other source files
number1 db 200

extern number2 ; 'number2' is a variable visible to the current source file, but defined in another

section .text

extern sum ; sum is a function visible to the current source file, but defined in another

fn:
    mov dil, byte [number1]
    mov sil, byte [number2]
    call sum
    ...
```

[pointer]: https://en.wikipedia.org/wiki/Pointer_(computer_programming)
[lea]: https://www.felixcloutier.com/x86/lea
[rel]: https://www.nasm.us/xdoc/2.16.03/html/nasmdoc3.html#section-3.3
[data]: https://en.wikipedia.org/wiki/Data_segment
