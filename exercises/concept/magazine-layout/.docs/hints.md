# Hints

## General

- Your solution file is included in another, which calls your macros.
  Keep each macro's name and argument order exactly as the task gives them, or the file will not assemble.
- A macro's arguments are tokens, substituted as `%1`, `%2`, `%3` wherever they appear in the body.
  They may be registers, address expressions, or literals, as long as each expansion is a valid instruction.
- Each macro is checked on which registers it leaves untouched, not only on what it writes.
  Read the clobber note in each task and change only the registers it permits.

## 1. Name the format constants

- A single-line `%define` gives a name to a value, so the rest of the code can read the name instead of a bare number.
  For a fixed number, `equ` does the same and is the usual choice for a constant.
- The byte constants can be written either as hexadecimal (`0x20`) or as a character literal (`' '`).
  Both assemble to the same value.

## 2. Write the `fill_run` macro

- You should give `rcx` the readable name `COUNTER`.
- `fill_run` is a multi-line macro that takes 3 arguments.
  Multi-line macros are defined with `%macro ... %endmacro`.
- The first argument of `fill_run` is a memory address in a 64-bit general-purpose register.
  The second is the count that may be passed in a 64-bit general-purpose register or as an immediate.
  The third is a byte to be written, as an immediate.
  You should plan the code in the macro to account for these specifications.
- The only register `fill_run` is allowed to modify is `COUNTER`.
- A loop inside a macro usually needs a label prefixed with `%%`.
  Without this prefix, the same label is created each time the macro is called, which can cause an error if the macro is called more than once.

## 3. Write the `lay_columns` macro

- `lay_columns` is a multi-line macro that takes 2 arguments.
  Multi-line macros are defined with `%macro ... %endmacro`.
- Both arguments of `lay_columns` are passed in 64-bit general-purpose registers.
  The first is a memory address, the second is an integer.
  You should plan the code in the macro to account for these specifications.
- The only registers `lay_columns` is allowed to modify are the two passed as arguments.
- The number of offsets the macro must write is fixed at assembly-time.
  You may use `%rep ... %endrep` to repeat the code.
- The offset calculation is done with `offset[i] = margin + i * COLUMN_STRIDE`.
  `margin` is the second argument of the macro.
  `i` is a loop counter that may be defined as an `%assign` variable.

## 4. Write the `set_header` macro

- `set_header` is a multi-line macro that takes 2 arguments.
  Multi-line macros are defined with `%macro ... %endmacro`.
- The first argument of `set_header` is the expression of an effective memory address.
  It takes a base register that may be summed with an index register scaled by `1`, `2`, `4` or `8`, and an immediate.
  This means a plain `rdi` is valid, as is `rdi+rax*4+2`.
- The second argument of `set_header` is an immediate that may have the values `0`, `1` or `2`.
- `set_header` must not modify any register at all.
- You should conditionally copy one byte to the destination address at assemble-time, according to the second argument.
  A value of `0` should copy `PLAIN`, a value of `1` should copy `RULED`, and a value of `2` should copy `BOXED`.
