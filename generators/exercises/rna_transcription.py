FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 256

extern void to_rna(const char *dna, char *buffer);
"""

def gen_func_body(prop, inp, expected):
    str_list = []
    dna = inp["dna"]
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f'{prop}("{dna}", buffer);\n')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);\n')
    return "".join(str_list)
