# Instructions

You're an avid bird watcher that keeps track of how many birds have visited your garden in the last seven days.

You have six tasks, all dealing with the numbers of birds that visited your garden.

~~~~exercism/note
The number of birds in each day is represented as a 8-bit (1-byte) number.
~~~~

## 1. Check what the counts were last week

For comparison purposes, you always keep a copy of the last week's counts nearby.

Implement the `last_week_counts` function that takes no parameter and returns a copy of last week's counts as a 8-byte number, where each byte represent a day's count, in order from the oldest (least-significant byte) to most recent.
Since the week has only 7 days, the last byte must be zeroed-out.

At the start of the program, the last week's counts, from the oldest (least-significant byte) to most recent, are: 0, 2, 5, 3, 7, 8 and 4.

## 2. Check what are the current counts for this week

Implement the `current_week_counts` function that takes no parameter and returns:

- A copy of current week's counts as a 8-byte number, where each byte represent a day's count, in order from the oldest (least-significant byte) to most recent.
- The number of days already with counts in the current week, as a 8-byte number.

All days after the most recent one should have its corresponding byte zeroed-out.

At the start of the program, there is no count for the current week.

~~~~exercism/note
In order to return two integers from a function, you should use both `rax` and `rdx` registers:

```x86asm
returning_two_values:
    mov rax, rdi
    mov rdx, rsi
    ret
```
~~~~

## 3. Save count for each day

Implement the `save_count` function which takes as parameter the most recent count, as a 1-byte number, and saves it in a new entry for the current week.
This function has no return value.

If there is already 7 entries in the current week before this function is called, the current week becomes the last week and the new entry is the first day of a new current week.

## 4. Check how many birds visited today

Implement the `today_count` function that has no parameter and returns the most recent entry for the current week, as a 1-byte number.

You can consider that this function will only be called after at least one day's count was added.

## 5. Update today's count

Sometimes after you finish counting birds for a day, but before you leave, you notice some new birds arriving.

Implement the `update_today_count` function that has no return value and adds a certain number of birds to the most recent entry for the current week.
This function takes as parameter the number of birds to be added, as a 1-byte number.

You can consider that this function will only be called after at least one day's count was added.

## 6. Insert new entries in bulk

Sometimes you are away to visit family.
On those occasions, you have a camera monitoring your garden, so you can update counts for the entire week.

Implement the `update_week_counts` function that has no return value and inserts counts for an entire week in one go.
It takes as parameter a 8-byte number, where each byte represent a day's count, in order from the oldest to most recent.
The last byte in the input parameter has no meaning and must be zeroed-out.

Once a new week is inserted, the current week becomes the last week and the inserted week becomes the current week.

You can consider that this function will only be called after all days in the current week were already filled.
