# Instructions

Piper is an avid pie baker.

No one knows if she picked pie baking because of her name, or if she changed her name to match her hobby.
At a glance, the latter doesn't seem very likely, but you see, Piper is absolutely fascinated by pies.
She's always tinkering in the kitchen, tweaking her recipes, improving her craft, to the absolute delight of her friends.
Nothing escapes her attention to detail, not the temperature of her oven, not the weight of each ball of dough, and certainly not the shape of the pie itself.

Her latest interest?
Baking pies as circular as possible, to the point of mathematical perfection, with the help of her favorite number, you guessed it: π.

Piper found a delightful formula to calculate π iteratively, the Newton/Euler Convergence Transformation:

```c
π / 2 = sum for k from 0 to infinity of ( k! ) / ( 2 * k + 1 )!!
```

Help Piper get her kitchen in order, and bake her mathematically perfect pie.

## 1. Portion the dough

Piper rolled out two batches of dough this morning, with different weights (in `g`).
To keep her pies uniform, she wants to portion both batches into balls of the same weight.
And of course she wants the portions as large as possible to waste as little dough as possible!

The largest weight that divides both batches evenly is their **greatest common divisor**.
The Euclidean algorithm computes it recursively:

- `gcd(a, 0) = a` (base case)
- `gcd(a, b) = gcd(b, a mod b)`

Note that the recursive call sits in tail position: nothing happens after it.
Define `largest_portion` so that the recursive step is a `jmp` to the function itself, not a `call`.

```c
largest_portion(252, 105);
// => 21
```

Both arguments are 64-bit non-negative integers.
The return value is a 64-bit non-negative integer.

## 2. Double Factorial

You already know how to write the ordinary factorial in a tail recursive way from the concept.
The same function is in your stub file.

However, the Newton/Euler formula also uses **double factorials**, written `!!`.
The double factorial operator is defined as:

```c
0!! = 1
n!! = 1 * 3 * 5 * ... * n // if n is odd
n!! = 2 * 4 * 6 * ... * n // if n is even
```

Note that the double factorial follows the same pattern as the factorial, except it decrements by 2 at each step instead of 1.
Define the `double_factorial` function which will compute the double factorial in a tail recursive manner.

```c
double_factorial(5);
// => 15
double_factorial(6);
// => 48
```

The argument is a 32-bit unsigned integer.
The return value is a 64-bit unsigned integer.

## 3. Newton/Euler Convergence Transformation

Now Piper has every tool she needs.
Define the `pipers_pi` function, which approximates π using a set number of terms from the Newton/Euler Convergence Transformation formula:

```c
π / 2 = sum for k from 0 to infinity of ( k! ) / ( 2 * k + 1 )!!
```

The numerator uses the ordinary factorial.
You can call the `factorial` function already defined for you!
The denominator uses the `double_factorial` you wrote in task 2.

Let's compute the first term together.
For an upper limit of `0` (instead of infinity), we get:

```c
π / 2 ≈ sum for k from 0 to 0 of ( k! ) / ( 2 * k + 1 )!!
π / 2 ≈ (0!) / ( 2 * 0 + 1 )!!
π / 2 ≈ 0! / 1!!
π / 2 ≈ 1 / 1
π / 2 ≈ 1.0
π ≈ 2.0
```

For an upper limit of `2`, we get instead:

```c
π / 2 ≈ sum for k from 0 to 2 of ( k! ) / ( 2 * k + 1 )!!
π / 2 ≈ ((0!) / ( 2 * 0 + 1 )!!) + ((1!) / ( 2 * 1 + 1 )!!) + ((2!) / ( 2 * 2 + 1 )!!)
π / 2 ≈ 1 + (1! / 3!!) + (2! / 5!!)
π / 2 ≈ 1 + (1 / 3) + (2 / 15)
π / 2 ≈ 1.4666666
π ≈ 2.9333333
```

Each extra term will improve the approximation.

```c
pipers_pi(0);
// => 2.0
pipers_pi(1);
// => 2.6666666
pipers_pi(2);
// => 2.9333333
```

The argument is a 32-bit non-negative integer.
The return value is a 64-bit floating point number.
