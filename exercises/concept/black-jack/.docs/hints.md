# Hints

## General

- The instructions [cmp][cmp] and [test][test] are useful to set flags according to some tested conditions.
- The instructions [jmp][jmp] and [jcc][jcc] are useful to branch according to flags previously set.
- When you call a function, you need to preserve any necessary value in a register the called function uses.

## 1. Calculate the value of a card

- You can use `cmp` to compare two cards, setting the appropriate flags.
- You can use `je` or `jz` to branch if a number is equal to the other.
- You can use `jl` to branch if a number is lesser than the other.

## 2. Determine which card has a higher value

- Once you have defined the `value_of_card` function, you can call it from other functions.
- You can use `cmp` to compare two cards, setting the appropriate flags.
- You can use `jg` to branch is a number is greater than the other, and `jl` to branch if it is lesser.
- If both cards have the same value, the second one is returned in `rdx`. Otherwise, `rdx` should be set to 0.

## 3. Calculate the value of an ace

- Once you have defined the `value_of_card` function, you can call it from other functions.
- You can use `add` to sum two numbers.
- You can use `sub` to subtract the second number from the first.
- You can use `cmp` to compare two cards, setting the appropriate flags.
- You can use `jg` to branch is a number is greater than the other, and `jl` to branch if it is lesser.

## 4. Determine blackjack

- You can use `cmp` to compare two cards, setting the appropriate flags.
- You can use `je` or `jz` to branch if a number is equal to the other.
- You can reuse the already implemented `value_of_card` function.

## 5. Splitting pairs

- You can use `cmp` to compare two cards, setting the appropriate flags.
- You can use `je` or `jz` to branch if a number is equal to the other.
- You can reuse the already implemented `value_of_card` function.
- You can handle the ace case (when at least one of the cards is an ace) separately.

## 6. Doubling down

- An ace can always be scored at either 1 or 11.
- You can reuse the already implemented `value_of_card` function.

[cmp]: https://www.felixcloutier.com/x86/cmp
[jmp]: https://www.felixcloutier.com/x86/jmp
[test]: https://www.felixcloutier.com/x86/test
[jcc]: https://www.felixcloutier.com/x86/jcc
