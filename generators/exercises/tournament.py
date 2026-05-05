from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdalign.h>

#define BUFFER_SIZE 1024
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern void tally(char buffer[], const char rows[]);
"""

FUNC_GEN_TEMPLATE = Template("""
alignas(16) char buffer[BUFFER_SIZE];
alignas(16) const char rows[] = "${rows}";
const char *expected = "${expected}";

${prop}(buffer, rows);
TEST_ASSERT_EQUAL_STRING(expected, buffer);
""")


def extra_cases():
    return [
        {
            "description": "team names sharing the first letter",
            "property": "tally",
            "input": {
                "rows": [
                    "Invincible Iguanas;Primal Panthers;draw",
                    "Polar Penguins;Thunderous Tigers;loss",
                    "Heroic Hawks;Howling Hyenas;win",
                    "Tenacious Turtles;Thunderous Tigers;win",
                ]
            },
            "expected": [
                "Team                           | MP |  W |  D |  L |  P",
                "Heroic Hawks                   |  1 |  1 |  0 |  0 |  3",
                "Tenacious Turtles              |  1 |  1 |  0 |  0 |  3",
                "Thunderous Tigers              |  2 |  1 |  0 |  1 |  3",
                "Invincible Iguanas             |  1 |  0 |  1 |  0 |  1",
                "Primal Panthers                |  1 |  0 |  1 |  0 |  1",
                "Howling Hyenas                 |  1 |  0 |  0 |  1 |  0",
                "Polar Penguins                 |  1 |  0 |  0 |  1 |  0",
            ],
        },
        {
            "description": "team composite names sharing the first word",
            "property": "tally",
            "input": {
                "rows": [
                    "Courageous Cougars;Courageous Californians;win",
                    "Courageous Californians;Blithering Badgers;win",
                    "Courageous Cougars;Wild Wolverines;draw",
                    "Charging Cheetahs;Wild Wolves;loss",
                    "Thunderous Tigers;Zealous Zebras;win",
                    "Wild Wolves;Thunderous Tigers;draw",
                ]
            },
            "expected": [
                "Team                           | MP |  W |  D |  L |  P",
                "Courageous Cougars             |  2 |  1 |  1 |  0 |  4",
                "Thunderous Tigers              |  2 |  1 |  1 |  0 |  4",
                "Wild Wolves                    |  2 |  1 |  1 |  0 |  4",
                "Courageous Californians        |  2 |  1 |  0 |  1 |  3",
                "Wild Wolverines                |  1 |  0 |  1 |  0 |  1",
                "Blithering Badgers             |  1 |  0 |  0 |  1 |  0",
                "Charging Cheetahs              |  1 |  0 |  0 |  1 |  0",
                "Zealous Zebras                 |  1 |  0 |  0 |  1 |  0",
            ],
        },
        {
            "description": "team composite names sharing the second word",
            "property": "tally",
            "input": {
                "rows": [
                    "Proud Panthers;Primal Panthers;win",
                    "Heroic Hawks;Blithering Badgers;win",
                    "Heroic Hedgehogs;Wild Wolves;draw",
                    "Fierce Falcons;Courageous Cougars;loss",
                    "Furious Foxes;Flying Falcons;draw",
                    "Wild Wolves;Flying Falcons;loss",
                    "Primal Panthers;Heroic Hawks;win",
                    "Flying Falcons;Proud Panthers;win",
                ]
            },
            "expected": [
                "Team                           | MP |  W |  D |  L |  P",
                "Flying Falcons                 |  3 |  2 |  1 |  0 |  7",
                "Courageous Cougars             |  1 |  1 |  0 |  0 |  3",
                "Heroic Hawks                   |  2 |  1 |  0 |  1 |  3",
                "Primal Panthers                |  2 |  1 |  0 |  1 |  3",
                "Proud Panthers                 |  2 |  1 |  0 |  1 |  3",
                "Furious Foxes                  |  1 |  0 |  1 |  0 |  1",
                "Heroic Hedgehogs               |  1 |  0 |  1 |  0 |  1",
                "Wild Wolves                    |  2 |  0 |  1 |  1 |  1",
                "Blithering Badgers             |  1 |  0 |  0 |  1 |  0",
                "Fierce Falcons                 |  1 |  0 |  0 |  1 |  0",
            ],
        },
        {
            "description": "many teams with names sharing prefixes and suffixes",
            "property": "tally",
            "input": {
                "rows": [
                    "Zealous Zebras;Charging Cheetahs;loss",
                    "Monolith;Blithering Badgers;win",
                    "Primal Panthers;Blithering Badgers;win",
                    "Thunderous Tigers;Howling Hyenas;win",
                    "Furious Foxes;Wild Wolves;draw",
                    "Nebula;Tenacious Turtles;loss",
                    "Heroic Hawks;Wild Wolves;win",
                    "Blithering Badgers;Devastating Donkeys;loss",
                    "Swift Iron Wolf Pack;Zealous Zebras;win",
                    "Charging Cheetahs;Thunderous Tigers;draw",
                    "Howling Hyenas;Primal Panthers;loss",
                    "Proud Panthers;Primal Panthers;draw",
                    "Flying Falcons;Proud Panthers;win",
                    "Fierce Falcons;Flying Falcons;loss",
                    "Tenacious Turtles;Heroic Hawks;win",
                    "Devastating Donkeys;Charging Cheetahs;win",
                    "Fierce Falcons;Primal Panthers;loss",
                    "Wild Wolves;Tenacious Turtles;draw",
                    "Furious Foxes;Blithering Badgers;draw",
                    "Charging Cheetahs;Primal Panthers;loss",
                    "Devastating Donkeys;Thunderous Tigers;loss",
                    "Heroic Hawks;Primal Panthers;win",
                    "Tenacious Turtles;Primal Panthers;win",
                    "Blithering Badgers;Zealous Zebras;draw",
                    "Swift Iron Wolf Pack;Howling Hyenas;win",
                    "Fierce Falcons;Swift Iron Wolf Pack;draw",
                    "Flying Falcons;Zealous Zebras;loss",
                    "Devastating Donkeys;Proud Panthers;draw",
                    "Primal Panthers;Swift Iron Wolf Pack;win",
                    "Heroic Hawks;Charging Cheetahs;draw",
                    "Howling Hyenas;Devastating Donkeys;loss",
                    "Wild Wolves;Flying Falcons;win",
                    "Thunderous Tigers;Blithering Badgers;win",
                    "Proud Panthers;Furious Foxes;draw",
                    "Fierce Falcons;Tenacious Turtles;loss",
                    "Primal Panthers;Zealous Zebras;draw",
                    "Charging Cheetahs;Proud Panthers;draw",
                    "Tenacious Turtles;Wild Wolves;win",
                    "Furious Foxes;Heroic Hawks;loss",
                    "Blithering Badgers;Flying Falcons;win",
                    "Devastating Donkeys;Swift Iron Wolf Pack;draw",
                    "Zealous Zebras;Howling Hyenas;draw",
                    "Primal Panthers;Blithering Badgers;loss",
                    "Fierce Falcons;Devastating Donkeys;draw",
                    "Swift Iron Wolf Pack;Thunderous Tigers;loss",
                    "Flying Falcons;Charging Cheetahs;win",
                    "Heroic Hawks;Furious Foxes;loss",
                    "Tenacious Turtles;Devastating Donkeys;draw",
                    "Monolith;Heroic Hawks;draw",
                    "Nebula;Blithering Badgers;loss",
                    "Wild Wolves;Furious Foxes;win",
                    "Charging Cheetahs;Swift Iron Wolf Pack;loss",
                    "Howling Hyenas;Thunderous Tigers;draw",
                    "Proud Panthers;Zealous Zebras;win",
                    "Primal Panthers;Flying Falcons;loss",
                    "Fierce Falcons;Primal Panthers;win",
                    "Tenacious Turtles;Blithering Badgers;draw",
                    "Heroic Hawks;Devastating Donkeys;win",
                    "Wild Wolves;Zealous Zebras;loss",
                    "Monolith;Tenacious Turtles;win",
                    "Nebula;Furious Foxes;draw",
                ]
            },
            "expected": [
                "Team                           | MP |  W |  D |  L |  P",
                "Tenacious Turtles              |  9 |  5 |  3 |  1 | 18",
                "Primal Panthers                | 12 |  5 |  2 |  5 | 17",
                "Heroic Hawks                   |  8 |  4 |  2 |  2 | 14",
                "Thunderous Tigers              |  6 |  4 |  2 |  0 | 14",
                "Devastating Donkeys            |  9 |  3 |  4 |  2 | 13",
                "Blithering Badgers             | 10 |  3 |  3 |  4 | 12",
                "Flying Falcons                 |  7 |  4 |  0 |  3 | 12",
                "Swift Iron Wolf Pack           |  7 |  3 |  2 |  2 | 11",
                "Zealous Zebras                 |  8 |  2 |  3 |  3 |  9",
                "Wild Wolves                    |  7 |  2 |  2 |  3 |  8",
                "Furious Foxes                  |  7 |  1 |  4 |  2 |  7",
                "Monolith                       |  3 |  2 |  1 |  0 |  7",
                "Proud Panthers                 |  6 |  1 |  4 |  1 |  7",
                "Charging Cheetahs              |  8 |  1 |  3 |  4 |  6",
                "Fierce Falcons                 |  6 |  1 |  2 |  3 |  5",
                "Howling Hyenas                 |  6 |  0 |  2 |  4 |  2",
                "Nebula                         |  3 |  0 |  1 |  2 |  1",
            ],
        },
    ]


def gen_func_body(prop, inp, expected):
    rows = '\\n"\n"'.join(inp["rows"])
    expected = '\\n"\n"'.join(expected)
    return FUNC_GEN_TEMPLATE.substitute(rows=rows, expected=expected, prop=prop)
