# Instructions

You maintain the macro library that a magazine's composition engine is built on.
The engine itself, the functions that lay out each page, is fixed and you do not write it.
What you write is the assemble-time machinery it is built from.

This exercise does not require you to write any function, only macros.
These macros are then included and called in functions already predefined in another file.

You have four tasks.

~~~~exercism/caution
Each macro is called by the exact name and argument order its task gives, so write them exactly.
Otherwise the file will not assemble.
~~~~

## 1. Name the format constants

The magazine's format is a handful of fixed numbers, and the rest of the layout refers to them only by name.
You should give each a readable name at assemble time:

- `COLUMN_COUNT` is `4`
- `COLUMN_STRIDE` is `18`
- `SPACE` is `0x20`, the blank byte
- `RULE` is `0x3D`, the byte `=`
- `RULE_WIDTH` is `4`
- `PLAIN` is `0x2E`, the byte `.`
- `RULED` is `0x2D`, the byte `-`
- `BOXED` is `0x23`, the byte `#`

The engine reports these in the order above.

```c
out = {4, 18, 32, 61, 4, 46, 45, 35} // the eight named values, in order
```

## 2. Write the `fill_run` macro

The engine blanks a galley and lays masthead rules by stamping a run of a single byte.
Capture that step as a multi-line macro the engine can call wherever a run needs filling.

First, define a readable name `COUNTER` for the register `rcx`.
Then, define the `fill_run` macro that should fill an array with N copies of a byte.
It takes three arguments in this order:

1. the destination address, passed in a 64-bit general-purpose register.
2. the count of bytes (N) to write, passed in a 64-bit general-purpose register or as an immediate.
3. the byte to write, passed in an immediate.

```x86asm
fill_run rdi, rax, SPACE
fill_run rdx, RULE_WIDTH, RULE
```

The `fill_run` macro may clobber `COUNTER` freely, but no other register.

Note that the count of bytes may be passed in a 64-bit general-purpose register, such as `rax` or `rsi`, or as an immediate, such as `10` or `4`.
You may consider that this count is never negative.

This macro is called in three times, in two different functions.

```c
length = 8
page   = {32, 32, 32, 32, 32, 32, 32, 32}

width  = 8
page   = {61, 61, 61, 61, 32, 32, 32, 32} // '====' then spaces
```

## 3. Write the `lay_columns` macro

The grid is fixed for the format, so the column starts can be computed at assemble time.

Define the `lay_columns` macro, that writes `COLUMN_COUNT` offsets, each a 64-bit integer.
It takes two arguments in this order:

1. the destination address, passed in a 64-bit general-purpose register
2. the left margin, passed in a 64-bit general-purpose register

```x86asm
lay_columns rsi, rax
```

The number of offsets to be written to the destination address is fixed and equal to `COLUMN_COUNT`.

Each offset is a 64-bit value calculated with `offset[i] = margin + i * COLUMN_STRIDE`, where `i` is the index of the offset starting at `0`, and `margin` is the second argument.

This macro may clobber its two register arguments, but no other.
It is called once.

```c
margin = 3
out    = {3, 21, 39, 57}
```

## 4. Write the `set_header` macro

Each of the three standing sections has a header style fixed by the format, so the byte is known at assemble time.

Define `set_header`, taking two arguments in this order:

1. the destination address.
2. a literal style id passed as an immediate, where `0` is plain, `1` is ruled, and `2` is boxed.

The destination address is the expression of an effective memory address.
It takes a base register that may be summed with an index register scaled by `1`, `2`, `4` or `8`, and an immediate:

```x86asm
set_header rdx+8*rcx+2, 1
```

Select the header byte (`PLAIN`, `RULED`, or `BOXED`) with conditional assembly (`%if` / `%elif` / `%else`) rather than a runtime branch.

This macro should not clobber any register.
It is called three times in the same function.

```c
pitch = 4
out   = {46, 0, 0, 0, 45, 0, 0, 0, 35} // '.', '-', '#'
```
