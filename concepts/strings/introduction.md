# Introduction

## ASCII Characters

In assembly, the most common encoding for representing characters is `ASCII`.

In ASCII encoding, a character is associated with a value ranging from 0 to 127.
This value is stored in the first 7 bits of 1 byte.
The last bit (the most significant) is cleared.

## Strings

A `string` is a sequence of characters.
In assembly, it is implemented as an array.

In x86-64 there are some instructions for loading, moving and storing values in a string.

Those instructions can be used not only with bytes, but with other data sizes as well.
Since assembly does not enforce abstractions, they are also not limited to sequences of elements representing characters.

They usually expect the source to be a memory location in `rsi` and the destination to be a memory location in `rdi`.

Many of those instructions are actually a family of related instructions, each operating on a different size.
In those cases, a suffix is appended to indicate this size:

```
+--------+----------+
| prefix |   size   |
+--------+----------+
|   b    |  1 byte  |
+--------+----------+
|   w    |  2 bytes |
+--------+----------+
|   d    |  4 bytes |
+--------+----------+
|   q    |  8 bytes |
+--------+----------+
```

Those instructions modify the register(s) used according to the value of the `direction flag (DF)`.

If the DF is cleared, addresses in `rsi` and/or `rdi` are increased by the indicated size.
And, if the DF is set, addresses are instead decreased by the same amount.

The instruction `cld` clears the direction flag, whereas the instruction `std` sets it.

The `System V ABI` states that the direction flag must be cleared at function entry.
So, this is the default behavior.

### Lods

The `lods` family of instructions load an element from a memory location in `rsi`.

This element is moved to `rax` and the address in `rsi` is modified according to the size of the element.

So, for instance, `lodsw` loads 2 bytes from the memory address in `rsi`, modifying `rsi` by 2.

### Stos

The `stos` family of instructions stores an element in `rax` into a memory location in `rdi`.

The address in `rdi` is modified according to the size of the element.

So, for instance, `stodsd` stores 4 bytes in `eax` into the memory address in `rdi`, modifying `rdi` by 4.

### Movs

The `movs` family of instructions copies an element from the memory location in `rsi` into the memory location in `rdi`.

The addresses in both `rsi` and `rdi` are modified according to the size of the element.

So, for instance, `movsq`:
- copies 8 bytes from the memory address in `rsi`, modifying `rsi` by 8; and
- stores 8 bytes into the memory address in `rdi`, modifying `rdi` by 8.

### Cmps

The `cmps` family of instructions compares the elements in the memory locations in `rsi` and `rdi`, setting flags in `rflags` according to the result.

The addresses in both `rsi` and `rdi` are modified according to the size of the element.

So, for instance, `cmpsb` compares 1 byte in the memory address in `rsi` with 1 byte in the memory address in `rdi`, modifying both registers by 1.

### Scas

The `scas` family of instructions compares the value in `rax` with the element from the memory address in `rdi`, setting flags in `rflags` according to the result.

The address in `rdi` is modified according to the size of the element.

So, for instance, `scasw` compares the value in `ax` with 2 bytes in the memory address in `rdi`, modifying `rdi` by 2.

### Rep

The `rep` family of instructions don't interact directly with memory.

Instead, they can be added as prefixes to the other mentioned instructions, *repeating* those instructions.

There are 3 instructions in this group:

- The `rep` prefix can be added to the `movs`, `lods`, and `stos` instructions;
- The `repe` and `repne` (equivalently, `repz` and `repnz`) prefixes can be added to the `cmps` and `scas` instructions.

All those prefixes repeat an instruction by a number of times equal to the value in `rcx`.
At each time, the value in `rcx` is decreased by 1.

However, `repe` and `repne` stop execution before this if the `zero flag (ZF)` is set or cleared, respectively.

It's important to notice that `rcx` is not an operand to those instructions.
Its value must be adjusted before using them.
