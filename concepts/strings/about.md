# About

## Characters

### Declaring characters

A [character encoding][char-encoding] is a specific convention used to represent elements of text in a natural language as a sequence of bytes.
An "element of text" here may be any unit that has significance in a natural language, for example, letters, spaces, punctuation, emojis, ideograms, etc.

NASM (The Netwide Assembler, the assembler used by this track) has support to the definition of data using [ASCII][ascii].

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

NASM also has support to [unicode characters][unicode] in [UTF-8][utf8], specified with `\u` or `\U` and in backticks:

```nasm
mov rax, `\u263a` ; UTF-8 smiley face (☺), value U+263a
mov rcx, `\u0393` ; UTF-8 capital letter gamma (Γ), value U+0393
```

Notice that there is no built-in support to any character encoding in x86-64 as a distinct type.
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

### Declaring strings

A [string][string] is a sequence of characters.
In assembly, it is usually implemented as an array.

It is possible to declare a string in NASM using the directive `db`, as usual for declared data.
Each character in a string is interpreted as a different byte (or sequence of bytes, for unicode characters with more than 1 byte).
Even though this defines an array, it is not necessary to use a comma (`,`) to separate values:

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

~~~~exercism/note
In assembly, strings are not automatically ended by a ASCII NUL character (value `0`).
When interfacing with higher level languages, such as C, it is the programmer's responsibility to ensure the correct terminator, if any, is appended at the end of a string.
~~~~

### String instructions

In x86-64 there are some instructions for loading, moving and storing values in a string.

Although called _string instructions_, they can be used not only with bytes, but with other data sizes as well.
They are also not limited to sequences of elements representing characters, but work with any array in memory.

They usually expect the source to be a memory location in `rsi` and/or the destination to be a memory location in `rdi`.

Those instructions are actually a family of related instructions, each operating on a different size.
A suffix is appended to indicate this size:

| prefix | size    |
|:------:|:--------|
| b      | 1 byte  |
| w      | 2 bytes |
| d      | 4 bytes |
| q      | 8 bytes |

Those instructions modify the register(s) used according to the value of the **direction flag (DF)**.

If the DF is cleared, addresses in `rsi` and/or `rdi` are increased by the indicated size.
And, if the DF is set, addresses are instead decreased by the same amount.

The instruction [cld][cld] clears the direction flag, whereas the instruction [std][std] sets it.

The System V ABI states that the direction flag must be cleared at function entry.
So, the default behavior is for memory to be read/written in ascending order of addresses.

The instructions are:

| instruction  | what it does                                          | example                                                 |
|--------------|-------------------------------------------------------|---------------------------------------------------------|
| [lods][lods] | loads from the memory location in `rsi` into `rax`    | `lodsw` loads 2 bytes into `ax`, changing `rsi` by 2    |
| [stos][stos] | stores `rax` into the memory location in `rdi`        | `stosd` stores 4 bytes from `eax`, changing `rdi` by 4  |
| [movs][movs] | copies between memory locations (`rsi` to `rdi`)      | `movsb` copies 1 byte, changing `rsi` and `rdi` by 1    |
| [cmps][cmps] | compares between memory locations (`rsi` and `rdi`)   | `cmpsq` compares 8 bytes, changing `rsi` and `rdi` by 8 |
| [scas][scas] | compares `rax` with value in memory location in `rdi` | `scasb` compares `al`, changing `rdi` by 1              |

Both `cmps` and `scas` make comparisons following the same semantics as `cmp`, setting flags accordingly.

Apart from those, the [rep][rep] family of instructions don't interact directly with memory.

Instead, they can be added as prefixes to the other mentioned instructions, _repeating_ those instructions.
They repeat an instruction by a number of times equal to the value in `rcx`.
At each time, the value in `rcx` is decreased by 1.

Note, however, that `rcx` is not an operand to those instructions.
Its value must be adjusted before using them.

Apart from using `rcx` as a counter, `repe` and `repne` also stop execution if the zero flag (ZF) is set or cleared, respectively.

There are 3 instructions in this group:

| instruction      | where can be added     | may stop earlier   |
|------------------|------------------------|--------------------|
| `rep`            | `movs`, `lods`, `stos` | no                 |
| `repe`,`repz`    | `cmps`, `scas`         | yes (ZF set)       |
| `repne`, `repnz` | `cmps`, `scas`         | yes (ZF cleared)   |

[char-encoding]: https://en.wikipedia.org/wiki/Character_encoding
[ascii]: https://en.wikipedia.org/wiki/ASCII
[unicode]: https://en.wikipedia.org/wiki/Unicode
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
