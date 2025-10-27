# Hints

## General

- Most two or three-operand instructions require that all operands be of the same size.

## 1. Keep track of different currencies

- You can keep the relevant strings in section .rodata or section .data and dispatch them according to the enum's value.
- An enum is implicitly converted to an integer, usually of 32-bit size.

## 2. Check the exchange rate

- The value of each enum element is the index in the C array referenced by `value_in_US_dollars`.
- In C, indexes start at offset 0 and are for elements, regardless of their size in bytes, so for example index `2` always refers to the third element.
- Each `double` occupies 8 bytes in space.
- The exchange rate can be calculated by dividing the value in US dollars for the foreign currency by the value in US dollars for the domestic currency.

## 3. Calculate value of bills

- The value of bills can be calculated by multiplying `denomination` and `number_of_bills`.
- An `unsigned long long` is an unsigned 64-bit integer.
- An `unsigned short` is an unsigned 16-bit integer.
- An `uint64_t` is an unsigned 64-bit integer.

## 4. Calculate number of bills

- You need to round `amount` down before converting it to an integer.
- A `float` is a 32-bit floating-point number.
- You can use [roundss][round] with `1` as third operand to round down a 32-bit floating-point value.
- An `unsigned int` is an unsigned 32-bit integer.

## 5. Calculate value after exchange

- You need to convert `spread` to a floating-point value before dividing it by `100` to get a percentage.
- After getting the percentage, you should multiply it by `exchange_rate` to get the spread _fee_.
- The _actual rate_ is the sum of the exchange rate with the spread fee.
- You should divide the budget by the actual rate to get the maximum exchanged money.
- You can reuse the previously implemented `get_number_of_bills` function to get the number of bills you are going to use.
- A `uint32_t` is an unsigned 32-bit integer.

[round]: https://www.felixcloutier.com/x86/roundss
