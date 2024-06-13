FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 256

extern void encode(char *buffer, const char *phrase);
extern void decode(char *buffer, const char *phrase);
"""

def gen_func_body(prop, inp, expected):
    str_list = []
    phrase = inp["phrase"]
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f'{prop}(buffer, "{phrase}");\n')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);\n')
    return "".join(str_list)
