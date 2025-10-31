# Hints

## General

- A struct's alignment is the _maximum_ alignment of any of its fields.
- The size of a struct is a multiple of its alignment.

## 1. Create a remote controlled car

- A struct's alignment is the _maximum_ alignment of any of its fields.
- The size of a struct is a multiple of its alignment.
- The alignment of an array is equal to the alignment of its elements.
- Each 8-byte of a struct should be classified separately.
- If an integer and a floating-point value share the same 8-byte, the entire 8-byte is passed in a General-Purpose Register (GPR).
- A floating-point value can not be an assembler-time constant defined with `equ`, but it can be a section .rodata constant.
- To move raw bytes from a `xmm` register to a GPR, without changing bit representation, the instructions [movd][mov] or [movq][mov] can be used.

## 2. Create new track

- A struct's alignment is the _maximum_ alignment of any of its fields.
- The size of a struct is a multiple of its alignment.
- If adjacent field in a struct can not be grouped to fit into its alignment, padding bytes are inserted.

## 3. Create a racing event

- A struct's alignment is the _maximum_ alignment of any of its fields.
- The size of a struct is a multiple of its alignment.
- A struct with up to 16 bytes is passed in registers to a function.
- A struct with more than 16 bytes is usually placed in memory.
- When a function returns a struct in memory, the address of a memory location to store this struct is passed as an implicit first argument, in `rdi`.
- In this case, the function should return this address in `rax`.

## 4. Confirm a car to the race

- A struct's alignment is the _maximum_ alignment of any of its fields.
- The size of a struct is a multiple of its alignment.
- A pointer occupies 8 bytes and is passed in a General-Purpose Register (GPR), regardless of the size of the type it points to.
- Both the `cars` array and the number of running cars must be updated in `race`.

## 5. Create a tournament

- A struct's alignment is the _maximum_ alignment of any of its fields.
- The size of a struct is a multiple of its alignment.
- A struct with more than 16 bytes is usually placed in memory.
- When a function takes as argument a struct in memory, this struct is passed on the stack.
- Both the `races` array and the number of races must be updated in `tournament`.

[mov]: https://www.felixcloutier.com/x86/movd:movq
