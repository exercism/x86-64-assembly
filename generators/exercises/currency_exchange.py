FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

enum currency_t {
    GBP,
    EUR,
    JPY,
    AUD,
    BRL,
    CNY,
    CAD,
    INR
};

static const double value_in_US_dollars[] = {
    1.33329, 1.16443, 0.00654374, 0.650888,
    0.185577, 0.140420, 0.714142, 0.0113863
};

extern void stringify_currency(char *buffer, enum currency_t currency);
extern double exchange_rate(enum currency_t domestic_currency, enum currency_t foreign_currency, const double *value_in_US_dollars);
extern uint64_t get_value_of_bills(unsigned long long denomination, unsigned short number_of_bills);
extern unsigned int get_number_of_bills(float amount, unsigned long long denomination);
extern uint32_t exchangeable_value(float budget, double exchange_rate, uint8_t spread, unsigned long long denomination);
"""


def extra_cases():
    return [
        {
            "description": "stringify_currencies",
            "property": "stringify_currency",
            "input": ["GBP", "AUD", "JPY", "CNY", "EUR", "INR", "CAD", "BRL"],
            "expected": ["GBP", "AUD", "JPY", "CNY", "EUR", "INR", "CAD", "BRL"],
        },
        {
            "description": "exchange_rates",
            "property": "exchange_rate",
            "input": [("JPY", "GBP"), ("CAD", "INR"), ("BRL", "AUD"), ("EUR", "CNY")],
            "expected": [
                1.33329 / 0.00654374,
                0.0113863 / 0.714142,
                0.650888 / 0.185577,
                0.140420 / 1.16443,
            ],
        },
        {
            "description": "value_of_bills",
            "property": "get_value_of_bills",
            "input": [(5000000, 1280), (50, 360), (200, 200)],
            "expected": [6400000000, 18000, 40000],
        },
        {
            "description": "number_of_bills",
            "property": "get_number_of_bills",
            "input": [(163271, 50000), (54361, 1000), (127.99, 2)],
            "expected": [3, 54, 63],
        },
        {
            "description": "exchangeable_values",
            "property": "exchangeable_value",
            "input": [
                (100000, 10.61, 10, 1),
                (1500, 0.84, 25, 40),
                (470000, 1050, 30, 10000000000),
                (425.33, 0.0009, 30, 700),
            ],
            "expected": [8568, 1400, 0, 363300],
        },
    ]


def array_literal(cards):
    return str(cards).replace("[", "{").replace("]", "}").replace("'", "")


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "stringify_currency":
        str_list.append("char buffer[4];")
        for currency in inp:
            str_list.append(f"{prop}(buffer, {currency});")
            str_list.append(
                f'TEST_ASSERT_EQUAL_STRING_MESSAGE("{currency}", buffer, "Currency: {currency}.");'
            )
    elif prop == "exchange_rate":
        for i, (currency1, currency2) in enumerate(inp):
            str_list.append(
                f'TEST_ASSERT_EQUAL_DOUBLE_MESSAGE({expected[i]}, {prop}({currency1}, {currency2}, value_in_US_dollars), "Domestic Currency: {currency1}; Foreign Currency: {currency2}.");'
            )
    elif prop == "get_value_of_bills":
        for i, (denomination, number) in enumerate(inp):
            str_list.append(
                f'TEST_ASSERT_EQUAL_UINT64_MESSAGE({expected[i]}, {prop}({denomination}, {number}), "Denomination: {denomination}; number of bills: {number}.");'
            )
    elif prop == "get_number_of_bills":
        for i, (amount, denomination) in enumerate(inp):
            str_list.append(
                f'TEST_ASSERT_EQUAL_UINT32_MESSAGE({expected[i]}, {prop}({amount}, {denomination}), "Amount: {amount}; Denomination: {denomination}.");'
            )
    else:
        for i, (budget, rate, spread, denomination) in enumerate(inp):
            str_list.append(
                f'TEST_ASSERT_EQUAL_UINT32_MESSAGE({expected[i]}, {prop}({budget}, {rate}, {spread}, {denomination}), "Budget: {budget}; Exchange Rate: {rate}; Spread: {spread}; Denomination: {denomination}.");'
            )
    return "\n".join(str_list)
