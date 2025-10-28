# Instructions

In this exercise you'll be organizing races between various types of remote controlled cars.
Each car has its own characteristics and runs on many different tracks in races throughout the tournament season.

~~~~exercism/note
The functions in this exercise are declared in a C source file with the provided signatures.
Your x86-64-assembly code must follow those specifications.
~~~~

## 1. Create a remote controlled car

You have defined a struct `car_t` to represent a remote controlled car:

```c
struct car_t {
    char name[10];
    int16_t speed;
    float battery;
};
```

Allow creating a remote controlled car by defining a function `new_car` in x86-64 assembly.
The field `battery` always starts with the value `100.0`.

```c
struct car_t new_car(short speed, const char name[]);
```

## 2. Create new track

Tracks are represented by a struct `track_t`:

```c
struct track_t {
    enum surface_t surface;
    size_t distance;
};
```

The `enum surface_t` keeps track of different surfaces for a track:

```c
enum surface_t {
    ASPHALT,
    SAND,
    ICE,
    CLAY
};
```

Allow creating a new track by defining a function `new_track` in x86-64 assembly.

```c
struct track_t new_track(enum surface_t surface, size_t distance);
```

## 3. Create a racing event

Up to 6 cars participate in each race, running some specified number of laps on a track.
Races are represented by a struct `race_t`:

```c
struct race_t {
    struct track_t track;
    uint8_t num_of_laps;
    struct car_t cars[6];
    uint8_t num_of_running_cars;
};
```

Define a function `new_race` in x86-64 assembly.
At the start, there are no confirmed participating cars for the race:

```c
struct race_t new_race(struct track_t track, uint8_t num_of_laps);
```

## 4. Confirm a car to the race

When a car's owner asks for it to participate in a race, its participation is only confirmed if the list is not already full.

Define a function `add_participant` in x86-64 assembly.
If there's room for one more participant in the race, the car is added to the list, updating the counter, and its participation is confirmed.
Otherwise, the race organizers must inform the car's owner that it can't participate this time.

```c
bool add_participant(struct race_t *race, struct car_t car);
```

## 5. Create a tournament

You keep track of races scheduled for the season in a struct `tournament_t`:

```c
struct tournament_t {
    struct race_t races[20];
    size_t num_of_races;
};
```

Define a function `add_race` in x86-assembly, to add a race to the tournament's array and also update its counter.
You may consider that there will always be enough space in the `races` array for the new race.

```c
void add_race(struct tournament_t *tournament, struct race_t race);
```
