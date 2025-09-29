# Introduction

Memory is usually allocated for the program by the Operational System (OS) in a general layout:

```
+------------------------+
| high |     stack       |
|      |      ...        |
|      |     heap        |
|      |   section .bss  |
|      |   section .data |
|      |   section .text |
| low  |    reserved     |
+------+-----------------+
```

Other sections may be available to use, depending on the assembler and OS.

The functions we have defined until now were all in `section .text`.
This section holds read-only executable data.

Other sections are used to declare data variables, that may be read-only, write-only or read-and-write.

Data variables declared in any of these sections are accessible from any function in the same source file.
They also persist across the entire duration of the program.

## Sections

### Section .data

The initialized data is declared in the `section .data`.

In NASM, an initialized variable has a name (`label`), a directive that indicates the data size, and a list of values separated by comma.
Each of these is separated with a space from the other and the label might optionally be followed by a `:`.

The main directives and their related data sizes are:

| directive | size |
|:---------:|:-----|
| db | 1 byte  |
| dw | 2 bytes |
| dd | 4 bytes |
| dq | 8 bytes |

For instance, this declares a byte variable named `space` with the value `10`:

```nasm
section .data
    space db 10
```

Variables declared in `section .data` are mutable, ie, they are read-and-write.

### Section .rodata

The `section .rodata` is similar to `section .data`.
Both sections contain initialized data, which is declared in the same way.

The main difference between them is that data variables in `section .rodata` are immutable, ie, they are read-only.

### Section .bss

Uninitialized data is declared in the `section .bss`.

On most platforms, this data is filled with zero by the OS at the start of the program.

In NASM, an uninitialized variable has a name (`label`), a directive that indicates data size and the number of elements to be reserved.
Each of these is separated with a space from the other.

The main directives and their related data sizes are:

| directive | size |
|:---------:|:-----|
| resb | 1 byte  |
| resw | 2 bytes |
| resd | 4 bytes |
| resq | 8 bytes |

For instance, this reserves uninitialized space for `3` bytes in a variable named `example`:

```nasm
section .bss
    example resb 3
```

And this reserves uninitialized space for `10` times `8` bytes (so, `80` bytes) in a variable named `arr`:

```nasm
section .bss
    arr resq 10
```

Variables in `section .bss` are mutable, ie, they are read-and-write.

## Accessing data

### Labels and Indirection

Declared data must have a name associated with it.
This name is called a `label`.

A `label` is a symbol that encodes the specific address of the variable in memory.

In NASM, trying to access data directly with its label does not yield the memory allocated, but its address:

```nasm
section .data
    example dq 27 ; this declares a 8-byte variable initialized with 27

section .text
fn:
    mov rax, example ; this stores the address of the declared variable in rax, not its contents
    ...
```

In order to access the contents of the memory, it's necessary to `dereference` it.
This is called `indirection`.

In NASM, this is done with `[]`:

```nasm
section .data
    example dq 27 ; this declares a 8-byte variable initialized with 27

section .text
fn:
    mov rax, [example] ; this dereferences example and access the value stored in memory (27)
    ...
```

However, there are some situations when there might be an ambiguity regarding the size of the memory dereferenced.
In those cases, a prefix specifying this size must be used.

These are the most important prefixes and their sizes in a typical x86-64 program:

| prefix | size |
|:-------|:-----|
| byte  | 1 byte  |
| word  | 2 bytes |
| dword | 4 bytes |
| qword | 8 bytes |

The last example can be rewritten with the size prefix:

```nasm
section .data
    example dq 27 ; this declares a 8-byte variable initialized with 27

section .text
fn:
    mov rax, qword [example] ; this dereferences example and access the value stored in memory (27)
    ...
```

It's good practice to always use a prefix when dereferencing memory.

### Arrays

Any data in assembly is a sequence of bytes.
This means that any data can be viewed as an `array` of those underlying bytes.

In order to access any byte after the first, it is necessary to compute its effective address.
An effective address is an expression that may consist of:

- a base address, for instance, the one indicated by the label of a variable;
- one index register scaled by `1`, `2`, `4` or `8`; and
- a signed 32-bit displacement.

Notice that this address is 0-indexed, so that a base address, without any offset, points to the first byte of a variable.

```nasm
section .data
    example dq 10 ; example is a 8-byte variable
                  ; so it can be viewed as an array of those 8 bytes
                  ; which can be accessed from index 0 to index 7

section .text
fn:
    mov al, byte [example] ; this accesses the first byte
    mov r8b, byte [example + 2] ; this accesses the third byte
    mov edx, dword [example + 1] ; this accesses 4 bytes starting at the second
```

An initialized variable declared with a list of values is an array of those values, each element having the size specified.
The same can be said for uninitialized variables which reserve more than 1 element.

However, offsets are always for *bytes*, even when each element in the array has a greater size:

```nasm
section .data
    arr dq 4, 8, 15, 23, 42 ; this declares an array with 5 qwords (8-bytes values), so 40 bytes in total
                            ; the value 4 is a qword that can be accessed at index 0 (the first byte)
                            ; the value 8 is a qword that can be accessed at index 8, since each element occupy 8 bytes
                            ; elements 15, 23 and 42 can be accessed at indexes 16, 24 and 32, respectively

section .text
fn:
    mov rdx, 2
    mov rcx, qword [arr + 8*rdx + 8]  ; rdx is an index register scaled by 8
                                      ; 8 is a signed 32-bit displacement
                                      ; rcx now holds 8-bytes stored in 'arr' starting at offset:
                                      ; 8*rdx(2) + 8 = 16 + 8 = 24
                                      ; this is the fourth element of the array, ie, the element 23
```

### The Lea instruction

There's an instruction called `lea` which computes an effective memory address and stores that address in the destination register.

This instruction uses a memory-form operand, but it does *not* read memory.
Instead, it computes the effective address expression and writes the result in the destination operand.

One of the advantages of `lea` is that it uses address-calculation arithmetic to compute a value.
This makes it useful to do arithmetic computations even when none of the registers holds a memory address:

```nasm
mov rcx, 3
mov rdx, 5
lea rax, [rcx + 8*rdx + 10] ; rax = rcx(3) + 8*rdx(5) + 10 = 3 + 40 + 10 = 53
```

### Relative Addressing

When accessing memory locations, the default behavior in NASM is to generate `absolute addresses`.
This means that the assembler usually produces a fixed memory address.

However, this can sometimes introduce security concerns, by making addresses predictable to an attacker.

One possible mitigation for this involves randomizing locations of memory regions, so that an attacker can't reliably predict addresses.
In order to do that, executables must be built as `PIE (Position Independent Executable)`.

However, in a PIE, the final address of a variable is not known at link time.
So, code instead computes addresses as an offset from the value in a special register called `rip`, which points to the next instruction to be executed.

This is usually called `RIP-relative addressing`.

In NASM you can request RIP-relative access with the `rel` operator:

```nasm
mov rax, qword [rel variable]
```

Relative addressing can also be made the default for a source file with `default rel` at the top.

When you need to form more complex addresses, it's often necessary to load the variable's address into a register first:

```nasm
lea rax, [rel variable]
mov rcx, qword [rax + 8*r8 + 4]
```

All exercises in this track are compiled and linked as PIE, so `rel` should be used to generate RIP-relative addresses.
