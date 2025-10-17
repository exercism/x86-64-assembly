# About

Any data in assembly is a sequence of bytes.
This means that any data can be viewed as an **[array][array]** of those underlying bytes.

## Accessing elements in an array

In order to access any value in memory, it is necessary to compute its **effective address**.

An effective address is an expression that may consist of:

- a _base address_, for instance, the one indicated by the label of a variable.
- one _index register_, possibly scaled by `1`, `2`, `4` or `8`.
- a signed 32-bit _displacement_, which is a number to be added to (or subtracted from) the base address.

Notice that this address is _0-indexed_, so that a base address, without any offset, points to the first byte of a variable.
This is why dereferencing memory using just a label, without any offset, yields a value starting at its first byte.

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
However, offsets are always for _bytes_, even when each element in the array has a greater size:

```nasm
section .data
    arr dq 4, 8, 15, 23, 42 ; this defines an array of 5 qwords (8-byte elements)
                            ; the first qword has value 4 and can be accessed at [arr] (offset 0)
                            ; any subsequent qword can be accessed at offsets increasing by the size in bytes of each element (8)

section .text
fn:
    mov rdx, 2
    lea rcx, [rel arr]
    mov rax, qword [rcx + 8*rdx + 8]  ; rdx is an index register scaled by 8
                                      ; 8 is a signed 32-bit displacement
                                      ; rax now holds 8-bytes stored in 'arr' starting at offset:
                                      ; 8*rdx(2) + 8 = 16 + 8 = 24
                                      ; this is the fourth element of the array, ie, the element 23
```

## Computing the size of an initialized array

NASM (The Netwide Assembler - the assembler used by this track) has a special symbol (`$`) that indicates the current location in memory.
This symbol offers a convenient way to compute the total size in memory occupied by an array:

```nasm
section .data
    example dd 4, 5, 6, 18, 20, 76, -12, 34
    example_length dq $ - example
```

When used just after `example`, `$` has the address in memory for the end of the array.
This means that `$ - example` is the difference between that address and the one pointed by the label `example`.
This is exactly the total size, in bytes, occupied by the array pointed by `example`.

So, by defining `example_length` with this value, we have created a 8-byte variable which stores the size, or length, of the array, in bytes.

## Section .bss

Uninitialized data is declared in the **[section .bss][bss]**.

On most platforms, this data is filled with zero by the OS at the start of the program.

In NASM, an uninitialized variable has a name, a directive that indicates data size and the number of elements to be reserved.
Each of these is separated with a space from the other.

The main directives and their related data sizes are:

| directive | size    |
|:---------:|:--------|
| resb      | 1 byte  |
| resw      | 2 bytes |
| resd      | 4 bytes |
| resq      | 8 bytes |

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

Variables in section .bss are mutable, ie, they are read-and-write.

Unitialized data can be accessed in the same way as initialized data, by using its effective address.
Similarly, they are also of static storage duration and accessible from any function in the same source file (and, if declared `global`, in other source files as well).

## Accessing array addresses with the Lea instruction

As it was explored in a previous concept, the `lea` instruction computes an effective memory address.
So, it can be used to compute the address of any element in an array, following the same semantics.

However, in relative addressing, it is often necessary to load the variable's address into a register before forming a more complex address:

```nasm
lea rax, [rel variable]
lea rdx, [rax + 8*r10 - 20]
```

~~~~exercism/note
One of the advantages of `lea` is that it uses address-calculation arithmetic to compute a value, without actually accessing the memory in that address.
This makes it useful to do arithmetic computations even when none of the registers holds a memory address:

```nasm
mov rcx, 3
mov rdx, 5
lea rax, [rcx + 8*rdx + 10] ; rax = rcx(3) + 8*rdx(5) + 10 = 3 + 40 + 10 = 53
```
~~~~

[array]: https://en.wikipedia.org/wiki/Array_(data_structure)
[bss]: https://en.wikipedia.org/wiki/.bss
