FUNC_PROTO = """\

#include "vendor/unity.h"

#include <stdint.h>

extern double daily_rate(double hourly_rate);
extern double apply_discount(double price, double discount);
extern uint64_t monthly_rate(double hourly_rate, double discount);
extern uint32_t days_in_budget(uint64_t budget, double hourly_rate, double discount);
"""


def extra_cases():
    return [
        {
            "description": "daily_rate_is_hourly_times_8",
            "property": "daily_rate",
            "input": 50,
            "expected": 400.0,
        },
        {
            "description": "daily_rate_always_returns_double",
            "property": "daily_rate",
            "input": 60,
            "expected": 480.0,
        },
        {
            "description": "daily_rate_does_not_round",
            "property": "daily_rate",
            "input": 55.1,
            "expected": 440.8,
        },
        {
            "description": "apply_discount_10_percent",
            "property": "apply_discount",
            "input": {"price": 140.0, "discount": 10.0},
            "expected": 126.0,
        },
        {
            "description": "apply_discount_does_not_round",
            "property": "apply_discount",
            "input": {"price": 111.11, "discount": 13.5},
            "expected": 96.11015,
        },
        {
            "description": "monthly_rate_is_daily_rate_times_22",
            "property": "monthly_rate",
            "input": {"hourly_rate": 62.0, "discount": 0.0},
            "expected": 10912,
        },
        {
            "description": "monthly_rate_is_rounded_up_1",
            "property": "monthly_rate",
            "input": {"hourly_rate": 62.8, "discount": 0.0},
            "expected": 11053,
        },
        {
            "description": "monthly_rate_is_rounded_up_2",
            "property": "monthly_rate",
            "input": {"hourly_rate": 65.2, "discount": 0.0},
            "expected": 11476,
        },
        {
            "description": "monthly_rate_gives_a_discount",
            "property": "monthly_rate",
            "input": {"hourly_rate": 67.0, "discount": 12.0},
            "expected": 10377,
        },
        {
            "description": "days_in_budget_is_budget_divided_by_daily_rate",
            "property": "days_in_budget",
            "input": {"budget": 1600, "hourly_rate": 50.0, "discount": 0.0},
            "expected": 4,
        },
        {
            "description": "days_in_budget_rounds_down_1",
            "property": "days_in_budget",
            "input": {"budget": 4390, "hourly_rate": 55.0, "discount": 0.0},
            "expected": 9,
        },
        {
            "description": "days_in_budget_rounds_down_2",
            "property": "days_in_budget",
            "input": {"budget": 4480, "hourly_rate": 55.0, "discount": 0.0},
            "expected": 10,
        },
        {
            "description": "days_in_budget_applies_discount",
            "property": "days_in_budget",
            "input": {"budget": 480, "hourly_rate": 70.0, "discount": 20.0},
            "expected": 1,
        },
    ]


def array_literal(cards):
    return str(cards).replace("[", "{").replace("]", "}").replace("'", "")


def unroll_args(args):
    if isinstance(args, (int, float)):
        return str(args)
    return str([*args.values()]).replace("[", "").replace("]", "")


def gen_func_body(prop, inp, expected):
    message = f"The function was called with arguments: {unroll_args(inp)}."
    if prop == "daily_rate":
        return f'TEST_ASSERT_EQUAL_DOUBLE_MESSAGE({expected}, {prop}({inp}), "{message}");\n'
    if prop == "apply_discount":
        return f'TEST_ASSERT_EQUAL_DOUBLE_MESSAGE({expected}, {prop}({inp["price"]}, {inp["discount"]}), "{message}");\n'
    if prop == "monthly_rate":
        return f'TEST_ASSERT_EQUAL_UINT64_MESSAGE({expected}, {prop}({inp["hourly_rate"]}, {inp["discount"]}), "{message}");\n'
    return f'TEST_ASSERT_EQUAL_UINT32_MESSAGE({expected}, {prop}({inp["budget"]}, {inp["hourly_rate"]}, {inp["discount"]}), "{message}");\n'
