# Introduction

## Characters

A **character encoding** is a specific convention used to represent elements of text in a natural language as a sequence of bytes.
An "element of text" here may be any unit that has significance in a natural language, for example, letters, spaces, punctuation, emojis, ideograms, etc.

NASM (The Netwide Assembler, the assembler used by this track) has support to the definition of data using **ASCII**.

Characters in NASM have up to 8 bytes and may be defined using single quotes (`'`), double quotes (`"`) or backticks (`` ` ``):

```nasm
mov rax, '0' ; this copies the ASCII character '0' (decimal value 48)
mov rcx, "z" ; this copies the ASCII character 'z' (decimal value 122)
mov rdx, ` ` ; this copies the ASCII character ' ' (decimal value 32)
```

Special characters must be defined in backticks and escaped with `\`:

```nasm
mov rax, `\n` ; this copies the ASCII character newline (decimal value 10)
mov rcx, `\t` ; this copies the ASCII character tab (decimal value 9)
```

NASM also has support to **unicode characters** in UTF-8, specified with `\u` or `\U` and in backticks:

```nasm
mov rax, `\u263a` ; UTF-8 smiley face (☺), value U+263a
mov rcx, `\u0393` ; UTF-8 capital letter gamma (Γ), value U+0393
```

Note that there is no built-in support to any character encoding in x86-64 as a distinct type.
Data in assembly is a sequence of bytes and the interpretation of those bytes as a character, a number, or anything else, is left to the programmer.

For instance, the ASCII character '0' is a single byte with the value 48.
So, storing 48 into a byte is exactly the same as storing the ASCII character '0':

```nasm
mov al, '0' ; al has the value 48
mov cl, 48  ; cl has the value '0'
; al and cl now have the same value
```

For this same reason, manipulating characters is done by directly transforming the values in those bytes:

```nasm
mov al, 'A' ; al now has the value 'A', which is 65 in ASCII
add al, 32 ; al now has the value 97, which is 'a' in ASCII
; so, summing 32 to an uppercase ASCII letter makes it lowercase

mov al, 5 ; al now has the value 5
add al, 48 ; al now has the value 53, which is '5' in ASCII
; so, summing 48 (equivalently, '0') transforms a number between 0 and 9 into a ASCII digit
```

## Strings

A **string** is a sequence of characters.
In assembly, it is usually implemented as an array.

It is possible to declare a string in NASM in the same way any array might be declared:

```nasm
section .data
    string1 db "h", "e", "l", "l", "o"
```

One difference between strings and other arrays is that NASM also has support to the declaration of strings without a comma (`,`) separating values.
It is also possible to interleave values with commas:

```nasm
section .data
    string2 db "hello"
    string3 db "h", "ello"
```

Note that, as already mentioned, characters are just bytes (or sequence of bytes in unicode encoding):

```nasm
section .data
    string1 db "hi"
    string2 db "h", "i"
    string3 db 104, 105
; string1, string2 and string3 are all equivalent
```

Similarly, since each ASCII character takes a single byte, these are all equivalent:

```nasm
section .data
    string1 dw 'hello' ; 3 words (2-byte)
    string2 dw 'he', "ll", `o` ; 3 words (2-byte)
    string3 db `hello`, 0 ; 3 words (2-byte)
```

~~~~exercism/caution
In assembly, strings are not automatically ended by a ASCII NUL character (value `0`).

When interfacing with higher level languages, such as C, it is the programmer's responsibility to ensure the correct terminator, if any, is appended at the end of a string.
~~~~

## String instructions

Since strings are arrays, you can work with them in the same way as any array, by explicitly dereferencing memory:

```nasm
section .data
    hello_msg db "hello", 0

section .text
fn:
    lea rax, [rel hello_msg]
    mov cl, byte [rax]
    ret
```

In addition to that, there are some instructions for loading, moving and storing values in sequences of bytes in memory.
Although called _string instructions_, they can be used with any sequence of bytes in memory, i.e., with any array:

| instruction  | what it does                                                                                                      |
|--------------|-------------------------------------------------------------------------------------------------------------------|
| `lods`       | loads a value from a memory location indicated by `rsi` into `rax`                                                |
| `stos`       | stores a value from `rax` into a memory location indicated by `rdi`                                               |
| `movs`       | copies a value from a memory location indicated by `rsi` and stores it in a memory location indicated by `rdi`    |
| `cmps`       | compares the value in a memory location indicated by `rsi` with the value in a memory location indicated by `rdi` |
| `scas`       | compares the value in`rax` with the value in a memory location indicated by `rdi`                                 |

Note that those instructions do _not_ take any explicit operand.
Their operands are implicit.

As a rule of thumb:

1. When their source operand is a memory location, its address should be stored in `rsi` (`s` for source).
2. When their destination operand is a memory location, its address should be stored instead in `rdi` (`d` for destination).
3. If one of the operands is not a memory location, it is the `rax` register.

Note that those instructions automatically dereference memory addresses according to the specific operation they perform.

All of them may operate in different sizes.
A suffix is appended to indicate this size:

| prefix | meaning | size    |
|:------:|---------|:--------|
| `b`    | byte    | 1 byte  |
| `w`    | word    | 2 bytes |
| `d`    | dword   | 4 bytes |
| `q`    | qword   | 8 bytes |

For example:

```nasm
movsb ; copies one byte from the memory location whose address is in `rsi` and stores it into the memory location whose address is in `rdi`
lodsq ; copies one qword (8 bytes) from the memory location whose address is in `rsi` and stores it in `rax`
stosw ; stores one word (2 bytes) into the memory location whose address is in `rdi`
cmpsd ; compares one dword (4 bytes) in the memory locations whose addresses are in `rsi` and `rdi`, setting flags as per `cmp`
```

They also update any address used by the size of the operation.
This update is made according to the value of the **direction flag (DF)**:

- If the `DF` is cleared, addresses are _increased_ by the size of the operation.
- If the `DF` is set, addresses are instead _decreased_ by the same amount.

The System V ABI states that the direction flag must be cleared at function entry.
So, _the default behavior is for memory to be read/written in ascending order of addresses_.

The instruction `cld` can be used to clear the direction flag, whereas the instruction `std`, to set it:

```nasm
lea r8, [rdi]
lea r9, [rsi]

movsq ; both rdi and rsi increase (because `DF` is cleared by default) by 8 (`q` for qword)
; so now:
; rdi == r8 + 8
; rsi == r9 + 8

std ; sets `DF`
lodsw ; rsi decreases (because `DF` is set) by 2 (`w` for word)
; so now:
; rdi == r8 + 8
; rsi == r9 + 8 - 2 == r9 + 6

cld ; clears `DF`
stosd ; rdi increases (because `DF` is cleared) by 4 (`d` for dword)
; so now:
; rdi == r8 + 8 + 4 == r8 + 12
; rsi == r9 + 6
```

~~~~exercism/caution
The caller expects the `DF` to be cleared after any called function returns, as per System V ABI.
If you ever set the `DF`, make sure to clear it before `ret`.
~~~~

### Lods

This instruction _reads_ from a memory location whose address is in `rsi` and copies the value into `rax`.

The value in `rsi` is updated by the number of bytes read:

```nasm
lodsq ; copies one qword (8 bytes) from the address indicated by `rsi` to `rax`
; the address in `rsi` is now increased or decreased by 8, according to `DF` (by default, increased)
```

### Stos

This instruction copies the value in `rax` and _writes_ it into a memory location whose address in `rdi`.

The value in `rdi` is updated by the number of bytes written:

```nasm
stosw ; copies one word (2 bytes) from `rax` to the address indicated by `rdi`
; the address in `rdi` is now increased or decreased by 2, according to `DF` (by default, increased)
```

### Movs

This instruction _reads_ from a memory location whose address is in `rsi` and _writes_ the value to a memory location whose address is in `rdi`.
The value in `rax` is not affected by this instruction.

Both `rsi` and `rdi` are updated by the number of bytes copied from one memory location to the other:

```nasm
movsb ; copies one byte from the address indicated by `rsi` to the address indicated by `rdi`
; the addresses in `rsi` and `rdi` are now increased or decreased by 1, according to `DF` (by default, increased)
```

### Cmps

This instruction _reads_ from a memory location whose address is in `rsi` and also _reads_ from a memory location whose address is in `rdi`.
It then compares the values and updates flags, as per `cmp`.

Both `rsi` and `rdi` are updated by the number of bytes read from both locations:

```nasm
cmpsd ; reads one dword (4 bytes) from the addresses indicated by `rsi` and `rdi` and compares them
; the addresses in `rsi` and `rdi` are now increased or decreased by 4, according to `DF` (by default, increased)
```

### Scas

This instruction compares the value in `rax` with the value it _reads_ from a memory location whose address is in `rdi`.
It then updates flags, as per `cmp`.

The value in `rdi` is updated by the number of bytes read:

```nasm
scasb ; compares one byte in `rax` with 1 byte read from the memory location whose address is in `rdi`
; the address in `rdi` is now increased or decreased by 1, according to `DF` (by default, increased)
```

### Rep

Apart from those, the **rep** instruction does not interact directly with memory.
Instead, it can be added as a prefix to the other mentioned instructions, _repeating_ those instructions.

It works similarly to `loop`, i.e., it repeats an instruction by a number of times equal to the value in `rcx`.
At each time, the value in `rcx` is decreased by `1`.
Just as with the `loop` instructions, the value in `rcx` must be set before the instruction is used:

```nasm
mov rcx, 4
rep movsq ; this repeats movsq 4 times
          ; it copies 4 * 8 == 32 bytes from a memory location indicated by `rsi` to a memory location indicated by `rdi`
```

Apart from using `rcx` as a counter, `repe` (or `repz`) and `repne` (or `repnz`) follow the same semantics as `loope` and `loopne`, i.e., they also stop execution if the `zero flag (ZF)` is cleared or set, respectively.

However, all `rep` instructions differ from their `loop` equivalent in that they can only be used to repeat a single string instruction, not a block of instructions:

| instruction      | where can be added     | may stop earlier          |
|------------------|------------------------|---------------------------|
| `rep`            | `movs`, `lods`, `stos` | no                        |
| `repe`,`repz`    | `cmps`, `scas`         | yes — stops when ZF is 0  |
| `repne`, `repnz` | `cmps`, `scas`         | yes — stops when ZF is 1  |
