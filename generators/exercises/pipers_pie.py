FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

extern uint64_t largest_portion(uint64_t a, uint64_t b);
extern uint64_t double_factorial(uint32_t n);
extern double pipers_pi(uint32_t n);
"""


def extra_cases():
    return [
        {
            "task_id": 1,
            "description": "largest_portion_small_coprime",
            "property": "largest_portion",
            "input": [17, 13],
            "expected": 1,
        },
        {
            "task_id": 1,
            "description": "largest_portion_b_divides_a",
            "property": "largest_portion",
            "input": [48, 12],
            "expected": 12,
        },
        {
            "task_id": 1,
            "description": "largest_portion_equal_inputs",
            "property": "largest_portion",
            "input": [100, 100],
            "expected": 100,
        },
        {
            "task_id": 1,
            "description": "largest_portion_first_is_zero",
            "property": "largest_portion",
            "input": [0, 42],
            "expected": 42,
        },
        {
            "task_id": 1,
            "description": "largest_portion_second_is_zero",
            "property": "largest_portion",
            "input": [42, 0],
            "expected": 42,
        },
        {
            "task_id": 1,
            "description": "largest_portion_both_zero",
            "property": "largest_portion",
            "input": [0, 0],
            "expected": 0,
        },
        {
            "task_id": 1,
            "description": "largest_portion_large_coprime",
            "property": "largest_portion",
            "input": [1000000007, 998244353],
            "expected": 1,
        },
        {
            "task_id": 1,
            "description": "largest_portion_fibonacci_pair",
            "property": "largest_portion",
            "input": [12200160415121876738, 7540113804746346429],
            "expected": 1,
        },
        {
            "task_id": 2,
            "description": "double_factorial_zero",
            "property": "double_factorial",
            "input": 0,
            "expected": 1,
        },
        {
            "task_id": 2,
            "description": "double_factorial_one",
            "property": "double_factorial",
            "input": 1,
            "expected": 1,
        },
        {
            "task_id": 2,
            "description": "double_factorial_four",
            "property": "double_factorial",
            "input": 4,
            "expected": 8,
        },
        {
            "task_id": 2,
            "description": "double_factorial_ten",
            "property": "double_factorial",
            "input": 10,
            "expected": 3840,
        },
        {
            "task_id": 2,
            "description": "double_factorial_eleven",
            "property": "double_factorial",
            "input": 11,
            "expected": 10395,
        },
        {
            "task_id": 2,
            "description": "double_factorial_thirty_two",
            "property": "double_factorial",
            "input": 32,
            "expected": 1371195958099968000,
        },
        {
            "task_id": 2,
            "description": "double_factorial_thirty_three",
            "property": "double_factorial",
            "input": 33,
            "expected": 6332659870762850625,
        },
        {
            "task_id": 2,
            "description": "double_factorial_uint64_wrap_no_stack_overflow",
            "property": "double_factorial",
            "input": 10000000,
            "expected": 0,
        },
        {
            "task_id": 3,
            "description": "pipers_pi_zero_terms",
            "property": "pipers_pi",
            "input": 0,
            "expected": 2.0,
        },
        {
            "task_id": 3,
            "description": "pipers_pi_three_terms",
            "property": "pipers_pi",
            "input": 3,
            "expected": 3.047619,
        },
        {
            "task_id": 3,
            "description": "pipers_pi_five_terms",
            "property": "pipers_pi",
            "input": 5,
            "expected": 3.121500,
        },
        {
            "task_id": 3,
            "description": "pipers_pi_ten_terms",
            "property": "pipers_pi",
            "input": 10,
            "expected": 3.141106,
        },
        {
            "task_id": 3,
            "description": "pipers_pi_fifteen_terms",
            "property": "pipers_pi",
            "input": 15,
            "expected": 3.141579,
        },
    ]


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "largest_portion":
        a = inp[0]
        b = inp[1]
        message = f"Passed arguments are: {a}, {b}"
        str_list.append(f"uint64_t a = {a}ULL, b = {b}ULL;")
        str_list.append(
            f'TEST_ASSERT_EQUAL_UINT64_MESSAGE({expected}, {prop}(a, b), "{message}");'
        )
    elif prop == "double_factorial":
        message = f"Passed argument is: {inp}"
        str_list.append(f"uint32_t n = {inp};")
        str_list.append(
            f'TEST_ASSERT_EQUAL_UINT64_MESSAGE({expected}, {prop}(n), "{message}");'
        )
    else:
        message = f"Passed argument is: {inp}"
        str_list.append(f"uint32_t n = {inp};")
        str_list.append(
            f'TEST_ASSERT_EQUAL_DOUBLE_MESSAGE({expected}, {prop}(n), "{message}");'
        )
    return "\n".join(str_list)
