FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern uint32_t time_to_make_juice(uint32_t ID);
extern uint32_t time_to_prepare(const uint32_t *IDs, uint32_t number_of_IDs);
extern uint32_t limes_to_cut(uint32_t wedges_needed, const uint8_t *limes, uint32_t number_of_limes);
extern uint32_t remaining_orders(uint32_t time_left, const uint32_t *IDs);
"""


def extra_cases():
    return [
        {
            "description": "time_to_make_pure_strawberry_joy",
            "property": "time_to_make_juice",
            "input": 1,
            "expected": 1,
        },
        {
            "description": "time_to_make_energizer",
            "property": "time_to_make_juice",
            "input": 2,
            "expected": 3,
        },
        {
            "description": "time_to_make_green_garden",
            "property": "time_to_make_juice",
            "input": 3,
            "expected": 3,
        },
        {
            "description": "time_to_make_tropical_island",
            "property": "time_to_make_juice",
            "input": 4,
            "expected": 4,
        },
        {
            "description": "time_to_make_all_or_nothing",
            "property": "time_to_make_juice",
            "input": 5,
            "expected": 5,
        },
        {
            "description": "time_to_make_feel_good",
            "property": "time_to_make_juice",
            "input": 6,
            "expected": 4,
        },
        {
            "description": "time_to_make_todays_special",
            "property": "time_to_make_juice",
            "input": 7,
            "expected": 7,
        },
        {
            "description": "time_to_make_clients_choice",
            "property": "time_to_make_juice",
            "input": 8,
            "expected": 10,
        },
        {
            "description": "time_to_prepare_one_order",
            "property": "time_to_prepare",
            "input": {"IDs": [4], "number_of_IDs": 1},
            "expected": 4,
        },
        {
            "description": "time_to_prepare_a_few_orders",
            "property": "time_to_prepare",
            "input": {"IDs": [2, 5, 6], "number_of_IDs": 3},
            "expected": 12,
        },
        {
            "description": "time_to_prepare_many_orders",
            "property": "time_to_prepare",
            "input": {"IDs": [7, 4, 1, 5, 6, 6, 8, 2, 7], "number_of_IDs": 9},
            "expected": 7 + 4 + 1 + 5 + 4 + 4 + 10 + 3 + 7,
        },
        {
            "description": "limes_to_cut_one_small",
            "property": "limes_to_cut",
            "input": {"wedges_needed": 6, "limes": ["S"], "number_of_limes": 1},
            "expected": 1,
        },
        {
            "description": "limes_to_cut_one_medium",
            "property": "limes_to_cut",
            "input": {"wedges_needed": 8, "limes": ["M"], "number_of_limes": 1},
            "expected": 1,
        },
        {
            "description": "limes_to_cut_one_large",
            "property": "limes_to_cut",
            "input": {"wedges_needed": 10, "limes": ["L"], "number_of_limes": 1},
            "expected": 1,
        },
        {
            "description": "limes_to_cut_two_smalls",
            "property": "limes_to_cut",
            "input": {
                "wedges_needed": 12,
                "limes": ["S", "S", "M"],
                "number_of_limes": 3,
            },
            "expected": 2,
        },
        {
            "description": "limes_to_cut_one_small_one_medium",
            "property": "limes_to_cut",
            "input": {
                "wedges_needed": 14,
                "limes": ["S", "M", "S", "L"],
                "number_of_limes": 4,
            },
            "expected": 2,
        },
        {
            "description": "limes_to_cut_one_small_one_large",
            "property": "limes_to_cut",
            "input": {
                "wedges_needed": 16,
                "limes": ["S", "L", "M", "S"],
                "number_of_limes": 4,
            },
            "expected": 2,
        },
        {
            "description": "limes_to_cut_two_mediums",
            "property": "limes_to_cut",
            "input": {
                "wedges_needed": 16,
                "limes": ["M", "M", "S", "L"],
                "number_of_limes": 4,
            },
            "expected": 2,
        },
        {
            "description": "limes_to_cut_one_medium_one_large",
            "property": "limes_to_cut",
            "input": {
                "wedges_needed": 18,
                "limes": ["M", "L", "M", "S"],
                "number_of_limes": 4,
            },
            "expected": 2,
        },
        {
            "description": "limes_to_cut_not_exact",
            "property": "limes_to_cut",
            "input": {
                "wedges_needed": 25,
                "limes": ["S", "S", "L", "M", "S"],
                "number_of_limes": 5,
            },
            "expected": 4,
        },
        {
            "description": "limes_to_cut_many_needed",
            "property": "limes_to_cut",
            "input": {
                "wedges_needed": 99,
                "limes": [
                    "S",
                    "M",
                    "L",
                    "M",
                    "L",
                    "S",
                    "L",
                    "M",
                    "S",
                    "M",
                    "S",
                    "L",
                    "M",
                    "L",
                    "S",
                ],
                "number_of_limes": 15,
            },
            "expected": 13,
        },
        {
            "description": "remaining_orders_one_order",
            "property": "remaining_orders",
            "input": {
                "time_left": 1,
                "IDs": [1, 5, 3],
            },
            "expected": 1,
        },
        {
            "description": "remaining_orders_two_orders",
            "property": "remaining_orders",
            "input": {
                "time_left": 5,
                "IDs": [6, 1, 3],
            },
            "expected": 2,
        },
        {
            "description": "remaining_orders_three_orders",
            "property": "remaining_orders",
            "input": {
                "time_left": 12,
                "IDs": [2, 5, 6, 7],
            },
            "expected": 3,
        },
        {
            "description": "remaining_orders_work_longer",
            "property": "remaining_orders",
            "input": {
                "time_left": 9,
                "IDs": [6, 8, 3],
            },
            "expected": 2,
        },
        {
            "description": "remaining_orders_many_orders_left",
            "property": "remaining_orders",
            "input": {
                "time_left": 7,
                "IDs": [1, 5, 8, 2, 3, 1, 2, 7, 5, 6, 4],
            },
            "expected": 3,
        },
    ]


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}").replace('"', "'")


def unroll_args(args):
    if isinstance(args, (int, float)):
        return str(args)
    if isinstance(args, dict):
        return str([*args.values()]).replace("[", "").replace("]", "")
    return str(args).replace("[", "").replace("]", "")


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "time_to_make_juice":
        message = f"The function was called with arguments: {unroll_args(inp)}."
        str_list.append(
            f'TEST_ASSERT_EQUAL_UINT32_MESSAGE({expected}, {prop}({inp}), "{message}");'
        )
    elif prop == "time_to_prepare":
        message = f"The function was called with arguments: {unroll_args(inp['IDs'])}."
        str_list.append(f"const uint32_t IDs[] = {array_literal(inp['IDs'])};")
        str_list.append(
            f'TEST_ASSERT_EQUAL_UINT32_MESSAGE({expected}, {prop}(IDs, ARRAY_SIZE(IDs)), "{message}");'
        )
    elif prop == "limes_to_cut":
        message = f"Number of wedges needed: {inp['wedges_needed']}. Limes: {unroll_args(inp['limes'])}."
        str_list.append(f"const uint8_t limes[] = {array_literal(inp['limes'])};")
        str_list.append(
            f'TEST_ASSERT_EQUAL_UINT32_MESSAGE({expected}, {prop}({inp["wedges_needed"]}, limes, ARRAY_SIZE(limes)), "{message}");'
        )
    else:
        message = (
            f"Time left: {inp['time_left']}. Order IDs: {unroll_args(inp['IDs'])}."
        )
        str_list.append(f"const uint32_t IDs[] = {array_literal(inp['IDs'])};")
        str_list.append(
            f'TEST_ASSERT_EQUAL_UINT32_MESSAGE({expected}, {prop}({inp["time_left"]}, IDs), "{message}");'
        )
    return "\n".join(str_list)
