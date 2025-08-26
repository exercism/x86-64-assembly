## x86-64 Assembly Specific Notes

In the x86-64-assembly track, the randomness of the ability() function is checked by a [Chi-squared test](https://en.wikipedia.org/wiki/Pearson%27s_chi-squared_test), considering a [p value](https://en.wikipedia.org/wiki/P-value) of 0.001.

This means that there's a 0.001% chance that a truly random ability score, calculated according to the instructions, fails the test.

Notice that, according to the instructions, an ability score is the sum of the 3 largest out of 4 rolls of an unbiased d6 (six-sided die).
