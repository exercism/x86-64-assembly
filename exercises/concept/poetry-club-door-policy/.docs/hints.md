# Hints

## General

- In a ASCII-encoded string, all characters occupy 1 byte in memory.
- You need to use `[]` to dereference memory locations.
- The ASCII value for an upper case letter is 32 less than the ASCII value for the equivalent lower case letter.

## 1. Get the first letter of a sentence

- In a ASCII-encoded string, all characters occupy 1 byte in memory.
- You need to use `[]` to dereference memory locations.
- The ASCII value for an upper case letter is 32 less than the ASCII value for the equivalent lower case letter.
- 1-byte values are returned in `al`.

## 2. Capitalize a word

- In a ASCII-encoded string, all characters occupy 1 byte in memory.
- You need to use `[]` to dereference memory locations.
- The ASCII value for an upper case letter is 32 less than the ASCII value for the equivalent lower case letter.
- Capitalization means having a single _uppercase_ character, followed by _lowercase_ characters.
- Only values between 'a' and 'z' are lowercase letters, and only values between 'A' and 'Z' are uppercase letters.
- So first, you need to extract the first letter and convert it to uppercase if it is in lower case.
- Then you need to determine the rest of the string, every character after the first should be converted to lowercase if it is an uppercase letter, or left unchanged otherwise.
- The string ends when `'\0'` (the NUL character) is found.
- You can use `lodsb` to load in `al` a byte in the memory location in `rsi`, changing `rsi` by 1.
- You can use `stosb` to store in the memory location in `rdi` a byte loaded in `al`, changing `rdi` by 1.

## 3. Get the last letter of a sentence

- In a ASCII-encoded string, all characters occupy 1 byte in memory.
- You need to use `[]` to dereference memory locations.
- The ASCII value for an upper case letter is 32 less than the ASCII value for the equivalent lower case letter.
- You need to loop over the string to find the last letter.
- Only values between 'a' and 'z' are lower case letters, and only values between 'A' and 'Z' are upper case letters.
- 1-byte values are returned in `al`.

## 4. Be polite

- In a ASCII-encoded string, all characters occupy 1 byte in memory.
- You need to use `[]` to dereference memory locations.
- The ASCII value for an upper case letter is 32 less than the ASCII value for the equivalent lower case letter.
- Re-use an existing function to capitalize the word.
- You can use `movsb` to copy a byte in the memory address in `rsi` to the memory address in `rdi`, changing both `rsi` and `rdi` by 1.
- You can define an initialized string in _section .rodata_ or _section .data_.
- You must use `rel` to compute a relative address.
- For an array declared with the label `arr`, `$ - arr` would be the total size of `arr` in bytes if used just after declaring the array.
- You can use `rep` to repeat a string instruction such as `movsb` a number of times specified by `rcx`.
- The string should end with `'\0'` (the NUL character) as terminator.
- Remember that special characters, with a backslash (such as `'\0'`) should be defined in backticks (` ` `), or by using their decimal value (which is `0` for NUL).
