## x86-64 Assembly Specific Notes

In the x86-64-assembly track, the randomness of the ability() function is checked by a [chi-squared test][chi-squared-test], at the level of [p][p-value] < 0.0001.

This means that if the ability score is being generated according to the instructions, there's less than a 0.01% chance of it producing a distribution of values that fails the test.

Notice that, according to the instructions, an ability score is the sum of the 3 largest out of 4 rolls of an unbiased d6 (six-sided die).

[chi-squared-test]: https://en.wikipedia.org/wiki/Pearson%27s_chi-squared_test
[p-value]: https://en.wikipedia.org/wiki/P-value
