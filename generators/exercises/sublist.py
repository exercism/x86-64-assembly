FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef enum {
    UNEQUAL = 0,
    EQUAL,
    SUBLIST,
    SUPERLIST,
} relation_t;

extern relation_t sublist(const int64_t *list_one, size_t list_one_count, const int64_t *list_two, size_t list_two_count);
"""


def gen_func_body(prop, inp, expected):
    list_one = inp["listOne"]
    list_two = inp["listTwo"]
    expected = expected.upper()

    call = "sublist("
    str_list = []
    if len(list_one) == 0:
        call += "NULL, 0"
    else:
        str_list.append(
            "const int64_t list_one[] = "
            + str(list_one).replace("[", "{").replace("]", "}")
            + ";"
        )
        call += "list_one, ARRAY_SIZE(list_one)"
    call += ", "
    if len(list_two) == 0:
        call += "NULL, 0"
    else:
        str_list.append(
            "const int64_t list_two[] = "
            + str(list_two).replace("[", "{").replace("]", "}")
            + ";"
        )
        call += "list_two, ARRAY_SIZE(list_two)"
    call += ")"

    str_list.append(f"TEST_ASSERT_EQUAL_INT({expected}, {call});\n")
    return "\n".join(str_list)
