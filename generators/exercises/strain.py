FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdbool.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef bool(*predicate_t)(const void*);

extern size_t keep(void *elems, size_t elem_size, size_t num_elems, predicate_t fn);
extern size_t discard(void *elems, size_t elem_size, size_t num_elems, predicate_t fn);

static bool always(const void *x) {
    (void)x;
    return true;
}

static bool never(const void *x) {
    (void)x;
    return false;
}

static bool is_even(const void *x) {
    const int *y = x;
    return (*y & 1) == 0;
}

static bool is_odd(const void *x) {
    const int *y = x;
    return (*y & 1) == 1;
}

static bool starts_with_z(const void *x) {
    const char * const *y = x;
    for (int i = 0; *(*y + i); ++i) {
        if (*(*y + i) == 'z') return true;
    }
    return false;
}

static bool contains_5(const void *x) {
    const int *y = x;
    for (int i = 0; i < 3; ++i) {
        if (y[i] == 5) return true;
    }
    return false;
}
"""


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}").replace("'", '"')


def gen_func_body(prop, inp, expected):
    lst = inp["list"]
    pred = inp["predicate"]
    str_list = []
    if pred == "fn(x) -> starts_with(x, 'z')":
        str_list.append("void *ptr = NULL;")
        str_list.append("size_t elem_size = sizeof(const char*);")
        str_list.append("size_t num_elems = 0;")
        if lst:
            str_list.append(f"const char *input[] = {array_literal(lst)};")
            str_list.append("ptr = (void*)input;")
            str_list.append("num_elems = ARRAY_SIZE(input);")
        str_list.append(
            f"const size_t size = {prop}(ptr, elem_size, num_elems, starts_with_z);"
        )
        if expected:
            str_list.append(f"const char *result[] = {array_literal(expected)};")
            str_list.append("TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(result), size);")
            str_list.append(
                "TEST_ASSERT_EQUAL_STRING_ARRAY(result, input, ARRAY_SIZE(result));"
            )
        else:
            str_list.append("TEST_ASSERT_EQUAL_UINT64(0, size);")
    elif pred == "fn(x) -> contains(x, 5)":
        str_list.append("void *ptr = NULL;")
        str_list.append("size_t elem_size = 3 * sizeof(const int);")
        str_list.append("size_t num_elems = 0;")
        if lst:
            str_list.append(f"const int input[][3] = {array_literal(lst)};")
            str_list.append("ptr = (void*)input;")
            str_list.append("num_elems = ARRAY_SIZE(input);")
        str_list.append(
            f"const size_t size = {prop}(ptr, elem_size, num_elems, contains_5);"
        )
        if expected:
            str_list.append(f"const int result[][3] = {array_literal(expected)};")
            str_list.append("TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(result), size);")
            str_list.append("for (size_t i = 0; i < ARRAY_SIZE(result); ++i) {")
            str_list.append("TEST_ASSERT_EQUAL_INT_ARRAY(result[i], input[i], 3);")
            str_list.append("}")
        else:
            str_list.append("TEST_ASSERT_EQUAL_UINT64(0, size);")
    else:
        str_list.append("void *ptr = NULL;")
        str_list.append("size_t elem_size = sizeof(int);")
        str_list.append("size_t num_elems = 0;")
        if lst:
            str_list.append(f"int input[] = {array_literal(lst)};")
            str_list.append("ptr = (void*)input;")
            str_list.append("num_elems = ARRAY_SIZE(input);")
        if pred == "fn(x) -> true":
            pred = "always"
        elif pred == "fn(x) -> false":
            pred = "never"
        elif pred == "fn(x) -> x % 2 == 1":
            pred = "is_odd"
        elif pred == "fn(x) -> x % 2 == 0":
            pred = "is_even"
        str_list.append(
            f"const size_t size = {prop}(ptr, elem_size, num_elems, {pred});"
        )
        if expected:
            str_list.append(f"const int result[] = {array_literal(expected)};")
            str_list.append("TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(result), size);")
            str_list.append(
                "TEST_ASSERT_EQUAL_INT_ARRAY(result, input, ARRAY_SIZE(result));"
            )
        else:
            str_list.append("TEST_ASSERT_EQUAL_UINT64(0, size);")
    return "\n".join(str_list)
