# Hints

## General

- A floating-point number is returned in `xmm0`.
- The first 8 floating-point arguments are passed in `xmm0` to `xmm7`.

## 1. Calculate the daily rate given an hourly rate

- An integer can be converted to a floating-point number by using `cvtsi2yy`, where `yy` corresponds to the desired precision.
- An integer is converted to a floating-point of the same size (32-bit or 64-bit).
- For single-precision floating-point numbers, the suffix is `ss`.
- An immediate (a constant number) must be stored in a general-purpose register before it is converted to a floating-point number.
- Two single-precision floating-point numbers can be multiplied with `mulss`.

## 2. Calculate a discounted price

- For double-precision floating-point numbers, the suffix is `sd`.
- Two double-precision floating-point numbers can be divided with `divsd`.
- A double-precision floating-point number can be subtracted from another with `subsd`.

## 3. Calculate the monthly rate, given an hourly rate and a discount

- You can use `roundsd` and `roundss` to round a floating-point number, using a third operand to indicate the rounding mode.
- The number for a round up (ceiling) is `2`.
- You can use `cvtxx2si` to convert a floating-point number to an integer, where `xx` is either `ss` or `sd`.
- A floating-point number is converted to an integer of the same size (32-bit or 64-bit).

## 4. Calculate the number of workdays given a budget, hourly rate, and discount

- You can use `cvtsd2ss` or `cvtss2sd` to convert a floating-point number from one precision format to the other.
- You can use `roundsd` and `roundss` to round a floating-point number, using a third operand to indicate the rounding mode.
- The number for a round down (floor) is `1`.
