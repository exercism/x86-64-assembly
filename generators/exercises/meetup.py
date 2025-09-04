FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 20

typedef enum {
    FIRST = 1,
    SECOND,
    THIRD,
    FOURTH,
    TEENTH,
    LAST
} week_t;

typedef enum {
    MONDAY = 1,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
} dayofweek_t;

extern void meetup(char *buffer, int year, int month, week_t week, dayofweek_t dayofweek);
"""


def extra_cases():
    return [
        {
            "description": "when last Thursday in February in a non-leap year is not the 29th",
            "property": "meetup",
            "input": {
                "year": 2300,
                "month": 2,
                "week": "last",
                "dayofweek": "Thursday",
            },
            "expected": "2300-02-22",
        },
        {
            "description": "when fourth Monday is the 23nd, the second day of the fourth week",
            "property": "meetup",
            "input": {
                "year": 2468,
                "month": 1,
                "week": "fourth",
                "dayofweek": "Monday",
            },
            "expected": "2468-01-23",
        },
    ]


def gen_func_body(prop, inp, expected):
    year = inp["year"]
    month = inp["month"]
    week = inp["week"].upper()
    dayofweek = inp["dayofweek"].upper()

    str_list = []
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f"{prop}(buffer, {year}, {month}, {week}, {dayofweek});\n")
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);\n')
    return "".join(str_list)
