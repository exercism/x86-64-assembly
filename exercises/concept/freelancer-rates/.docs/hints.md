# Hints

## General

- A floating-point number is returned in `xmm0`.
- The first 8 floating-point arguments are passed in `xmm0` to `xmm7`.

## 1. Calculate the daily rate given an hourly rate

- A floating-point number is returned in `xmm0`.
- The first 8 floating-point arguments are passed in `xmm0` to `xmm7`.
- A 64-bit integer can be converted to a double-precision floating-point number by using `cvtsi2sd`.
- An immediate (a constant number) must be stored in a general-purpose register before it is converted to a floating-point number.
- Two double-precision floating-point numbers can be multiplied with `mulsd`.

## 2. Calculate a discounted price

- A floating-point number is returned in `xmm0`.
- The first 8 floating-point arguments are passed in `xmm0` to `xmm7`.
- Two double-precision floating-point numbers can be divided with `divsd`.
- A double-precision floating-point number can be subtracted from another with `subsd`.

## 3. Calculate the monthly rate, given an hourly rate and a discount

- A floating-point number is returned in `xmm0`.
- The first 8 floating-point arguments are passed in `xmm0` to `xmm7`.
- You can use `roundsd` to round a double-precision floating-point number, using a third operand to indicate the rounding mode.
- The number for a round up (ceiling) is `2`.
- You can use `cvtsd2si` to convert a double-precision floating-point number to a 64-bit integer.

## 4. Calculate the number of workdays given a budget, hourly rate, and discount

- A floating-point number is returned in `xmm0`.
- The first 8 floating-point arguments are passed in `xmm0` to `xmm7`.
- You can use `roundsd` to round a double-precision floating-point number, using a third operand to indicate the rounding mode.
- The number for a round down (floor) is `1`.
- You can use `cvtsd2ss` to convert a double-precision floating-point number to a single-precision floating-point number.
- You can use `cvtss2si` to convert a single-precision floating-point number to a 32-bit integer.
