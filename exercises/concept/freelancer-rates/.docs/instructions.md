# Instructions

In this exercise, you'll be writing code to help a freelancer communicate with a project manager.
Your task is to provide a few utilities to quickly calculate daily and monthly rates, optionally with a given discount.

We first establish a few rules between the freelancer and the project manager:

- The daily rate is 8 times the hourly rate.
- A month has 22 billable days.

Sometimes, the freelancer is offering to apply a discount on their daily rate (for example for their most loyal customers or not-for-profit customers).

Discounts are modeled as fractional numbers representing percentages, for example, `25.0` (25%).

## 1. Calculate the daily rate given an hourly rate

Implement a function called `daily_rate` to calculate the daily rate given as parameter an hourly rate, as a 64-bit floating-point number.
The contract defines that a day has 8 billable hours.

```c
daily_rate(60)
// => 480.0
```

The returned daily rate should be a 64-bit floating-point number.

## 2. Calculate a discounted price

Implement a function `apply_discount` to calculate the price after a discount.
It should accept two parameters: the original price and the discount rate in percent, both as a 64-bit floating-point number.

```c
apply_discount(150.0, 10.0)
// => 135.0
```

The returned value should always be a 64-bit floating-point number.

## 3. Calculate the monthly rate, given an hourly rate and a discount

Implement a `monthly_rate` function to calculate the discounted monthly rate.
It takes two parameters, an hourly rate and the discount in percent, both as a 64-bit floating-point number.

```c
monthly_rate(77.0, 10.5)
// => 12130
```

The returned monthly rate should be rounded up (take the ceiling) to the nearest 64-bit integer.

## 4. Calculate the number of complete workdays given a budget, hourly rate, and discount

Implement a function `days_in_budget` that takes as parameters:

1. A budget, as a 64-bit unsigned integer.
2. An hourly rate, as a 64-bit floating-point number.
3. A discount in percent, as a 64-bit floating-point number.

This function should return the number of complete days of work the budget covers.

```c
days_in_budget(20000, 80, 11.0)
// => 35
```

The returned number of days should be rounded down (take the floor) to the nearest 32-bit integer.
