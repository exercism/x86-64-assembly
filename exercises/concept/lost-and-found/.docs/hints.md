# Hints

## General

- The first six integer arguments are passed to a function in `rdi`, `rsi`, `rdx`, `rcx`, `r8` and `r9`.
- Addresses in memory are 64-bit (8-byte) values.

## 1. Create an entry for each item

- All integer arguments after the sixth are passed in the stack, the first being in `rsp + 8`.
- The number of extra arguments is equal to the number of categories, which is passed in `r9`.
- You can loop to add the extra arguments one by one, or you can use [movsq][movs] combined with [rep][rep].

## 2. Reserve space for a monthly list of items

- You need to know the size of the array in order to clear its bytes after calling the allocating function.
- When you call an external function, it can modify the value in any _caller-saved register_.
- You can preserve the value of a register in the stack by using [push][push] or by manipulating `rsp` directly.
- Any modification to `rsp`, including with `push` must be reversed before the function returns, either with [pop][pop] or by changing `rsp` directly.

## 3. Insert an item in the monthly list

- A value that does not fit into a register is passed to a function on the stack.
- Each entry for an item occupies 120 bytes of space, which is much larger than the maximum size for a register (8 bytes).
- Arguments passed on the stack can be found in `rsp + 8`.
- You can loop to add the values to the destination memory location, or you can use [movsb][movs] combined with [rep][rep].

## 4. Print an item

- The introductory string is not mandatory, you can call the printing function with `0` instead.
- If passed, the introductory string must have at most 50 ASCII characters, already including a mandatory `\0` (NUL character, with value `0`) at the end.
- Whenever you call a function, you must reserve space on the stack for any argument after the sixth.
- The System V ABI states that the stack should be 16-byte aligned before calling a function, which is particularly important for external functions.
- Each entry for an item in the list occupies 120 bytes of space.

[movs]: https://www.felixcloutier.com/x86/movs:movsb:movsw:movsd:movsq
[rep]: https://www.felixcloutier.com/x86/rep:repe:repz:repne:repnz
[push]: https://www.felixcloutier.com/x86/push
[pop]: https://www.felixcloutier.com/x86/pop
