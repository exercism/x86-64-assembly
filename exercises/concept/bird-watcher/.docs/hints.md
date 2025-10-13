# Hints

## General

- An effective address may be computed with the [lea][lea] instruction.
- You should use `rel` to form valid relative addresses in memory.
- The prefix to access 8-byte values in memory is `qword`.

## 1. Check what the counts were last week

- In order to access contents stored in an address in memory, you need to dereference it using `[]`.

## 2. Check what are the current counts for this week

- Uninitialized variables are defined in _section .bss_.
- You should use both `rax` and `rdx` to return two integers from a function.

## 3. Save count for each day

- The prefix to access 1-byte values in memory is `byte`.
- You can insert or retrieve bytes in bulk using the prefix for a greater data size when accessing memory.
- You can check for conditions using [cmp][cmp].
- You can conditionally branch using [jcc][jcc].
- You can use [inc][inc] to add 1 to a destination operand's value.

## 4. Check how many birds visited today

- 1-byte integer values are returned in `al`.
- You can use [dec][dec] to subtract 1 from a destination operand's value.

## 5. Update today's count

- You can use [add][add] with a destination memory operand.

## 6. Insert new entries in bulk

- You can insert or retrieve bytes in bulk using the prefix for a greater data size when accessing memory.

[lea]: https://www.felixcloutier.com/x86/lea
[cmp]: https://www.felixcloutier.com/x86/cmp
[jcc]: https://www.felixcloutier.com/x86/jcc
[inc]: https://www.felixcloutier.com/x86/inc
[dec]: https://www.felixcloutier.com/x86/dec
[add]: https://www.felixcloutier.com/x86/add
