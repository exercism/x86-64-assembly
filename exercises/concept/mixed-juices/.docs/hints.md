# Hints

## General

- A loop in x86-64 is achieved by jumping to a previous label.
- A loop may be exited by jumping to a label outside of it.
- In order to access contents stored in an address in memory, you need to dereference it using `[]`.
- The prefix to access 4-byte values in memory is `dword`.
- An array is represented by its address, which is a 8-byte value in x86-64.

## 1. Determine how long it takes to make a juice

- You can use `cmp` to check for conditions and `jcc` to branch according to some condition tested.

## 2. Determine how long it takes to make all ordered juices

- You need to check if you have reached the end of the array, otherwise you might end up getting an error.
- You can use `add` to add a value in the source operand to the destination operand.
- You can use `dec` to reduce the value in the destination operand by 1.
- You can reuse the already implemented `time_to_make_juice` function.

## 3. Replenish the lime wedge supply

- You need to keep track of two things, how many limes were already cut and how many wedges are still missing.
- It's possible that you don't need any wedge since the start or that the input array is empty, so you need to check for an exit condition before executing any iteration of the loop.
- You can use `sub` to subtract the value in a destination operand by the value in a source operand.
- You can use `inc` to add 1 to the value in a destination operand.

## 4. Finish up the shift

- The time left in the shift won't start as 0, so it is safe to execute at least one iteration of the loop before checking for an exit condition.
- You can reuse the already implemented `time_to_make_juice` function.
