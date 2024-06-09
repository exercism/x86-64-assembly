#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
This script can be used to generate the test file from the canonical data.

It is currently specific to the protein translation exercise,
but should be easy to modify for other exercises.
"""

import sys
import json
import tomllib
from string import Template
import re

#=EXERCISE=SPECIFIC=BITS============================================================================

EXTERNAL_FUNCTIONS_STR = "const char **proteins(const char *rna);"
ADDITIONAL_DEFINITIONS_STR = ""

def write_test_function(test, ignore):
    return TEST_FUNCTION_TEMPLATE.substitute(
        test_name=make_valid_c_function_name(test['description']),
        test_ignore=IGNORE_TEST_STR if ignore else '',
        rna_strand='\"' + test['input']['strand'] + '\"',
        expected_size=len(test['expected']),
        expected_test=EXPECTED_TEST_TEMPALTE.substitute(
            expected=', '.join(['\"' + x + '\"' for x in test['expected']])) if len(test['expected']) > 0 else ''
    )

TEST_FUNCTION_TEMPLATE = Template("""
void test_${test_name}() {${test_ignore}
    const char **names = proteins(${rna_strand});

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(${expected_size}, size);${expected_test}
}
""")

EXPECTED_TEST_TEMPALTE = Template("""\n
    const char *expected[] = {${expected}};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);"""
)

#===================================================================================================

TEST_FILE_TEMPLATE = Template("""
// Version: 1.0.0

#include "vendor/unity.h"

${external_functions}
${additional_definitions}

void setUp(void) {
}

void tearDown(void) {
}

${test_defintions}

int main(void) {
    UNITY_BEGIN();${test_calls}
    return UNITY_END();
}

""")

TEST_CALL_TEMPLATE = Template("""
    RUN_TEST(test_${test_name});""")

IGNORE_TEST_STR = "\n    TEST_IGNORE();"

def make_valid_c_function_name(name):
    return re.sub("\W", "", name.replace(' ', '_').replace('-', '_'))

def write_test_call(test):
    return TEST_CALL_TEMPLATE.substitute(test_name = make_valid_c_function_name(test['description']))

def test_included(test, test_toml):
    return test_toml.get(test['uuid'], {}).get('include', True)


if __name__ == '__main__':
    if len(sys.argv) < 3 or len(sys.argv) > 4:
        print('Usage: python create_tests.py <path-to-canonical-data> <path-to-test-file> [path-to-toml-file]')
        sys.exit(1)

    with open(sys.argv[1], 'r') as canonical_data_json:
        canonical_data = json.load(canonical_data_json)

    if len(sys.argv) == 4:
        with open(sys.argv[3], 'rb') as toml_file:
            test_toml = tomllib.load(toml_file)
    else:
        test_toml = {}

    with open(sys.argv[2], 'w') as test_file:
        test_file.write(TEST_FILE_TEMPLATE.substitute(
            additional_definitions=ADDITIONAL_DEFINITIONS_STR,
            external_functions=EXTERNAL_FUNCTIONS_STR,
            test_defintions="".join([write_test_function(test, i != 0)
                for i, test in enumerate(canonical_data['cases']) if test_included(test, test_toml)]),
            test_calls="".join([write_test_call(test)
                for test in canonical_data['cases'] if test_included(test, test_toml)])
        ))

