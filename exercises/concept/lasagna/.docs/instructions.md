# Instructions

In this exercise you're going to write some code to help you cook a brilliant lasagna from your favorite cooking book.

You have four tasks, all related to the time spent cooking the lasagna.

~~~~exercism/note
These are the instructions mentioned in this concept:

| Instruction | Description                                                        |
|-------------|--------------------------------------------------------------------|
| `mov`       | copies the contents from a source operand to a destination operand |
| `add`       | destination operand = destination operand + source operand         |
| `sub`       | destination operand = destination operand - source operand         |
| `imul`      | destination operand = destination operand * source operand         |
| `call`      | calls the function in its only operand                             |
| `ret`       | returns from a function                                            |
~~~~

## 1. Define the expected oven time in minutes

Define the `expected_minutes_in_oven` function that does not take any parameters and returns how many minutes the lasagna should be in the oven.
According to the cooking book, the expected oven time in minutes is 40:

```c
expected_minutes_in_oven();
// => 40
```

## 2. Calculate the remaining oven time in minutes

Define the `remaining_minutes_in_oven` function that takes the actual minutes the lasagna has been in the oven as a parameter and returns how many minutes the lasagna still has to remain in the oven, based on the expected oven time in minutes from the previous task.

```c
remaining_minutes_in_oven(30);
// => 10
```

## 3. Calculate the preparation time in minutes

Define the `preparation_time_in_minutes` function that takes the number of layers you added to the lasagna as a parameter and returns how many minutes you spent preparing the lasagna, assuming each layer takes you 2 minutes to prepare.

```c
preparation_time_in_minutes(2);
// => 4
```

## 4. Calculate the elapsed time in minutes

Define the `elapsed_time_in_minutes` function that takes two parameters, in this order:

1. The number of layers you added to the lasagna.
2. The number of minutes the lasagna has been in the oven.

The function should return how many minutes you've worked on cooking the lasagna.
This is the sum of the preparation time in minutes, and the time in minutes the lasagna has spent in the oven at the moment.

```c
elapsed_time_in_minutes(3, 20);
// => 26
```
