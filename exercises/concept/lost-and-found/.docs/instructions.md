# Instructions

Your friend Leticia works at the Lost-and-Found office in a metro station.

Every article found is added to a new entry in a list of found items for the day.
At the end of the month, any item not retrieved is moved to a deposit in a box labeled with the date it was found.
This is all done on paper, so things sometimes get unwieldy!

Leticia asked for your help in automating some of these tasks.

## 1. Create an entry for each item

The first thing you need to do is to organize all items, so they can be looked up in a easier way.
Each item is identified in storage by its ID, a description, the date it was found and a variable number of categories.

Define a function `create_item_entry` that has no return value and inserts a new item entry in a memory location.
This function may take any number of parameters, of which the first six always are:

1. The address for a location in memory where the item should be stored.
2. The ID for the item, as a 64-bit unsigned integer.
3. The address for a string with the item's description.
4. The day the item was found, as a 64-bit unsigned integer.
5. The month the item was found, as a 64-bit unsigned integer.
6. The number of categories for the item, as a 64-bit unsigned integer.

Each subsequent parameter is the address for a string with one of the categories.

Values should be stored in the provided memory location in the same order of the arguments: ID, description, day, month, number of categories, and each category in order.

## 2. Reserve space for a monthly list of items

It is cumbersome to search for items in so many different lists.
So, you decide to organize everything in a single list for each month.
This list is implemented as an array.

Define the `create_monthly_list` function that allocates space in memory for an array of items and returns the address of that memory location.
It takes as parameters:

1. The capacity of the array in bytes, as a 64-bit unsigned integer.
2. An allocator function.

The allocator function takes as parameter a 64-bit unsigned integer corresponding to the size in memory to be allocated, in bytes, and returns the address for the allocated space.

Note that the allocated space has _undefined_ value, so all bytes in that space should be cleared, ie, their value should be set to `0`.

## 3. Insert an item in the monthly list

At each day, every found item should be inserted in the monthly list.

Define the `insert_found_item` function that has no return value and takes as parameters:

1. The address for a space in memory where the monthly list is located.
2. The current number of entries already stored in the list, as a 64-bit unsigned integer.
3. A new entry to be added to the list.

You may consider that the new entry always fits into the list and that all entries in the list take up 120 bytes in space.

## 4. Print an item

Searching for a specific item would be much easier if Leticia could see all categories for the item on the screen.

Define the `print_item` function that takes as parameters:

1. The address for a buffer where an introductory ASCII NUL-terminated string may be stored.
2. The address for a space in memory where the monthly list is located.
3. The index of the entry that should be printed, as a 64-bit unsigned integer.
4. A printing function.

This function has no return value and should call the printing function with the following arguments:

1. A 64-bit value with the address to the memory location with the introductory string or with `0` if no string is passed.
2. The index of the item in the array, as a 64-bit unsigned integer.
3. The ID for the item, as a 64-bit unsigned integer.
4. The address for a string with the item's description.
5. The day the item was found, as a 64-bit unsigned integer.
6. The month the item was found, as a 64-bit unsigned integer.
7. The number of categories for the item, as a 64-bit unsigned integer.
8. The address of the first category string.

The introductory string is not mandatory, the value 0 can be passed instead.
If passed, the introductory string must have at most 50 characters and be NUL-terminated (ending in `0`).

You may consider that each item in the list takes up 120 bytes in space.
