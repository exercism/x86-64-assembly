# Instructions

In this exercise you are going to implement some rules of [Blackjack][blackjack],
such as the way the game is played and scored.

```exercism/note
In this exercise, the cards are represented by numbers; each number card is represented by its numerical value, while jacks, queens, kings, and aces are identified by 11, 12, 13, and 14, respectively (jokers are not used in the game).

In order to make it easier to work with this representation, some constants are defined at the top of the file; `C2` to `C10` are for number cards, `CJ` for a jack, `CQ` for a queen, `CK` for a king, and `CA` for an ace.

A [standard French-suited 52-card deck][standard_deck] is assumed, but in most versions, several decks are shuffled together for play.

[standard_deck]: https://en.wikipedia.org/wiki/Standard_52-card_deck
```

```exercism/note
These are the instructions mentioned in this concept:

| Instruction   | Description                                            |
|---------------|--------------------------------------------------------|
| cmp a, b      | sets flags according to a - b                          |
| jmp a         | code stops executing here and continues in label a     |
| jcc a         | code continues in label a if condition in `cc` is met  |

Those are the conditions checked in a `jcc` after a `cmp a, b`:

| Instruction | Jumps when          |
|-------------|---------------------|
| je          | a == b              |
| jl          | a < b (signed)      |
| jg          | a > b (signed)      |
| jb          | a < b (unsigned)    |
| ja          | a > b (unsigned)    |
| jle         | a <= b (signed)     |
| jge         | a >= b (unsigned)   |
| jbe         | a <= b (unsigned)   |
| jae         | a >= b (unsigned)   |
| jne         | a != b              |
| jnl         | !(a < b) (signed)   |
| jng         | !(a > b) (signed)   |
| jnb         | !(a < b) (unsigned) |
| jna         | !(a > b) (unsigned) |
| jnle        | !(a <= b) (signed)  |
| jnge        | !(a >= b) (signed)  |
| jnbe        | !(a <= b) (unsigned)|
| jnae        | !(a >= b) (unsigned)|
```

## 1. Calculate the value of a card

In **Blackjack**, the value of a `CA` is either 1 or 11, depending on the hand (more on this later).
Face cards (`CJ`, `CQ`, and `CK`) are scored at 10 points and any other card is worth its _numerical_ value.

Define the `value_of_card` function with parameter `card`, a number representing a card.
The function must return the _numerical value_ of the passed-in card.
Since a `CA` can take on multiple values (1 **or** 11), we fix the value of a `CA` at 1 for the time being.
Later on, you will implement a function to determine the value of a `CA`, given an existing hand.

```c
value_of_card(13)
// => 10

value_of_card(4)
// => 4

value_of_card(14)
// => 1
```

## 2. Determine which card has a higher value

Define the `higher_card` function having parameters `card_one` and `card_two`, two numbers each representing a card.
For scoring purposes, the values of a `CJ`, a `CQ`, and a `CK` are all 10.
The function must return which card has the higher value for scoring.
If both cards have an equal value, return both.

A `CA` can take on multiple values, so we will fix its value to 1 for this task.

```c
higher_card(13, 11)
// => {13, 11}

higher_card(4, 6)
// => 6

>>> higher_card(13, 14)
// => 13
```

````exercism/note
In order to return two integers from a function, you should use both `rax` and `rdx` registers:

```x86asm
returning_two_values:
    mov rax, rdi
    mov rdx, rsi
    ret
```

If only one card is returned, `rdx` must be set to 0.
````

## 3. Calculate the value of an ace

As mentioned earlier, a `CA` is worth _either_ 1 **or** 11 points, depending on the hand.
The rules of **Blackjack** require that the values of `CA`s be chosen to maximize the score of the hand but without going over 21 (going “bust”).

Define the `value_of_ace` function with parameters `card_one` and `card_two`, which are two numbers representing a pair of cards already in the hand _before_ receiving the last `CA`.
Your function must return which value, 1 or 11, will be assigned to the upcoming `CA`.
Remember: the value of the new hand (with the `CA`) needs to be as high as possible _without_ going over 21.

**Hint**: if we already have a `CA` in hand, then the value for the upcoming `CA` would be 1.

```c
value_of_ace(6, 13)
// => 1

value_of_ace(7, 3)
// => 11
```

## 4. Determine if the hand is a blackjack

If a player is dealt a `CA` and a ten-card (`C10`, `CJ`, `CQ`, or `CK`) as their first two cards, then the player has a score of 21.
This hand is known as a **blackjack**.

Define the `is_blackjack` function with parameters `card_one` and `card_two`, which are two numbers representing a pair of cards.
The function must return 1 if the two-card hand is a **blackjack**, 0 otherwise.
In order to make it easier to work with the values, the constants `TRUE` and `FALSE`, respectively equivalent to 1 and 0, are defined at the top of the file.

**Note** : The score _calculation_ can be done in many ways.
But if possible, we'd like you to check if there is a `CA` and a ten-card **_in_** the hand, as opposed to _summing_ the card values.

```c
is_blackjack(14, 13)
// => 1

is_blackjack(10, 9)
// => 0
```

## 5. Splitting pairs

If a player's first two cards are of the same value (e.g., the hand of two `C6`s, or the hand of a `CQ` and a `CK`), the player may choose to treat them as two separate hands.
This is known as "splitting pairs".

Define the `can_split_pairs` function with parameters `card_one` and `card_two`, which are two numbers representing a pair of cards.
The function must return 1 if the two-card hand can be split into two hands, 0 otherwise.
In order to make it easier to work with the values, the constants `TRUE` and `FALSE`, respectively equivalent to 1 and 0, are defined at the top of the file.

```c
can_split_pair(12, 13)
// => 1

can_split_pair(10, 14)
// => 0
```

## 6. Doubling down

When the original two cards dealt total 9, 10, or 11 points, a player can place an additional bet equal to their original bet.
This is known as "doubling down".

Define the `can_double_down` function with parameters `card_one` and `card_two`, which are two numbers representing a pair of cards.
The function must return 1 if the two-card hand allows the player to "double down", 0 otherwise.
In order to make it easier to work with the values, the constants `TRUE` and `FALSE`, respectively equivalent to 1 and 0, are defined at the top of the file.

```c
can_double_down(14, 9)
// => 1

can_double_down(10, 2)
// => 0
```

[blackjack]: https://bicyclecards.com/how-to-play/blackjack/
