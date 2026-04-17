FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

extern uint32_t get_box_weight(uint16_t count_first, uint16_t weight_first, uint16_t count_second, uint16_t weight_second);
extern uint8_t max_number_of_boxes(uint8_t box_height);
extern int32_t items_to_be_moved(uint32_t remaining_items, uint32_t items_in_box);
extern int64_t calculate_payment(uint64_t upfront_payment, uint32_t boxes_moved, uint32_t num_trips, uint32_t lost_items,
                                 uint64_t value_of_each_lost_item, uint8_t num_of_workers);
"""


def extra_cases():
    return [
        {
            "task_id": 1,
            "description": "weight_of_small_box",
            "property": "get_box_weight",
            "input": {
                "count_first": 30,
                "weight_first": 40,
                "count_second": 50,
                "weight_second": 20,
            },
            "expected": 2700,
        },
        {
            "task_id": 1,
            "description": "weight_of_medium_box",
            "property": "get_box_weight",
            "input": {
                "count_first": 15,
                "weight_first": 242,
                "count_second": 1100,
                "weight_second": 2,
            },
            "expected": 6330,
        },
        {
            "task_id": 1,
            "description": "weight_of_large_box",
            "property": "get_box_weight",
            "input": {
                "count_first": 12,
                "weight_first": 5600,
                "count_second": 133,
                "weight_second": 521,
            },
            "expected": 136993,
        },
        {
            "task_id": 2,
            "description": "max_stack_for_small_box",
            "property": "max_number_of_boxes",
            "input": 30,
            "expected": 10,
        },
        {
            "task_id": 2,
            "description": "max_stack_for_medium_box",
            "property": "max_number_of_boxes",
            "input": 85,
            "expected": 3,
        },
        {
            "task_id": 2,
            "description": "max_stack_for_large_box",
            "property": "max_number_of_boxes",
            "input": 182,
            "expected": 1,
        },
        {
            "task_id": 3,
            "description": "items_remaining_for_first_product",
            "property": "items_to_be_moved",
            "input": {"remaining_items": 76532, "items_in_box": 120},
            "expected": 76412,
        },
        {
            "task_id": 3,
            "description": "items_remaining_for_second_product",
            "property": "items_to_be_moved",
            "input": {"remaining_items": 1234876, "items_in_box": 666986},
            "expected": 567890,
        },
        {
            "task_id": 3,
            "description": "items_remaining_for_third_product",
            "property": "items_to_be_moved",
            "input": {"remaining_items": 217, "items_in_box": 217},
            "expected": 0,
        },
        {
            "task_id": 3,
            "description": "items_remaining_accounting_error",
            "property": "items_to_be_moved",
            "input": {"remaining_items": 156, "items_in_box": 723},
            "expected": -567,
        },
        {
            "task_id": 4,
            "description": "payment_few_lost_items",
            "property": "calculate_payment",
            "input": {
                "upfront_payment": 2000,
                "boxes_moved": 1000,
                "num_trips": 5,
                "lost_items": 21,
                "value_of_each_lost_item": 2,
                "num_of_workers": 1,
            },
            "expected": 2029,
        },
        {
            "task_id": 4,
            "description": "no_payment_too_many_lost_items",
            "property": "calculate_payment",
            "input": {
                "upfront_payment": 2000,
                "boxes_moved": 598,
                "num_trips": 2,
                "lost_items": 120,
                "value_of_each_lost_item": 45,
                "num_of_workers": 4,
            },
            "expected": -794,
        },
        {
            "task_id": 4,
            "description": "payment_many_boxes",
            "property": "calculate_payment",
            "input": {
                "upfront_payment": 57412,
                "boxes_moved": 163214,
                "num_trips": 183,
                "lost_items": 1931,
                "value_of_each_lost_item": 185,
                "num_of_workers": 216,
            },
            "expected": 2123,
        },
        {
            "task_id": 4,
            "description": "no_payment_everything_upfront",
            "property": "calculate_payment",
            "input": {
                "upfront_payment": 22975,
                "boxes_moved": 4523,
                "num_trips": 6,
                "lost_items": 120,
                "value_of_each_lost_item": 8,
                "num_of_workers": 5,
            },
            "expected": 0,
        },
    ]


def unroll_args(args):
    if isinstance(args, (int, float)):
        return str(args)
    return str([*args.values()]).replace("[", "").replace("]", "")


def gen_func_body(prop, inp, expected):
    plural = "s" if isinstance(inp, dict) and len(inp) > 1 else ""
    message = f"The function was called with argument{plural}: {unroll_args(inp)}."
    if prop == "get_box_weight":
        return (
            f"TEST_ASSERT_EQUAL_UINT32_MESSAGE({expected}, {prop}"
            f"({inp['count_first']}, {inp['weight_first']}, {inp['count_second']}, {inp['weight_second']}), "
            f'"{message}");\n'
        )
    if prop == "max_number_of_boxes":
        return f'TEST_ASSERT_EQUAL_UINT8_MESSAGE({expected}, {prop}({inp}), "{message}");\n'
    if prop == "items_to_be_moved":
        return (
            f"TEST_ASSERT_EQUAL_INT64_MESSAGE({expected}, {prop}"
            f"({inp['remaining_items']}, {inp['items_in_box']}), "
            f'"{message}");\n'
        )
    return (
        f"TEST_ASSERT_EQUAL_INT64_MESSAGE({expected}, {prop}"
        f"({inp['upfront_payment']}, {inp['boxes_moved']}, {inp['num_trips']}, "
        f"{inp['lost_items']}, {inp['value_of_each_lost_item']}, {inp['num_of_workers']}), "
        f'"{message}");\n'
    )
