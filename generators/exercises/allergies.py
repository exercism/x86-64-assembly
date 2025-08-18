FUNC_PROTO = """\
#include "vendor/unity.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

enum item {
    EGGS,
    PEANUTS,
    SHELLFISH,
    STRAWBERRIES,
    TOMATOES,
    CHOCOLATE,
    POLLEN,
    CATS,
    MAX_ITEMS
};

struct item_list {
    int size;
    enum item items[MAX_ITEMS];
};

extern int allergic_to(enum item item, unsigned int score);
extern void list(unsigned int score, struct item_list *list);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    score = inp["score"]
    if prop == "allergic_to":
        item = inp["item"].upper()
        if expected:
            str_list.append(f"TEST_ASSERT_TRUE({prop}({item}, {score}));\n")
        else:
            str_list.append(f"TEST_ASSERT_FALSE({prop}({item}, {score}));\n")
    elif prop == "list":
        item_list = list(map(lambda item: str(item).upper(), expected))
        item_list = str(item_list).replace("'", "")
        item_list = item_list.replace("[", "{")
        item_list = item_list.replace("]", "}")
        if expected:
            str_list.append(f"int expected[] = {item_list};\n")
        str_list.append("struct item_list item_list;\n\n")
        str_list.append(f"{prop}({score}, &item_list);\n")
        if expected:
            str_list.append(
                "TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), item_list.size);\n"
            )
            str_list.append(
                "TEST_ASSERT_EQUAL_INT_ARRAY(expected, item_list.items, item_list.size);\n"
            )
        else:
            str_list.append("TEST_ASSERT_EQUAL_INT(0, item_list.size);\n")
    return "".join(str_list)
