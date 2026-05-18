FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>
#include <stdlib.h>

#define BUFFER_SIZE 32
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

typedef struct box_t box_t;

typedef enum {
    NONE = 0,
    VALUE,
    BOX
} type_t;

typedef struct {
    size_t size;
    box_t *boxes;
} array_t;

struct box_t {
    type_t tag;
    union {
        int64_t value;
        array_t array;
    } contents;
};

extern size_t flatten(int64_t buffer[], const box_t *box);
"""


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    count = 1
    str_list = []
    str_list.append("void *objs[100];")
    str_list.append("size_t num_obj = 0;")
    str_list.append("")
    str_list.append("box_t box;")

    def process_box(box, prefix):
        nonlocal str_list, count
        if box is None:
            str_list.append(f"{prefix}.tag = NONE;")
        elif type(box) is list:
            str_list.append(f"{prefix}.tag = BOX;")
            str_list.append(f"{prefix}.contents.array.size = {len(box)};")
            if box:
                name = f"c{count}"
                count += 1
                str_list.append(
                    f"{prefix}.contents.array.boxes = calloc({len(box)}, sizeof(box_t));"
                )
                str_list.append(
                    f"objs[num_obj++] = (void*){prefix}.contents.array.boxes;"
                )
                str_list.append("")
                str_list.append(f"box_t *{name} = {prefix}.contents.array.boxes;")
                for i, child in enumerate(box):
                    process_box(child, f"{name}[{i}]")
                str_list.append("")
        elif isinstance(box, int):
            str_list.append(f"{prefix}.tag = VALUE;")
            str_list.append(f"{prefix}.contents.value = {box};")

    process_box(inp["array"], "box")
    str_list.append("")
    str_list.append("alignas(32) int64_t buffer[BUFFER_SIZE];")
    str_list.append(f"const size_t length = {prop}(buffer, &box);")
    str_list.append("for (size_t i = num_obj; i-- > 0; ) {")
    str_list.append("free(objs[i]);")
    str_list.append("objs[i] = NULL;")
    str_list.append("}")
    str_list.append("")
    if len(expected) > 0:
        str_list.append(f"const int64_t expected[] = {array_literal(expected)};")
        str_list.append("TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);")
        str_list.append(
            "TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));"
        )
    else:
        str_list.append("TEST_ASSERT_EQUAL_UINT64(0, length);")
    return "\n".join(str_list)
