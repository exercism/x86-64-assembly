FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdalign.h>

#define BUFFER_SIZE 16

extern int distance(const char strand1[], const char strand2[]);
"""


def gen_func_body(prop, inp, expected):
    strand1 = inp["strand1"]
    strand2 = inp["strand2"]
    if len(strand1) >= 16 or len(strand2) >= 16:
        return ""
    if type(expected) is not int:
        expected = -1
    str_list = []
    str_list.append(f'alignas(16) const char strand1[BUFFER_SIZE] = "{strand1}";')
    str_list.append(f'alignas(16) const char strand2[BUFFER_SIZE] = "{strand2}";')
    str_list.append(f"TEST_ASSERT_EQUAL_INT({expected}, {prop}(strand1, strand2));")
    return "\n".join(str_list)
