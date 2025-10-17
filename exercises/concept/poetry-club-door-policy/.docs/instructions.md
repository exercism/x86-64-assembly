# Instructions

A new poetry club has opened in town, and you're thinking of attending.
Because there have been incidents in the past, the club has a very specific door policy which you'll need to master, before attempting entry.

There are two doors at the poetry club, a front and a back door, and both are guarded.
To gain entry, you'll need to work out the password of the day.

The password is always based on a poem and can be derived in a two-step process.

1. The guard will recite the poem, one line at a time and you have to respond with an appropriate letter of that line.
2. The guard will now tell you all the letters you responded with at once, and you need to write them down on a piece of paper in a specific format.

The details of the process depend on which door you are trying to enter.

~~~~exercism/note
All strings in this exercise will be ASCII-encoded and NUL-terminated.
This means all characters use ASCII encoding and every string ends when the '\0' (the NUL character, with value `0`) is found.
~~~~

## 1. Get the first letter of a sentence

To determine the letters for the front door password, you need to respond with the first letter of the line of the poem, that the guard recites to you.

To end up with a nice password, the members of the poetry club like to use _acrostic_ poems.
This means that the first letter of each sentence forms a word.
Here is an example by one of their favorite writers Michael Lockwood.

```text
Stands so high
Huge hooves too
Impatiently waits for
Reins and harness
Eager to leave
```

So when the guard recites **Stands so high**, you'll respond **S**, when the guard recites **Huge hooves too**, you'll respond **H**.

Implement the function `front_door_response` that takes the address in memory for a line of the poem as an argument and returns the first letter of that line.
This letter must be returned as a ASCII-encoded character, occupying 1 byte.

```c
front_door_response("Stands so high");
// => 'S'
```

## 2. Capitalize a word

Now that you have all the correct letters, all you need to do to get the password for the front door is to correctly capitalize the word.

Implement the function `front_door_password` that takes as argument the address in memory for a string containing only the combined letters you found in task 1.
It should modify the input string [in-place][in-place], so it is correctly capitalized.
This means that the correct string should be stored in the same memory location of the input.

The function has no return value.

```c
front_door_password('SHIRE');
// => buffer == "Shire"

front_door_password('shire');
// => buffer == "Shire"
```

## 3. Get the last letter of a sentence

To determine letters for the back door password, you need to respond with the last letter of the line of the poem that the guard recites to you.

The members of the poetry club are really clever.
The poem mentioned before is also _telestich_, which means that the last letter of each sentence also forms a word:

```text
Stands so high
Huge hooves too
Impatiently waits for
Reins and harness
Eager to leave
```

When the guard recites **Stands so high**, you'll respond **h**, when the guard recites **Huge hooves too**, you'll respond **o**.

Note that sometimes the guard does stylistic pauses (in the form of punctuation or whitespace) when reciting the poem.
You will need to ignore those pauses to derive the correct letter.

Implement the function `back_door_response` that takes as argument the address in memory for a line of the poem and returns the last letter of that line.
This letter must be returned as a ASCII-encoded character, occupying 1 byte.

```c
back_door_response('Stands so high');
// => "h"

back_door_response('Stands ... so high   ');
// => "h"
```

## 4. Be polite

To enter the poetry club via the back door, you need to be extra polite.
So to derive the password, this time you need to correctly capitalize the word and add `", please."` at the end.

Implement the function `back_door_password` that accepts as arguments, in this order:

1. The address in memory for a buffer where the resulting string will be stored.
2. The address in memory for a string containing the combined letters you found in task 3.

The function should store the polite version of the capitalized password in the [buffer][buffer].
A _buffer_ is an array which can be used to store values in memory to move them between different functions.

This function has no return value.

```c
back_door_password("horse");
// => "Horse, please."
```

[in-place]: https://en.wikipedia.org/wiki/In-place_algorithm
[buffer]: https://en.wikipedia.org/wiki/Data_buffer
