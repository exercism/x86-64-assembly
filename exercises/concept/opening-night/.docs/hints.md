# Hints

## General

- The tests call your functions from several threads at the same time.
  You should use atomic instructions to ensure no update is lost.
- The `lock` prefix makes a read-modify-write instruction atomic.
  `xchg` with a memory operand is always atomic, not needing a prefix.
- The shared values are all 64-bit.

## 1. Count the admissions

- The group size should be added to the tally.
- You can use the `lock` prefix to make some instructions atomic.

## 2. Change the reel

- The `xchg` instruction may be used to swap two operands.
  It is automatically atomic when used with a memory operand.
- The function returns the identifier of the previously mounted reel.

## 3. Sell a ticket

- The `xadd` instruction adds the source operand to the destination operation, while returning the old value, before the update.
  You need to atomically add one to the current count, and return the updated value, not the old value.
- You can use the `lock` prefix to make some instructions atomic.
- A value may change between two instructions, even if they are atomic.
  Reading the counter and writing to it should be done on the same atomic instruction.
- The value returned is the count _after_ it is incremented.

## 4. Fill the premiere

- If the count already reached maximum capacity, it must not be updated and the function should return `0`.
- If the count didn't reach maximum capacity yet, it should be incremented by `1` and this new count should be returned.
- `cmpxchg` may be used to ensure the count still has the value it had on a previous read, and only then update it.
  This instruction compares its first operand with `rax`.
  If the first operand is equal to `rax`, its value is replaced by the second operand and `ZF` is set.
  Otherwise, its value is stored in `rax` and `ZF` is cleared.

## 5. Mind the booth

- The function has three parts in sequence: claim the booth, run the task, reopen the booth.
- Claiming the booth is a test-and-set.
  The same instruction should get the old value of the flag and also set it to `1`.
  An old value of `0` means the booth was free and is now yours, while a `1` means someone else is inside.
- A value may change between two instructions, even if they are atomic.
  Reading the flag and writing to it should be done on the same atomic instruction.
- When the booth is held, execute `pause` and then try the swap again.
- When the booth is free, you should run the task.
- The task is an external function.
  The stack should be 16-byte aligned before calling it, and any caller-saved register may be clobbered by it.
  You will need the flag memory location after running the task, so save this value into somewhere safe.
- After running the task, the booth should be reopened by storing `0` into the flag.
