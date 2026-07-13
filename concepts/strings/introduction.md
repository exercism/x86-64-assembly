# Introduction

## Characters

A **character encoding** is a specific convention used to represent elements of text in a natural language as a sequence of bytes.
An "element of text" here may be any unit that has significance in a natural language, for example, letters, spaces, punctuation, emojis, ideograms, etc.

NASM (The Netwide Assembler, the assembler used by this track) has support for the definition of data using **ASCII**.

Character constants in NASM may be up to 8 bytes long and may be defined using single quotes (`'`), double quotes (`"`) or backticks (`` ` ``):

```x86asm
mov rax, '0' ; this copies the ASCII character '0' (decimal value 48)
mov rcx, "z" ; this copies the ASCII character 'z' (decimal value 122)
mov rdx, ` ` ; this copies the ASCII character ' ' (decimal value 32)
```

Special characters must be defined in backticks and escaped with `\`:

```x86asm
mov rax, `\n` ; this copies the ASCII character newline (decimal value 10)
mov rcx, `\t` ; this copies the ASCII character tab (decimal value 9)
```

Note that there is no built-in support for any character encoding in x86-64 as a distinct type.
Data in assembly is a sequence of bytes and the interpretation of those bytes as a character, a number, or anything else, is left to the programmer.

For instance, the ASCII character '0' is a single byte with the value 48.
So, storing 48 into a byte is exactly the same as storing the ASCII character '0':

```x86asm
mov al, '0' ; al has the value 48
mov cl, 48  ; cl has the value '0'
; al and cl now have the same value
```

For this same reason, manipulating characters is done by directly transforming the values in those bytes:

```x86asm
mov al, 'A' ; al now has the value 'A', which is 65 in ASCII
add al, 32 ; al now has the value 97, which is 'a' in ASCII
; so, summing 32 to an uppercase ASCII letter makes it lowercase

mov al, 5 ; al now has the value 5
add al, 48 ; al now has the value 53, which is '5' in ASCII
; so, summing 48 (equivalently, '0') transforms a number between 0 and 9 into an ASCII digit
```

## Strings

A **string** is a sequence of characters.
In assembly, it is usually implemented as an array.

It is possible to declare a string in NASM in the same way any array might be declared:

```x86asm
section .data
    string1 db "h", "e", "l", "l", "o"
```

One difference between strings and other arrays is that NASM also has support for the declaration of strings without a comma (`,`) separating values.
It is also possible to interleave values with commas:

```x86asm
section .data
    string2 db "hello"
    string3 db "h", "ello"
```

Note that, as already mentioned, characters are just bytes (or a sequence of bytes in Unicode encoding):

```x86asm
section .data
    string1 db "hi"
    string2 db "h", "i"
    string3 db 104, 105
; string1, string2 and string3 are all equivalent
```

Since each ASCII character takes a single byte, any subsequent byte in a wider size is `0`.
For example, declaring `'a'` as a qword (8 bytes) means the first byte is `'a'` (`97`) and the other seven bytes are all `0`.

For this reason, these are all equivalent:

```x86asm
section .data
    ; in all of the following, "hello" takes 5 bytes
    string1 dw 'hello'         ; 3 words (2-byte) - 5 bytes for "hello" + 0
    string2 dw 'he', "ll", `o` ; 3 words (2-byte) - 5 bytes for "hello" + 0
    string3 db `hello`, 0      ; 6 bytes - 5 bytes for "hello" + 0
```

~~~~exercism/caution
In assembly, strings are not automatically ended by an ASCII NUL character (value `0`).

When interfacing with higher-level languages, such as C, it is the programmer's responsibility to ensure the correct terminator, if any, is appended at the end of a string.
~~~~

## String instructions

Since strings are arrays, you can work with them in the same way as any array, by explicitly dereferencing memory:

```x86asm
section .data
    hello_msg db "hello", 0

section .text
fn:
    lea rdi, [rel hello_msg]
    mov al, byte [rdi]       ; al == 'h'
    mov cl, byte [rdi + 4]   ; cl == 'o'
    ret
```

In addition to that, there are some instructions for loading, moving and storing values in sequences of bytes in memory.
Although called _string instructions_, they can be used with any sequence of bytes in memory, i.e., with any array.

The three most important string instructions are `lods`, `stos` and `movs`:

| instruction | what it does                                                                                                      |
| ----------- | ----------------------------------------------------------------------------------------------------------------- |
| `lods`      | loads a value from a memory location indicated by `rsi` into `rax`                                                |
| `stos`      | stores a value from `rax` into a memory location indicated by `rdi`                                               |
| `movs`      | copies a value from a memory location indicated by `rsi` and stores it in a memory location indicated by `rdi`    |

Note that those instructions do _not_ take any explicit operand.
Their operands are implicit.

As a rule of thumb:

1. When their source operand is a memory location, its address should be stored in `rsi` (`s` for source).
2. When their destination operand is a memory location, its address should be stored instead in `rdi` (`d` for destination).
3. If one of the operands is not a memory location, it is the `rax` register.

Note that those instructions automatically dereference memory addresses according to the specific operation they perform.

All of them may operate in different sizes.
A suffix is appended to indicate this size:

| suffix | meaning | size    |
| :----: | ------- | :------ |
|  `b`   | byte    | 1 byte  |
|  `w`   | word    | 2 bytes |
|  `d`   | dword   | 4 bytes |
|  `q`   | qword   | 8 bytes |

For example:

```x86asm
movsb ; copies one byte from the memory location whose address is in `rsi` and stores it into the memory location whose address is in `rdi`
lodsq ; copies one qword (8 bytes) from the memory location whose address is in `rsi` and stores it in `rax`
stosw ; stores one word (2 bytes) from `ax` into the memory location whose address is in `rdi`
```

They also update any address used by the size of the operation.
This update is made according to the value of the **direction flag (DF)**:

- If the `DF` is cleared, addresses are _increased_ by the size of the operation.
- If the `DF` is set, addresses are instead _decreased_ by the same amount.

The System V ABI states that the direction flag must be cleared at function entry.
So, _the default behavior is for memory to be read/written in ascending order of addresses_.

The instruction `cld` can be used to clear the direction flag, whereas the instruction `std`, to set it:

```x86asm
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

### Rep

Apart from those, the **rep** instruction does not interact directly with memory.
Instead, it can be added as a prefix to the other mentioned instructions, _repeating_ those instructions.

When prefixed with `rep`, string instructions are repeated a number of times equal to the value in `rcx`.
Each time, the value in `rcx` is decreased by `1`.
Note that the value in `rcx` must be set before the instruction is used:

```x86asm
mov rcx, 4
rep movsq ; this repeats `movsq` 4 times
          ; it copies 4 * 8 == 32 bytes from a memory location indicated by `rsi` to a memory location indicated by `rdi`
```

~~~~exercism/advanced
On modern CPUs, `rep movs` and `rep stos` are usually fast options when moving data in large blocks.
Other string instructions, and even `movs` and `stos` when operating without `rep`, however, are usually slower than a plain loop.

A more in-depth view on this topic can be found in [Chapter 16.9, "String instructions", of this reference book][agner-optimization-guide].

[agner-optimization-guide]: https://www.agner.org/optimize/optimizing_assembly.pdf#%5B%7B%22num%22%3A261%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C87%2C785%2C0%5D
~~~~
