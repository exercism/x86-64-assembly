# Hints

## General

- Functions are just memory addresses, and they can be manipulated as any memory address.
- Memory addresses are 64-bit integer values, passed and returned in the usual registers.
- It is possible to `call` or `jmp` to a function stored in a register or in memory.

## 1. Remember a transaction

- Functions are just memory addresses, and they can be manipulated as any memory address.
- Memory addresses are 64-bit integer values, passed and returned in the usual registers.
- `remember_transaction` should store a function in a persistent memory location.
- In `apply_remembered`, the argument to be passed to the saved function is already stored in the right register (`rdi`).

## 2. The bank's manual

- The dispatch table is just an array and can be indexed as any array.
- Each entry in the dispatch table is a function and functions are 64-bit (8-byte) integer values.
- In `select_transaction`, the argument to the transaction is originally in `rdx` and needs to be moved to `rdi` before calling the function.
- The call to the dispatched transaction is in tail position, so you may use a tail call (`jmp`).

## 3. Process a monthly statement

- Each entry in the array is a function and functions are 64-bit (8-byte) integer values.
- Any caller-saved register may be clobbered by an external function, so you should save any necessary value before calling such a function.
  The caller-saved registers are `rax`, `rcx`, `rdx`, `rdi`, `rsi`, `r8`, `r9`, `r10` and `r11`.
- Callee-saved registers, such as `rbx`, `rbp`, `r12`, `r13`, `r14` and `r15` are not modified by a called function.
  However, you need to save their original value before using them, and restore that value before returning.
- The stack should be 16-byte aligned before calling an external function.
  At point of entry, `rsp` is 8 less than a multiple of 16.
- For an empty array, no transaction is applied and the function should return the starting balance unchanged.

## 4. Process with a guard

- Each entry in the array is a function and functions are 64-bit (8-byte) integer values.
- Any caller-saved register may be clobbered by an external function, so you should save any necessary value before calling such a function.
- Callee-saved registers, such as `rbx`, `rbp`, `r12`, `r13`, `r14` and `r15` are not modified by a called function.
  However, you need to save their original value before using them, and restore that value before returning.
- The stack should be 16-byte aligned before calling an external function.
  At point of entry, `rsp` is 8 less than a multiple of 16.
- The guard function takes as argument the result of each transaction.
  This value must be in `rdi` before calling the guard function.
- The guard function returns `0` for an invalid result, and non-zero for a valid one.
  A valid result updates the running balance and the number of approved transactions.
- The function returns two 64-bit non-negative integers: the final balance should be in `rax` and the number of approved transactions should be in `rdx`.
