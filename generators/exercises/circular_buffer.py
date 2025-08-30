FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

extern void create_buffer(size_t capacity);
extern bool read_buffer(int32_t *output);
extern bool write_buffer(int32_t input);
extern void clear_buffer(void);
extern void overwrite_buffer(int32_t input);
extern void delete_buffer(void);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    capacity = inp["capacity"]
    str_list.append(f"create_buffer({capacity});\n")
    index = 1
    for op in inp["operations"]:
        if op["operation"] == "read":
            str_list.append(f"int32_t output_{index};\n")
            str_list.append(
                f"TEST_ASSERT_EQUAL({str(op['should_succeed']).lower()}, {op['operation']}_buffer(&output_{index}));\n"
            )
            if op["should_succeed"]:
                str_list.append(
                    f"TEST_ASSERT_EQUAL({op['expected']}, output_{index});\n"
                )
            index += 1
        elif op["operation"] == "write":
            str_list.append(
                f"TEST_ASSERT_EQUAL({str(op['should_succeed']).lower()}, {op['operation']}_buffer({op['item']}));\n"
            )
        elif op["operation"] == "overwrite":
            str_list.append(f"{op['operation']}_buffer({op['item']});\n")
        else:
            str_list.append(f"{op['operation']}_buffer();\n")
    str_list.append("delete_buffer();\n")
    return "".join(str_list)
