# Instructions

A local store is moving its inventory to a larger warehouse.
You were hired to pack and move everything.

You have four tasks, all related to managing the transport.

~~~~exercism/note
These are the instructions mentioned in this concept:

| Instruction   | Description                                                          |
|---------------|----------------------------------------------------------------------|
| add a, b      | sets a to a + b                                                      |
| adc a, b      | sets a to a + b + CF (previous carry)                                |
| inc a         | sets a to a + 1                                                      |
| sub a, b      | sets a to a - b                                                      |
| dec a         | sets a to a - 1                                                      |
| imul a        | sets rax to a * rax (signed)                                         |
| imul a, b     | sets a to a * b                                                      |
| imul a, b, c  | sets a to b * c                                                      |
| mul a         | sets rax to a * rax (unsigned)                                       |
| div a         | sets rax to rax / a and rdx to rax % a (unsigned)                    |
| idiv a        | sets rax to rax / a and rdx to rax % a (signed)                      |
| movzx a, b    | copies a to b, adding 0 to exceding bits                             |
| movsx a, b    | copies a to b, adding 1 to exceding bits if num b < 0 or 0 otherwise |
~~~~

~~~~exercism/note
Remember that you can access the same register with different sizes by changing the name of the operand.
For example: `rax` (64-bit), `eax` (32-bit), `ax` (16-bit), `al` (8-bit).

You can refer to the [previous concept][basics] for the full table.

[basics]: https://exercism.org/tracks/x86-64-assembly/concepts/basics
~~~~

## 1. Get weight of each box

Items are being packed in boxes that must be labeled with their weight.
There is no scale around, but luckily you know how much each item weighs on average.

In order to better organize things, a box holds only items of two different products.

Define a function `get_box_weight` that returns the total weight of a box, in `g`.
This function takes as parameters, in this order:

- The number of items for the first product in the box
- The weight of each item of the first product, in `g`
- The number of items for the second product in the box
- The weight of each item of the second product, in `g`

Consider that an empty box weighs **500 g**.
A constant `WEIGHT_OF_EMPTY_BOX` is defined at the top of the file.

Example:

```c
get_box_weight(30, 40, 50, 20);
// => 2700
```

All arguments are 16-bit non-negative integers, and the return value is a 32-bit non-negative integer.

## 2. Calculate how many boxes fit into the truck

Boxes are being stacked and moved to the new warehouse in a truck.
However, there is only so much vertical space in the truck.

Define a function `max_number_of_boxes` that returns how many boxes of a certain height can be stacked vertically (one on top of another) within the truck.

This function takes as parameter the height of the box, in `cm`.
Consider that the truck interior height is **300 cm**.
A constant TRUCK_HEIGHT is defined at the top of the file.

Example:

```c
max_number_of_boxes(30);
// => 10
```

The argument and the return value are 8-bit non-negative integers.

## 3. Check if all products are accounted for

There is a checklist in the new warehouse with the number of items still unaccounted for each product.
For each new box moved there, you need to calculate the new value in the checklist for each product in the box.

Define a function `items_to_be_moved` that returns how many items remain to be moved to the new warehouse for a given product.
This function takes as parameters, in this order:

- The number of items still unaccounted for a product
- The number of items for the product in a box

Example:

```c
items_to_be_moved(76532, 120);
// => 76412
```

The arguments are 32-bit non-negative integers.
The return value is a 32-bit integer.
In case of an error in the process, it is possible that the result is a negative number.

## 4. Get payment

Your payment is based on how many boxes were moved and how many truck trips were necessary.
For each box, you will be paid **5 dollars** and for each trip, you will be paid **220 dollars**.
You may have received part of this payment up front to cover initial costs.

However, some products are not covered by insurance and your payment will be reduced by the value of any of those items broken or missing.
It is possible that you end up owing money if you are not careful!

This payment, or debt, will be divided equally between you and a number of workers you hired.
Any remaining money, or debt, is yours.

Define a function `calculate_payment` that returns how much you should be paid, or pay, at the end.
This function takes as parameters, in this order:

- How much you have received up front, as a 64-bit non-negative integer
- The total number of boxes moved, as a 32-bit non-negative integer
- The number of truck trips made, as a 32-bit non-negative integer
- The number of broken or missing items, as a 32-bit non-negative integer
- The value of each lost item, as a 64-bit non-negative integer
- The number of workers to split the payment or debt with you, as a 8-bit positive integer

Example:

```c
calculate_payment(2000, 1000, 5, 21, 2, 1);
// => 2029
```

The return value is a 64-bit integer.
