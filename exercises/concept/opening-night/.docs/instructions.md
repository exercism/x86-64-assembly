# Instructions

It is opening night at the Grand Marquee, and the whole staff is working at once.
The crowd pours in through every door, several box-office windows sell from the same ticket roll, the premiere is close to selling out, and up in the projection booth the reels have to keep moving.

Everything the staff shares lives at a memory address, and the tests call your functions from several threads at the same time.
A value that is read, changed, and written back in separate steps will lose updates under that load, so each function must make its update atomic.

All shared values in this exercise are 64-bit signed integers.

You have five tasks.

~~~~exercism/note
The updates in this exercise should be performed with _atomic_ instructions.
The tests run your functions concurrently and check that no update is lost, so a non-atomic read-modify-write is very likely to fail them.
~~~~

## 1. Count the admissions

The doors are open, and at every one of them an usher is tearing tickets.
Each group let through is counted into one shared admissions tally, and with every door counting at once, the house count must still come out true.

Implement the `admit_group` function, which atomically adds the size of a group to the tally.

This function takes as arguments, in this order:

- `admissions`: memory address of the shared admissions tally, a 64-bit signed integer.
- `group_size`: the number of people in the group, a 64-bit signed integer, always greater than `0`.

```c
admissions = 120, group_size = 4
// admissions is now 124
```

The tests admit groups through several doors at once.
The final tally must equal the sum of every group let through.

This function has no return value.
The tally should be updated in-place.

## 2. Change the reel

The projector mounts exactly one reel.
Mounting the next reel and taking out the current one must be a single motion: with two projectionists at the machine, two separate steps could hand the same reel to both of them, or drop one on the floor.

Implement the `change_reel` function, which atomically mounts the next reel and returns the one that was mounted.

This function takes as arguments, in this order:

- `mounted`: memory address of the identifier of the mounted reel, a 64-bit signed integer.
- `next_reel`: the identifier of the reel to mount, a 64-bit signed integer.

```c
mounted = 7, next_reel = 9
// => 7, and mounted is now 9
```

This function returns the identifier of the previously mounted reel as a 64-bit signed integer.
The tests have several threads swap reels through the same mount at once, and check that every reel handed in comes back out exactly once.

## 3. Sell a ticket

Every window sells from one shared count of tickets sold.
Adding to a count, as the doors do, is not enough here: each sale must also learn the number it was given.
No two sales may share a number, and after the rush the count must equal the number of tickets sold, exactly.

Implement the `sell_ticket` function, which atomically adds one to the count and returns the number of the ticket just sold.
The ticket number is the count _after_ this sale: when the count was `41`, this sale is ticket `42`.

This function takes as an argument:

- `tickets_sold`: memory address of the shared count of tickets sold, a 64-bit signed integer.

```c
tickets_sold = 0
// => 1, and tickets_sold is now 1

tickets_sold = 41
// => 42, and tickets_sold is now 42
```

This function returns the ticket number as a 64-bit signed integer.
The tests sell from several windows at once: every returned number must be distinct, and the final count must equal the number of sales.

## 4. Fill the premiere

The premiere has a fixed number of seats, and every window is selling it.
A sale may only go through while a seat remains, and the screening must never oversell, not even when every window grabs for the last seat in the same instant.
Checking the count and then adding to it as two separate steps leaves a window in between, so the check and the update must succeed or fail together.

Implement the `claim_seat` function, which atomically claims the next seat when one is still free.
When a seat is claimed, the function returns the seat's number, which is the count of taken seats after this claim.
When the screening is sold out, it returns `0` and leaves the count unchanged.

This function takes as arguments, in this order:

- `seats_taken`: memory address of the count of seats already taken, a 64-bit signed integer, never above `capacity`.
- `capacity`: the number of seats in the screening, a 64-bit signed integer, always greater than `0`.

```c
seats_taken = 0, capacity = 150
// => 1, and seats_taken is now 1

seats_taken = 82, capacity = 150
// => 83, and seats_taken is now 83

seats_taken = 149, capacity = 150
// => 150, and seats_taken is now 150

seats_taken = 150, capacity = 150
// => 0, and seats_taken stays 150
```

This function returns the seat number, or `0` when the screening is sold out, as a 64-bit signed integer.

## 5. Mind the booth

The projection booth fits one person.
A word in memory says whether it is occupied: `0` for free, `1` for occupied.
Staff come by all night, each with a task to do inside: sign the logbook, thread the projector, file a reel.
Whatever the task, the booth's rule is the same, and enforcing it is your job: one person inside at a time, from the start of their task to its end.

Implement the `visit_booth` function, which:

1. waits until the booth is free;
2. claims the booth;
3. runs the visitor's task;
4. reopens the booth after the task and before returning.

While the booth is held by someone else, it should wait politely with `pause`.

This function takes as arguments, in this order:

- `booth`: memory address of the occupancy word, a 64-bit signed integer that is either `0` or `1`.
- `task`: the visitor's task, a function that takes no parameters and has no return value.

Note the tests run tasks that look at the booth and at a shared logbook.
This means the booth must be occupied for the whole task, every visit must run its task exactly once, and with several visitors at once the logbook must come out exact.

~~~~exercism/caution
The visitor's task is an ordinary function that follows the calling convention:

- it may overwrite any caller-saved register, so you should keep anything you still need after the task somewhere the call cannot touch;
- it also expects the stack to be 16-byte aligned at the point of the call.

A violation of either rule may surface as a crash rather than a failed check.
~~~~
