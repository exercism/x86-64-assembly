# About

## ASCII Characters

In assembly, the most common encoding for representing characters is [ASCII][ascii].

In ASCII encoding, a character is associated with a value ranging from 0 to 127.
This value is stored in the first 7 bits of 1 byte.
The last bit (the most significant) is cleared.

NASM, the assembler used by the track, also supports [UTF-8][utf8] encoding.

~~~~exercism/note
In x86-64, there's no difference between a character and a number.

For instance, the character '0' is a byte with the value 48.
So, storing 48 into a byte is exactly the same as storing the character '0':

```nasm
mov al, '0' ; al has the value 48
mov cl, 48  ; cl has the value '0'
; al and cl now have the same value
```
~~~~

## Strings

A [string][string] is a sequence of characters.
In assembly, it is implemented as an array.

In x86-64 there are some instructions for loading, moving and storing values in a string.

Those instructions can be used not only with bytes, but with other data sizes as well.
They are also not limited to sequences of elements representing characters.

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

The instruction [cld][cld] clears the direction flag, whereas the instruction [std][std] sets it.

The `System V ABI` states that the direction flag must be cleared at function entry.
So, the default behavior is for memory to be read/written in ascending order of addresses.

### Lods

The [lods][lods] family of instructions loads an element from the memory location in `rsi` into `rax`.
The address in `rsi` is modified according to the size of the element.

So, for instance, `lodsw` loads 2 bytes from the memory address in `rsi` into `ax`, modifying `rsi` by 2.

### Stos

The [stos][stos] family of instructions stores an element from `rax` into a memory location in `rdi`.
The address in `rdi` is modified according to the size of the element.

So, for instance, `stodsd` stores 4 bytes from `eax` into the memory address in `rdi`, modifying `rdi` by 4.

### Movs

The [movs][movs] family of instructions copies an element from the memory location in `rsi` into the memory location in `rdi`.
The addresses in both `rsi` and `rdi` are modified according to the size of the element.

So, for instance, `movsq`:
- copies 8 bytes from the memory address in `rsi`, modifying `rsi` by 8; and
- stores those 8 bytes into the memory address in `rdi`, modifying `rdi` by 8.

### Cmps

The [cmps][cmps] family of instructions compares the elements in the memory locations in `rsi` and `rdi`, setting flags in `rflags` according to the result.
The addresses in both `rsi` and `rdi` are modified according to the size of the element.

So, for instance, `cmpsb` compares 1 byte in the memory address in `rsi` with 1 byte in the memory address in `rdi`, modifying both registers by 1.

### Scas

The [scas][scas] family of instructions compares the value in `rax` with the element from the memory address in `rdi`, setting flags in `rflags` according to the result.
The address in `rdi` is modified according to the size of the element.

So, for instance, `scasw` compares the value in `ax` with 2 bytes in the memory address in `rdi`, modifying `rdi` by 2.

### Rep

The [rep][rep] family of instructions don't interact directly with memory.

Instead, they can be added as prefixes to the other mentioned instructions, *repeating* those instructions.

There are 3 instructions in this group:

- The `rep` prefix can be added to the `movs`, `lods`, and `stos` instructions;
- The `repe` and `repne` (equivalently, `repz` and `repnz`) prefixes can be added to the `cmps` and `scas` instructions.

All those prefixes repeat an instruction by a number of times equal to the value in `rcx`.
At each time, the value in `rcx` is decreased by 1.

However, `repe` and `repne` stop execution earlier if the `zero flag (ZF)` is set or cleared, respectively.

It's important to notice that `rcx` is not an operand to those instructions.
Its value must be adjusted before using them.

[ascii]: https://en.wikipedia.org/wiki/ASCII
[utf8]: https://en.wikipedia.org/wiki/UTF-8
[string]: https://en.wikipedia.org/wiki/String_(computer_science)
[lods]: https://www.felixcloutier.com/x86/lods:lodsb:lodsw:lodsd:lodsq
[stos]: https://www.felixcloutier.com/x86/stos:stosb:stosw:stosd:stosq
[movs]: https://www.felixcloutier.com/x86/movs:movsb:movsw:movsd:movsq
[cmps]: https://www.felixcloutier.com/x86/cmps:cmpsb:cmpsw:cmpsd:cmpsq
[scas]: https://www.felixcloutier.com/x86/scas:scasb:scasw:scasd
[rep]: https://www.felixcloutier.com/x86/rep:repe:repz:repne:repnz
[cld]: https://www.felixcloutier.com/x86/cld
[std]: https://www.felixcloutier.com/x86/std
