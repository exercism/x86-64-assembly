# Hints

## General

- The `cmovcc` family of instructions do not take immediates.
  You must load any constant number into a register before using them.
- The `setcc` family of instructions work only with 8-bit operands.
  It is often necessary to sign or zero extend them after setting the appropriate value.

## 1. Add a bonus without overflowing the display

- The cap value is `999999`.
  Any sum greater than this becomes `999999` instead.
- A comparison followed by a `cmovcc` can replace a value with another when a condition holds.
- The `cmovcc` family of instructions do not take immediates.
  You must load any constant number into a register before using them.

## 2. Compare two scores

- A single comparison can be followed by more than one `setcc` or `cmovcc` to set or move multiple values, according to the same or different flags.
- The `setcc` family of instructions work only with 8-bit operands.
- A signed 8-bit operand can be sign-extended to 64 bits with `movsx`.

## 3. Validate a raw score

- A single comparison can be followed by more than one `setcc` or `cmovcc` to set or move multiple values, according to the same or different flags.
- The conditional suffix for signed comparison is `l`, for lesser, and `g`, for greater.

## 4. Track the two highest scores

- There are two top values.
  A new candidate should be compared with both.
- A single comparison can be followed by more than one `setcc` or `cmovcc` to set or move multiple values, according to the same or different flags.
- The conditional suffix for signed comparison is `l`, for lesser, and `g`, for greater.
