FUNC_PROTO = """\
#include <stdbool.h>
#include "vendor/unity.h"

typedef struct {
   double a;
   double b;
   double c;
} triangle_t;

extern bool is_equilateral(triangle_t sides);
extern bool is_isosceles(triangle_t sides);
extern bool is_scalene(triangle_t sides);
"""

def gen_func_body(prop, inp, expected):
    # print(prop, inp, expected)
    return f"triangle_t sides = {{ {inp['sides'][0]}, {inp['sides'][1]}, {inp['sides'][2] } }} ;\nTEST_ASSERT_{str(expected).upper()}(is_{prop}(sides));\n"
