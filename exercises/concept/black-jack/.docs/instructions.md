# Instructions

In this exercise you are going to implement some rules of [Blackjack][blackjack],
such as the way the game is played and scored.

~~~~exercism/note
In this exercise, the cards are represented as numbers, such that each number card is represented as its numerical value, jack is 11, queen is 12, king is 13 and ace is 14.
Jokers are discarded.

In order to make it easier to work with this representation, constants are defined at the top of the file, such that C2 to C10 is a number card, CJ is jack, CQ is queen, CK is king and CA is ace.

A [standard French-suited 52-card deck][standard_deck] is assumed, but in most versions, several decks are shuffled together for play.
~~~~

## 1. Calculate the value of a card

In Blackjack, it is up to each individual player if an ace is worth 1 or 11 points (_more on that later_).
Face cards (joker, queen and king) are scored at 10 points and any other card is worth its "pip" (_numerical_) value.

Define the `value_of_card` function with parameter `card`, a number representing a card.
The function should return the _numerical value_ of the passed-in card.
Since an ace can take on multiple values (1 **or** 11), this function should fix the value of an ace card at 1 for the time being.
Later on, you will implement a function to determine the value of an ace card, given an existing hand.

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
For scoring purposes, the value of jack, queen and king is 10.
The function should return which card has the higher value for scoring.
If both cards have an equal value, return both.

An ace can take on multiple values, so we will fix its value to 1 for this task.

```c
higher_card(13, 11)
// => {13, 11}

higher_card(4, 6)
// => 6

>>> higher_card(13, 14)
// => 13
```

~~~~exercism/note
In order to return two integers from a function, you should use both `rax` and `rdx` registers:

```nasm
returning_two_values:
    mov rax, rdi
    mov rdx, rsi
    ret
```

If only one card is returned, `rdx` must be set to 0.
~~~~

## 3. Calculate the value of an ace

As mentioned before, an ace can be worth _either_ 1 **or** 11 points.
Players try to get as close as possible to a score of 21, without going _over_ 21 (_going "bust"_).

Define the `value_of_ace` function with parameters `card_one` and `card_two`, which are two numbers representing a pair of cards already in the hand _before_ getting an ace card.
Your function will have to decide if the upcoming ace will get a value of 1 or a value of 11, and return that value.
Remember: the value of the hand with the ace needs to be as high as possible _without_ going over 21.

**Hint**: if we already have an ace in hand, then the value for the upcoming ace would be 1.

```c
value_of_ace(6, 13)
// => 1

value_of_ace(7, 3)
// => 11
```

## 4. Determine a "Natural" or "Blackjack" Hand

If a player is dealt an ace and a ten-card (10, jack, queen or king) as their first two cards, then the player has a score of 21.
This is known as a **blackjack** hand.

Define the `is_blackjack` function with parameters `card_one` and `card_two`, which are two numbers representing a pair of cards.
Determine if the two-card hand is a **blackjack**, and return 1 if it is, 0 otherwise.
In order to make it easier to work with the values, the constants `TRUE` and `FALSE`, equivalent to 1 and 0 respectively, are defined at the top of the file.

**Note** : The score _calculation_ can be done in many ways.
But if possible, we'd like you to check if there is an ace and a ten-card **_in_** the hand, as opposed to _summing_ the hand values.

```c
is_blackjack(14, 13)
// => 1

is_blackjack(10, 9)
// => 0
```

## 5. Splitting pairs

If the players first two cards are of the same value, such as two sixes, or a queen and a king, a player may choose to treat them as two separate hands.
This is known as "splitting pairs".

Define the `can_split_pairs` function with parameters `card_one` and `card_two`, which are two numbers representing a pair of cards.
Determine if this two-card hand can be split into two pairs.
If the hand can be split, return 1, otherwise, return 0.
In order to make it easier to work with the values, the constants `TRUE` and `FALSE`, equivalent to 1 and 0 respectively, are defined at the top of the file.

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
Determine if the two-card hand can be "doubled down", and return 1 if it can, 0 otherwise.
In order to make it easier to work with the values, the constants `TRUE` and `FALSE`, equivalent to 1 and 0 respectively, are defined at the top of the file.

```c
can_double_down(14, 9)
// => 1

can_double_down(10, 2)
// => 0
```

[blackjack]: https://bicyclecards.com/how-to-play/blackjack/
[standard_deck]: https://en.wikipedia.org/wiki/Standard_52-card_deck
