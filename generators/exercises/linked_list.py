FUNC_PROTO = """\
#include <stddef.h>
#include "vendor/unity.h"

// constructs a new (empty) list - called during setup
// recommend : don't rely on `malloc`/`calloc`
extern void list_create(void);

// counts the items on a list
extern size_t list_count(void);

// inserts item at back of a list
extern void list_push(int item_data);

// removes item from back of a list
extern int list_pop(void);

// inserts item at front of a list
extern void list_unshift(int item_data);

// removes item from front of a list
extern int list_shift(void);

// deletes a node that holds the matching data
extern void list_delete(int data);

// destroys an entire list - called during teardown
// recommend : clear pointer and values for this run
extern void list_destroy(void);

"""


def gen_func_body(prop, inp, expected):
    body = ""
    for op in inp.get("operations", []):
        if "expected" in op:
            body += f"TEST_ASSERT_EQUAL({op['expected']}, list_{op['operation']}());\n"
        else:
            if "value" in op:
                body += f"list_{op['operation']}({op['value']});\n"
            else:
                body += f"list_{op['operation']}();\n"
    return body
