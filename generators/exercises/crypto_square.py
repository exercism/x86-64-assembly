from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 100
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern void ciphertext(char buffer[], const char *plaintext);
"""

FUNC_GEN_TEMPLATE = Template("""
char buffer[BUFFER_SIZE];

${prop}(buffer, "${plaintext}");

TEST_ASSERT_EQUAL_STRING("${expected}", buffer);
""")


def gen_func_body(prop, inp, expected):
    return FUNC_GEN_TEMPLATE.substitute(
        expected=expected, prop=prop, plaintext=inp["plaintext"]
    )
