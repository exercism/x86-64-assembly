# Instructions

Your friend has just sent you a message with an important secret.
Not wanting to make it easy for others to read it, the message was encrypted by performing a series of bit manipulations.
You will need to write the methods to help decrypt the message.

~~~~exercism/note
These are the single bit instructions mentioned in this concept:

| Name | Description                                                                   |
|------|-------------------------------------------------------------------------------|
|bt    |copies the bit into `CF` without modifying any operand                         |
|bts   |copies the bit into `CF` and sets it in the destination operand                |
|btr   |copies the bit into `CF` and clears it in the destination operand              |
|btc   |copies the bit into `CF` and complements (flips) it in the destination operand |

These are the bitwise instructions mentioned in this concept:

| Name   | Description                                  |
|--------|----------------------------------------------|
|and     |1 if both bits are 1                          |
|or      |1 if at least one of the bits is 1            |
|xor     |1 if the bits differ                          |
|not     |1 if bit was 0; 0 if bit was 1                |

These are the shift instructions mentioned in this concept:

| Name    | Description             |
|---------|-------------------------|
|shl/sal  |Shifts bits to the left  |
|shr/sar  |Shifts bits to the right |

These are the rotation instructions mentioned in this concept:

| Name    | Description                                   |
|---------|-----------------------------------------------|
|rol      |Rotates bits to the left                       |
|ror      |Rotates bits to the right                      |
|rcl      |Rotates bits to the left, including the `CF`   |
|rcr      |Rotates bits to the right, including the `CF`  |

These are the miscellaneous instructions mentioned in this concept:

| Name     | Description                                                                            |
|----------|----------------------------------------------------------------------------------------|
| popcnt   | Counts the number of bits set                                                          |
| lzcnt    | Counts the number of leading zeros (a bit cleared before the first set bit)            |
| bsr      | Gets the index of the most significant set bit. If no bit is set, result is undefined  |
| bsf      | Gets the index of the least significant set bit. If no bit is set, result is undefined |
~~~~

## 1. Extract the mask

The message is encoded in a 16-bit integer.
However, of those, the 8 highest bits are not actually part of the message, but a mask that needs to be used in the decryption.

Implement the `extract_higher_bits` function that takes a 16-bit integer and returns the 8 highest bits of it.

```c
extract_mask(0b1010010011000101)
// => 0b10100100
```

## 2. Extract the message

Having the ability of extracting the mask is not enough, you should also isolate the message.

Implement the `extract_lower_bits` function that takes a 16-bit integer and returns the 8 lowest bits of it.

```c
extract_mask(0b1100010011000101);
// => 0b11000101
```

## 3. Extract redundant bits

Some bits are set in both the message and the mask.
This is a very important piece of information that will be used later.

Implement the `extract_redundant_bits` that takes a 16-bit integer, encoding both the message and a mask, and returns a 8-bit integer with only the redundant bits set.
A bit in the returned number should be set to 1 where it is also 1 in both the message and the mask.
All other bits should be _cleared_.

```c
extract_redundant_bits(0b1100010011000101);
// => 0b10000100
```

## 4. Set all message bits

Next, there are some bits that need to be set to `1` in the message, according to the mask.

Implement the `set_message_bits` function that takes a 16-bit integer, encoding both the message and a mask, and returns the result of setting the bits in the message to 1.
A bit from the message should be set to 1 where the bit in the mask is also 1.
All other bits should be kept _unchanged_, so that they remain set if they were already set, and cleared if they were already cleared.

```c
set_message_bits(0b1110010011000101);
// => 0b11100101
```

## 5. Rotate private key

There is a piece of the puzzle not explicit in the message: the 16-bit number `0b1011001100111100`.
This number is your shared private key and you should use it to help decrypt the message.

In order to do that, you first need to rotate the bits of your private key to the left by a certain number of positions.
The number of positions is equal to the number of redundant bits set in both the message and the mask.

Implement the `rotate_private_key` function that takes a 16-bit integer, encoding both the message and a mask, and returns the result of rotating your private key.
This result is a 16-bit integer.

```c
rotate_private_key(0b1100010011000101);
// => 0b1100110011110000
```

~~~~exercism/note
NASM (The Netwide Assembler, the assembler used by this track) has support to constants in binary format with `0b` prefixed.
It also supports using an underscore (`_`) as separator in a constant, for readability:

```nasm
PRIVATE_KEY equ 0b1011_0011_0011_1100
```
~~~~

## 6. Format private key

In order to be used in decryption, your private key must be formatted to isolate the relevant bits.

To fully format a private key, you must:

- Rotate it.
- Isolate the lowest 8-bit portion of the rotated private key, which is the base value.
- Isolate the highest 8-bit portion of the rotated private key, which is a mask to be applied to the base value.
- Flip set bits in the base value that are also set in the mask.
- Flip all bits in the result.

A flipped bit is 1 if it was 0 and 0 if it was 1.

Implement the `format_private_key` function that takes a 16-bit integer, encoding both the message and a mask, and returns a fully formatted 8-bit private key.

```c
format_private_key(0b1100010011000101);
// => 0b11000011
```

## 7. Finish decryption

Once you have the message with all relevant bits set and the formatted private key, it is time to join them together to get the resulting message.

The resulting message is a 16-bit integer, of which:

- The highest 8 bits is filled with the formatted private key.
- The lowest 8 bits is filled with the message, after setting all relevant bits.

Implement the `decrypt_message` function that takes a 16-bit integer encoding both the message and a mask, and returns a 16-bit integer with the message fully decrypted.

This function should make use of the formatted private key that you generate with `format_private_key` and also of the message with all relevant bits set with `set_message_bits`.

```c
decrypt_message(0b1100010011000101);
// => 0b1100001111100101
```
