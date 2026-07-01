FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdbool.h>
#include <stddef.h>

#define BUFFER_SIZE 16

#define ARRAY_SIZE(x) ((int)(sizeof(x) / sizeof((x)[0])))

extern int append(const int *list1, const int list1_size, const int *list2, const int list2_size,
                  int *result);
extern int filter(const int *list, const int list_size, bool (*filter_predicate)(int), int *result);
extern int map(const int *list, const int list_size, int (*map_transform)(int), int *result);
extern int foldl(const int *list, const int list_size, int initial, int (*fold_accumulate)(int, int));
extern int foldr(const int *list, const int list_size, int initial, int (*fold_accumulate)(int, int));
extern int reverse(const int *list, const int list_size, int *result);

static bool is_odd(int x) {
    return x % 2 == 1;
}

static int plus_one(int x) {
    return x + 1;
}

static int multiply(int acc, int el) {
    return el * acc;
}

static int add(int acc, int el) {
    return el + acc;
}

static int divide(int acc, int el) {
    return acc == 0 ? 0 : el / acc;
}
"""


def array_literal(numbers):
    return "{" + ", ".join(str(d) for d in numbers) + "}"


def describe(case):
    description = case["description"]
    property = case["property"]
    return f"{property} {description}"


def gen_func_body(prop, inp, expected):
    str_list = []

    if prop in ["foldl", "foldr"]:
        initial = inp["initial"]

    function = None
    if prop not in ["append", "reverse"]:
        function = inp["function"]
        if function == "(x) -> x modulo 2 == 1":
            function = "is_odd"
        if function == "(x) -> x + 1":
            function = "plus_one"

        if function == "(acc, el) -> el * acc":
            function = "multiply"
        if function == "(acc, el) -> el + acc":
            function = "add"
        if function == "(acc, el) -> el / acc":
            function = "divide"

    if prop == "append":
        list1 = inp["list1"]
        list2 = inp["list2"]
        if len(list1) > 0:
            str_list.append(f"const int list1[] = {array_literal(list1)};\n")
            list1_with_count = "list1, ARRAY_SIZE(list1)"
        else:
            list1_with_count = "NULL, 0"
        if len(list2) > 0:
            str_list.append(f"const int list2[] = {array_literal(list2)};\n")
            list2_with_count = "list2, ARRAY_SIZE(list2)"
        else:
            list2_with_count = "NULL, 0"
    else:
        list_ = inp["list"]
        if function == "divide":
            initial = 5
            list_ = [2, 5]
            if prop == "foldl":
                expected = 0
            else:
                expected = 2

        if len(list_) > 0:
            str_list.append(f"const int list[] = {array_literal(list_)};\n")
            list_with_count = "list, ARRAY_SIZE(list)"
        else:
            list_with_count = "NULL, 0"

    match prop:
        case "append":
            str_list.append("int buffer[BUFFER_SIZE];\n")
            call = f"{prop}({list1_with_count}, {list2_with_count}, buffer)"
        case "filter" | "map":
            str_list.append("int buffer[BUFFER_SIZE];\n")
            call = f"{prop}({list_with_count}, {function}, buffer)"
        case "foldl" | "foldr":
            call = f"{prop}({list_with_count}, {initial}, {function})"
        case "reverse":
            str_list.append("int buffer[BUFFER_SIZE];\n")
            call = f"{prop}({list_with_count}, buffer)"

    if isinstance(expected, list):
        if len(expected) == 0:
            str_list.append(f"TEST_ASSERT_EQUAL_INT(0, {call});\n")
        else:
            expected = array_literal(expected)
            str_list.append(f"const int expected[] = {expected};\n")
            str_list.append(f"TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), {call});\n")
            str_list.append(
                "TEST_ASSERT_EQUAL_INT_ARRAY(expected, buffer, ARRAY_SIZE(expected));\n"
            )
    else:
        str_list.append(f"TEST_ASSERT_EQUAL_INT({expected}, {call});\n")

    return "".join(str_list)
