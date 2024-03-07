from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

extern const char **proteins(const char *rna);
"""

TEST_FUNCTION_TEMPLATE = Template("""
const char **names = proteins(${rna_strand});

int size;
for (size = 0; names[size]; size++) {}
TEST_ASSERT_EQUAL_INT(${expected_size}, size);
""")

EXPECTED_TEST_TEMPALTE = Template("""
const char *expected[] = {${expected}};
TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
""")

def gen_func_body(_, input, expected):
    func_body = TEST_FUNCTION_TEMPLATE.substitute(
        rna_strand='\"' + input["strand"] + '\"',
        expected_size=len(expected) if "error" not in expected else 0
    )
    if expected and "error" not in expected:
        func_body += EXPECTED_TEST_TEMPALTE.substitute(
            expected=', '.join(['\"' + x + '\"' for x in expected])
        )
    return func_body
