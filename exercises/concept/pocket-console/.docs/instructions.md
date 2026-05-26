# Instructions

You are writing firmware for the scoring system in a retro handheld console.
The machine's CPU is modest, and the scoreboard display refreshes at a fixed rate.
For the picture to stay smooth, the scoring routines must run in a predictable number of cycles regardless of what the player is doing.

You have four tasks.

~~~~exercism/note
The code for the tasks should be branchless.
Use `cmovcc`, `setcc`, and arithmetic instead of conditional jumps.
~~~~

## 1. Add a bonus without overflowing the display

The score region of the handheld's LCD has room for six decimal digits.
It cannot show any number above `999999`.
When a bonus would push the running total past that limit, the displayed total is held at the maximum rather than wrapping around.

Define a function `add_bonus` that, given a current total and a bonus to add, returns the new total clamped at `999999`.
The arguments, in order, are:

1. `total`: the current score total (always between `0` and `999999`)
2. `bonus`: the bonus to add (always non-negative)

The return value is `total + bonus` if that sum is less than or equal to `999999`, and `999999` otherwise:

```c
add_bonus(500, 100);
// => 600
add_bonus(999990, 50);
// => 999999
add_bonus(999999, 0);
// => 999999
```

Both arguments and the return value are 64-bit signed integers.

~~~~exercism/note
You may assume that `total + bonus` does not overflow a 64-bit signed integer.
~~~~

## 2. Compare two scores

The handheld keeps a small leaderboard of the player's best recent scores in its save file.
After each play, the new score is inserted into the leaderboard at the right position.
The sort routine asks which of two scores is ahead and expects the answer as a small integer.

Define a function `compare_scores` that, given two scores, returns:

- `+1` if the first score is _higher_
- `-1` if the first score is _lower_
- `0` if the two scores are _equal_

Example:

```c
compare_scores(500, 300);
// => 1
compare_scores(300, 500);
// => -1
compare_scores(500, 500);
// => 0
```

Both arguments and the return value are 64-bit signed integers.

## 3. Validate a raw score

The handheld can connect to another unit through its link cable to share scores after a multiplayer match.
The cable is electrically noisy and incoming bytes are occasionally corrupted, producing values far below the legal minimum or far above the legal maximum.
The validator clamps each incoming score into the legal range before the rest of the system sees it.

Define a function `validate_score` that, given a raw score and the legal bounds, returns the score clamped to `[min, max]`.
The arguments, in order, are:

1. `score`: the raw score received over the link cable
2. `min`: the smallest allowed score
3. `max`: the largest allowed score

The return value is `min` if `score < min`, `max` if `score > max`, and `score` otherwise.
You may assume that `min <= max`.

Example:

```c
validate_score(450, 0, 500);
// => 450
validate_score(-50, 0, 1530);
// => 0
validate_score(1234567, 0, 2999);
// => 2999
```

All arguments and the return value are 64-bit signed integers.

## 4. Track the two highest scores

At the end of each play session, the handheld scans the recent-plays log in its save file to find the two highest scores ever recorded.
The log is a plain array of 64-bit signed integers in memory.
The scan walks the array once and keeps two running maxes: the highest seen so far, and the second highest.

Note that both numbers should be at least `0`.
Any negative number is disregarded.

A first version of the function was written with cascading conditional jumps.
For each candidate, the code asks where it fits (above first, between first and second, or nowhere) and shifts the running maxes accordingly, discarding any negative result.

This works.
However, since the input values are random, each conditional jump leads to many branch mispredictions.
This is why you have decided to refactor the main loop to be branchless.

Below is the function with the branchy section commented out:

```x86asm
; rdi = output buffer for two elements, rsi = input array address, rdx = number of elements in array
top_two:
    xor r8d, r8d                   ; first  = 0
    xor r9d, r9d                   ; second = 0
    xor ecx, ecx                   ; index = 0
    test rdx, rdx
    jz .done

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                       BRANCHY CODE TO REFACTOR
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;.loop:
;    mov rax, qword [rsi + 8*rcx]   ; candidate
;    inc rcx
;    cmp rax, r8
;    jle .check_second              ; candidate <= first, try second
;    mov r9, r8                     ; second = first
;    mov r8, rax                    ; first  = candidate
;    cmp rcx, rdx
;    jb .loop                       ; go to next iteration
;    jmp .done                      ; otherwise, we are done
;.check_second:
;    cmp rax, r9
;    jle .loop                      ; candidate <= second, go to next iteration
;    mov r9, rax                    ; second = candidate
;    cmp rcx, rdx
;    jb .loop                       ; go to next iteration
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.done:
    mov qword [rdi], r8            ; save first
    mov qword [rdi + 8], r9        ; save second
    ret
```

Replace the commented-out section with a branchless implementation.
The only jump permitted in the new code is the one that jumps back to the start of the loop to check a new element in the array.

The function has no return value and takes the same arguments as the branchy version:

1. `out`: output buffer where the function will write the top two non-negative scores in descending order, as 64-bit signed integers
2. `array`: input array of 64-bit signed integers
3. `length`: the number of elements in the array, as a 64-bit unsigned integer

~~~~exercism/note
If the array contains duplicate values, the duplicates may appear in both output slots if they are the top two scores.
~~~~
