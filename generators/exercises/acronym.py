FUNC_PROTO = """\
#include <string.h> 

#include "vendor/unity.h"

#define BUFFER_SIZE 0x100
char out[BUFFER_SIZE];

extern void abbreviate(const char* in, char* out);

void tearDown(void) {
    memset(out, 0, BUFFER_SIZE*sizeof(char)); 
}
"""
def gen_func_body(prop, inp, expected):
    str_list = []
    value = inp["phrase"].replace("\\", "\\\\")
    str_list.append(f'const char *in = "{value}";\n')
    str_list.append(f'{prop}(in, out);\n')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", out);\n')
    return "".join(str_list)