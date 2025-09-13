from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 20

extern void add_seconds(char buffer[], const char *moment);
"""

FUNC_GEN_TEMPLATE = Template("""
char buffer[BUFFER_SIZE];
${prop}(buffer, "${moment}");

TEST_ASSERT_EQUAL_STRING("${expected}", buffer);
""")


def extra_cases():
    return [
        {
            "description": "ends_in_leap_year_divisible_by_400",
            "property": "add",
            "input": {"moment": "2369-02-13"},
            "expected": "2400-10-22T01:46:40",
        },
        {
            "description": "ends_in_non_leap_year_divisible_by_100",
            "property": "add",
            "input": {"moment": "2068-12-21"},
            "expected": "2100-08-30T01:46:40",
        },
        {
            "description": "ends_in_leap_year_divisible_by_4",
            "property": "add",
            "input": {"moment": "1981-02-25"},
            "expected": "2012-11-03T01:46:40",
        },
        {
            "description": "starts_in_leap_year_divisible_by_400",
            "property": "add",
            "input": {"moment": "2000-10-14"},
            "expected": "2032-06-22T01:46:40",
        },
        {
            "description": "starts_in_non_leap_year_divisible_by_100",
            "property": "add",
            "input": {"moment": "1900-04-02"},
            "expected": "1931-12-10T01:46:40",
        },
        {
            "description": "starts_in_leap_year_divisible_by_4",
            "property": "add",
            "input": {"moment": "1996-07-19"},
            "expected": "2028-03-27T01:46:40",
        },
        {
            "description": "ends_in_leap_year_before_end_of_february",
            "property": "add",
            "input": {"moment": "1944-05-28"},
            "expected": "1976-02-04T01:46:40",
        },
        {
            "description": "starts_in_leap_year_before_end_of_february",
            "property": "add",
            "input": {"moment": "1972-01-17"},
            "expected": "2003-09-25T01:46:40",
        },
        {
            "description": "full_time_with_year_rollover",
            "property": "add",
            "input": {"moment": "2099-12-31T23:59:59"},
            "expected": "2131-09-10T01:46:39",
        },
    ]


def gen_func_body(prop, inp, expected):
    return FUNC_GEN_TEMPLATE.substitute(
        prop=f"{prop}_seconds", moment=inp["moment"], expected=expected
    )
