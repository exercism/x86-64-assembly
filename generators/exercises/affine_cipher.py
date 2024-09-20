FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 256

extern void encode(char *buffer, const char *phrase, int a, int b);
extern void decode(char *buffer, const char *phrase, int a, int b);
"""

def gen_func_body(prop, inp, expected):
    str_list = []
    if expected.__class__ == dict:
        expected = ""
    phrase = inp["phrase"]
    a = inp["key"]["a"]
    b = inp["key"]["b"]
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f'{prop}(buffer, "{phrase}", {a}, {b});\n')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);\n')
    return "".join(str_list)
