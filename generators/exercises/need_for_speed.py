FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct car_t {
    char name[10];
    int16_t speed;
    float battery;
};

enum surface_t {
    ASPHALT,
    SAND,
    ICE,
    CLAY
};

struct track_t {
    enum surface_t surface;
    size_t distance;
};

struct race_t {
    struct track_t track;
    uint8_t num_of_laps;
    struct car_t cars[6];
    uint8_t num_of_running_cars;
};

struct tournament_t {
    struct race_t races[20];
    size_t num_of_races;
};

extern struct car_t new_car(short speed, const char name[]);
extern struct track_t new_track(enum surface_t surface, size_t distance);
extern struct race_t new_race(struct track_t track, uint8_t num_of_laps);
extern bool add_participant(struct race_t *race, struct car_t car);
extern void add_race(struct tournament_t *tournament, struct race_t race);
"""


def extra_cases():
    return [
        {
            "description": "new_cars",
            "property": "new_car",
            "input": [
                ("Thunder", 517),
                ("Opal", 626),
                ("Monster", 483),
                ("Firebolt", 789),
                ("Jumbo", 548),
                ("Rampage", 773),
            ],
            "expected": [
                ("Thunder", 517),
                ("Opal", 626),
                ("Monster", 483),
                ("Firebolt", 789),
                ("Jumbo", 548),
                ("Rampage", 773),
            ],
        },
        {
            "description": "new_tracks",
            "property": "new_track",
            "input": [
                ("SAND", 4780),
                ("ASPHALT", 10450),
                ("CLAY", 5587),
                ("ICE", 1384),
            ],
            "expected": [
                ("SAND", 4780),
                ("ASPHALT", 10450),
                ("CLAY", 5587),
                ("ICE", 1384),
            ],
        },
        {
            "description": "new_races",
            "property": "new_race",
            "input": [
                ((("CLAY", 7628), 18)),
                (("SAND", 3456), 25),
                (("ASPHALT", 5287), 36),
                (("ICE", 4981), 17),
            ],
            "expected": [
                ((("CLAY", 7628), 18)),
                (("SAND", 3456), 25),
                (("ASPHALT", 5287), 36),
                (("ICE", 4981), 17),
            ],
        },
        {
            "description": "add_participants",
            "property": "add_participant",
            "input": (
                (("ASPHALT", 5287), 36),
                [
                    ("Thunder", 517),
                    ("Opal", 626),
                    ("Monster", 483),
                    ("Firebolt", 789),
                    ("Jumbo", 548),
                    ("Rampage", 773),
                    ("Razor", 633),
                    ("Astro", 892),
                ],
            ),
            "expected": [True, True, True, True, True, True, False, False],
        },
        {
            "description": "add_races",
            "property": "add_race",
            "input": [
                ((("ICE", 23435), 27)),
                (("CLAY", 3456), 12),
                (("ASPHALT", 5287), 21),
                (("ICE", 4981), 33),
                (("SAND", 1245), 13),
                (("ASPHALT", 7736), 24),
            ],
            "expected": None,
        },
    ]


def adjust_bool(bool):
    return str(bool).lower()


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "new_car":
        for i, (name, speed) in enumerate(inp):
            exp_name, exp_speed = expected[i]
            str_list.append(f'char name{i + 1}[10] = "{name}";')
            str_list.append(f"struct car_t car{i + 1} = {prop}({speed}, name{i + 1});")
            str_list.append(
                f'TEST_ASSERT_EQUAL_INT16_MESSAGE({exp_speed}, car{i + 1}.speed, "Mismatch on car speed.");'
            )
            str_list.append(
                f'TEST_ASSERT_EQUAL_STRING_MESSAGE("{exp_name}", car{i + 1}.name, "Mismatch on car name.");'
            )
            str_list.append(
                f'TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, car{i + 1}.battery, "Mismatch on car battery.");'
            )
    elif prop == "new_track":
        for i, (surface, dist) in enumerate(inp):
            exp_surface, exp_dist = expected[i]
            str_list.append(f"struct track_t track{i + 1} = {prop}({surface}, {dist});")
            str_list.append(
                f'TEST_ASSERT_EQUAL_MESSAGE({exp_surface}, track{i + 1}.surface, "Mismatch on track surface.");'
            )
            str_list.append(
                f'TEST_ASSERT_EQUAL_UINT64_MESSAGE({exp_dist}, track{i + 1}.distance, "Mismatch on track distance.");'
            )
    elif prop == "new_race":
        for i, ((surface, dist), num_laps) in enumerate(inp):
            (exp_surface, exp_dist), exp_laps = expected[i]
            str_list.append(
                f"struct race_t race{i + 1} = {prop}(new_track({surface}, {dist}), {num_laps});"
            )
            str_list.append(
                f'TEST_ASSERT_EQUAL_MESSAGE({exp_surface}, race{i + 1}.track.surface, "Mismatch on track surface.");'
            )
            str_list.append(
                f'TEST_ASSERT_EQUAL_UINT64_MESSAGE({exp_dist}, race{i + 1}.track.distance, "Mismatch on track distance.");'
            )
            str_list.append(
                f'TEST_ASSERT_EQUAL_UINT8_MESSAGE({exp_laps}, race{i + 1}.num_of_laps, "Mismatch on number of laps.");'
            )
            str_list.append(
                f'TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, race{i + 1}.num_of_running_cars, "Mismatch on number of running cars.");'
            )
    elif prop == "add_participant":
        ((start_surface, start_dist), start_laps), inp_arr = inp
        str_list.append(
            f"struct race_t race = new_race(new_track({start_surface}, {start_dist}), {start_laps});"
        )
        for i, (name, speed) in enumerate(inp_arr):
            str_list.append(f'char name{i + 1}[10] = "{name}";')
            str_list.append(
                f'TEST_ASSERT_EQUAL_MESSAGE({adjust_bool(expected[i])}, {prop}(&race, new_car({speed}, name{i + 1})), "Number of cars in array before the function is called - {i + 1}.");'
            )
            if expected[i]:
                str_list.append(
                    f'TEST_ASSERT_EQUAL_STRING_MESSAGE("{name}", race.cars[{i}].name, "Mismatch on name for car at index {i}.");'
                )
                str_list.append(
                    f'TEST_ASSERT_EQUAL_UINT16_MESSAGE({speed}, race.cars[{i}].speed, "Mismatch on speed for car at index {i}.");'
                )
                str_list.append(
                    f'TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, race.cars[{i}].battery, "Mismatch on battery for car at index {i}.");'
                )
    else:
        str_list.append("struct tournament_t tournament = {0};")
        for i, ((surface, dist), num_laps) in enumerate(inp):
            str_list.append(
                f"{prop}(&tournament, new_race(new_track({surface}, {dist}), {num_laps}));"
            )
            str_list.append(
                f'TEST_ASSERT_EQUAL_UINT64_MESSAGE({i + 1}, tournament.num_of_races, "Mismatch on number of races.");'
            )
            str_list.append(
                f'TEST_ASSERT_EQUAL_MESSAGE({surface}, tournament.races[{i}].track.surface, "Mismatch on track surface for race at index {i}.");'
            )
            str_list.append(
                f'TEST_ASSERT_EQUAL_UINT64_MESSAGE({dist}, tournament.races[{i}].track.distance, "Mismatch on track distance for race at index {i}.");'
            )
            str_list.append(
                f'TEST_ASSERT_EQUAL_UINT8_MESSAGE({num_laps}, tournament.races[{i}].num_of_laps, "Mismatch on number of laps for race at index {i}.");'
            )
            str_list.append(
                f'TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, tournament.races[{i}].num_of_running_cars, "Mismatch on number of running cars for race at index {i}.");'
            )
    return "\n".join(str_list)
