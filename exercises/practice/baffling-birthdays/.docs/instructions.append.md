# Instructions append

## x86-64 Assembly Specific Notes

The function `random_birthdates()` should produce dates with the following properties:

1. The year should be valid.
   A valid year `y` is non-leap and so that `1600 <= y < 2129`.
2. The year is uniformly distributed across the full range of valid values.
3. The birthday is uniformly distributed across all 365 days of the year, so that each calendar day is equally likely.
   Note that this means months are _not_ equally likely: a 31-day month is more probable than a 30-day month and both are more probable than February.

Both the year and birthday distributions are checked by a [chi-squared test][chi-squared-test], at the level of [p][p-value] < 0.0001.

This means that if the dates are being generated according to the instructions, there's less than a 0.01% chance of it producing a distribution of values that fails the test.

[chi-squared-test]: https://en.wikipedia.org/wiki/Pearson%27s_chi-squared_test
[p-value]: https://en.wikipedia.org/wiki/P-value
