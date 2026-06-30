FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>
#include <stdalign.h>

enum nucleotide {
    ADENINE = 0,
    CYTOSINE,
    GUANINE,
    THYMINE
};

extern void nucleotide_counts(const char strand[], int64_t counts[]);
"""


def describe(case):
    return case["description"].replace("-", " ")


def gen_func_body(prop, inp, expected):
    strand = inp["strand"]
    counts = (
        [-1, -1, -1, -1]
        if "error" in expected
        else [expected["A"], expected["C"], expected["G"], expected["T"]]
    )
    str_list = []
    str_list.append(f'alignas(16) const char strand[] = "{strand}";')
    str_list.append("int64_t counts[4];")
    str_list.append(f"{prop}(strand, counts);")
    str_list.append(f"TEST_ASSERT_EQUAL_INT64({counts[0]}, counts[ADENINE]);")
    str_list.append(f"TEST_ASSERT_EQUAL_INT64({counts[1]}, counts[CYTOSINE]);")
    str_list.append(f"TEST_ASSERT_EQUAL_INT64({counts[2]}, counts[GUANINE]);")
    str_list.append(f"TEST_ASSERT_EQUAL_INT64({counts[3]}, counts[THYMINE]);")
    return "\n".join(str_list)
