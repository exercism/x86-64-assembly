# Hints

## General

- x86-64 addresses in memory are 64-bit (8-byte) numbers.
- You should use `rel` to form valid relative addresses in memory.

## 1. Get the RGB value for a color

- x86-64 addresses in memory are 64-bit (8-byte) numbers.
- You should use `rel` to form valid relative addresses in memory.
- In order to access contents stored in an address in memory, you need to dereference it using `[]`.
- 32-bit (4-byte) integers are returned in `eax`.

## 2. Add base color

- x86-64 addresses in memory are 64-bit (8-byte) numbers.
- You should use `rel` to form valid relative addresses in memory.
- Initialized variables are defined in _section .data_.
- A variable must be declared `global` to be visible to other source files.
- You can reuse the already implemented `get_color_value` function.

## 3. Define constants for primary colors

- x86-64 addresses in memory are 64-bit (8-byte) numbers.
- You should use `rel` to form valid relative addresses in memory.
- Initialized constants are defined in _section .rodata_.
- A constant must be declared `global` to be visible to other source files.

## 4. Combine colors

- x86-64 addresses in memory are 64-bit (8-byte) numbers.
- You should use `rel` to form valid relative addresses in memory.
- In order to access contents stored in an address in memory, you need to dereference it using `[]`.
- An external function or data must be declared `extern` in the corresponding section.
- An external function may modify any of the usual register you may be using, so you need to save variables in memory before calling it.
- `combining_function` takes the 32-bit value (not the address) for the base color in `rdi` and the 32-bit value (not the address) for the secondary color in `rsi`.
