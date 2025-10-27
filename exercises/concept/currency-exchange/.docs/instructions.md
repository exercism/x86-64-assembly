# Instructions

Your friend Chandler plans to visit exotic countries all around the world.
Sadly, Chandler's math skills aren't good.
He's pretty worried about being scammed by currency exchanges during his trip - and he wants you to make a currency calculator for him.

Here are his specifications for the app.

~~~~exercism/note
The functions in this exercise are declared in a C source file with the provided signatures.
Your x86-64-assembly code must follow those specifications.
~~~~

## 1. Keep track of different currencies

You have created a `enum currency_t` to keep track of different currencies Chandler uses in his travels:

```c
enum currency_t {
    GBP,
    EUR,
    JPY,
    AUD,
    BRL,
    CNY,
    CAD,
    INR
};
```

You sometimes need to print those currencies on the screen so you can check if they are right.

Create the `stringify_currency` function:

```c
void stringify_currency(char *buffer, enum currency_t currency);
```

This function has no return value and should store a C-style string in the location indicated by `buffer`.
The string should visually represent which kind of currency was passed to the function:

```c
char buffer[4];
stringify_currency(buffer, CAD);
// => "CAD"
```

## 2. Check the exchange rate

Create the `exchange_rate` function:

```c
double exchange_rate(enum currency_t domestic_currency, enum currency_t foreign_currency, const double *value_in_US_dollars);
```

The `domestic_currency` argument represents Chandler's local currency to be exchanged for a `foreign_currency`.

`value_in_US_dollars` is a pointer to an array of `double` that contains the value of one unit of each currency in US dollars.
Currencies are indexes in this array.
So, if `EUR` is a valid element for `enum currency_t`, then `value_in_US_dollars[EUR]` yields the value of `1 EUR` in US dollars.

This function should return the value of one unit of foreign currency in the domestic currency.

```c
const double value_in_US_dollars[8] = {
    1.33329, 1.16443, 0.00654374, 0.650888,
    0.185577, 0.140420, 0.714142, 0.0113863
};

exchange_rate(JPY, GBP, value_in_US_dollars);
// => 203.750454633
```

## 3. Calculate value of bills

Create the `get_value_of_bills` function:

```c
uint64_t get_value_of_bills(unsigned long long denomination, unsigned short number_of_bills);
```

The argument `denomination` is the value of a single bill, whereas `number_of_bills` is the total number of bills.

This exchanging booth only deals in cash of certain increments.
The total you receive must be divisible by the value of one "bill" or unit, which can leave behind a fraction or remainder.
Your function should return only the total value of the bills (_excluding fractional amounts_) the booth would give back.
Unfortunately, the booth gets to keep the remainder/change as an added bonus.

```c
get_value_of_bills(5, 128);
// => 640
```

## 4. Calculate number of bills

Create the `get_number_of_bills` function:

```c
unsigned int get_number_of_bills(float amount, unsigned long long denomination);
```

This function should return the _number of currency bills_ that you can receive within the given _amount_.
In other words:  How many _whole bills_ of currency fit into the starting amount?
Remember -- you can only receive _whole bills_, not fractions of bills, so remember to divide accordingly.
Effectively, you are rounding _down_ to the nearest whole bill/denomination.

```c
get_number_of_bills(127.5, 5);
// => 25
```

## 5. Calculate value after exchange

Create the `exchangeable_value` function:

```c
uint32_t exchangeable_value(float budget, double exchange_rate, uint8_t spread, unsigned long long denomination);
```

Parameter `spread` is the _percentage taken_ as an exchange fee, written as an integer.
It needs to be converted to decimal by dividing it by 100.
Note that the spread is added to the exchange rate, so that a spread of `10` results in a exchange rate 10% higher.

This function should return the maximum value of the new currency after calculating the *exchange rate* adjusted by the *spread*.
Remember that the currency *denomination* is a whole number, and cannot be sub-divided.

```c
exchangeable_value(127.25, 0,873350884, 10, 20);
// => 120
exchangeable_value(127.25, 0,873350884, 10, 5);
// => 130
```
