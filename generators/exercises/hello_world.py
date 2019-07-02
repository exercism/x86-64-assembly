FUNC_PROTO = """\
#include "vendor/unity.h"

extern const char *hello(void);
"""

def gen_func_body(prop, inp, expected):
    return f'TEST_ASSERT_EQUAL_STRING("{expected}", {prop}());\n'
