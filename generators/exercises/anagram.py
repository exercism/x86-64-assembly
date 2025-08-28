FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>

extern void find_anagrams(int *is_anagram, const char *candidates[], size_t num_candidates, const char *subject);
"""


def gen_func_body(prop, inp, expected):
    if prop != "find_anagrams":
        raise ValueError("Only property 'find_anagrams' is supported")
    str_list = []
    subject = inp["subject"]
    candidates = inp["candidates"]
    num_candidates = len(candidates)
    candidates_list = ", ".join(f'"{c}"' for c in candidates)
    str_list.append(f"const char *candidates[] = {{{candidates_list}}};\n")

    expected_bools = ["1" if c in expected else "0" for c in candidates]
    str_list.append(
        f"const int expected[{num_candidates}] = {{{', '.join(expected_bools)}}};\n"
    )
    str_list.append(f"int is_anagram[{num_candidates}] = {{0}};\n")
    str_list.append("\n")
    str_list.append(
        f'find_anagrams(is_anagram, candidates, {num_candidates}, "{subject}");\n'
    )
    str_list.append("\n")
    str_list.append(
        f"TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, {num_candidates});\n"
    )
    return "".join(str_list)
