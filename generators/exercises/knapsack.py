FUNC_PROTO = """\
#include "stdint.h"
#include "vendor/unity.h"

typedef struct {
    uint32_t value;
    uint32_t weight;
} Item;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern uint32_t maximumValue(Item *items, uint32_t count, uint32_t maxWeight);
"""


def gen_func_body(prop, inp, expected):
    count = len(inp["items"])
    if count == 0:
        return f"TEST_ASSERT_EQUAL_UINT32({expected}, maximumValue(NULL, {count}, {inp['maximumWeight']}));\n"

    else:
        item_list = []
        for i in inp["items"]:
            item_list.append(f"    {{{i['value']}, {i['weight']}}}")

        text = f"Item items[{count}] = {{\n"
        text += ",\n".join(item_list)

        text += "\n};\n"
        text += f"TEST_ASSERT_EQUAL_UINT32({expected}, maximumValue(items, ARRAY_SIZE(items), {inp['maximumWeight']}));\n"
    return text
