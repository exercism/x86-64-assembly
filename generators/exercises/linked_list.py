FUNC_PROTO = """\
#include <stddef.h>
#include "vendor/unity.h"

typedef int ll_data_t;

struct list_node {
   struct list_node *prev, *next;
   ll_data_t data;
};

struct list {
   struct list_node *first, *last;
};

// constructs a new (empty) list
extern struct list *list_create(void);

// counts the items on a list
extern size_t list_count(const struct list *list);

// inserts item at back of a list
extern void list_push(struct list *list, ll_data_t item_data);

// removes item from back of a list
extern ll_data_t list_pop(struct list *list);

// inserts item at front of a list
extern void list_unshift(struct list *list, ll_data_t item_data);

// removes item from front of a list
extern ll_data_t list_shift(struct list *list);

// deletes a node that holds the matching data
extern void list_delete(struct list *list, ll_data_t data);

// destroys an entire list
// list will be a dangling pointer after calling this method on it
extern void list_destroy(struct list *list);

"""

def gen_func_body(prop, inp, expected):
    body = ""
    for op in inp.get("operations", []):
        if "expected" in op:
            body += f'TEST_ASSERT_EQUAL({op["expected"]}, list_{op["operation"]}(list));\n'
        else:
            if "value" in op:
                body += f'list_{op["operation"]}(list, {op["value"]});\n'
            else:
                body += f'list_{op["operation"]}(list);\n'
    return body