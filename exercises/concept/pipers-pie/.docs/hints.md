# Hints

## General

- A tail call in x86-64 is a `jmp` to another function
- For functions that aren't naturally tail recursive, you may define a helper that takes an accumulator as an extra argument and tail-calls itself

## 1. Portion the dough

- The Euclidean algorithm is already in tail form
- The base case is `rsi == 0`
- To compute `a mod b`, you may use [div][integers-concept]

## 2. Double Factorial

- Both `0!!` and `1!!` are `1`
- In a double factorial, `n` decreases by 2 each step
- The accumulator starts at `1`

## 3. Newton/Euler Convergence Transformation

- Your tail-recursive helper can take as many extra arguments as you need to keep running values
- You may reference [a previous concept][floats-concept] for instructions to operate on 64-bit floating-point numbers
- Multiply the final sum by `2` since the formula gives `π/2`

[integers-concept]: https://exercism.org/tracks/x86-64-assembly/concepts/integers
[floats-concept]: https://exercism.org/tracks/x86-64-assembly/concepts/floating-point-numbers
