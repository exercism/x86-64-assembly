import re
from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define BUFFER_SIZE 20
#define WORD_SIZE 48
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef struct {
    char word[WORD_SIZE];
    size_t count;
} wordMap;

extern size_t count_words(wordMap *buffer, const char *sentence);
"""

FUNC_GEN_TEMPLATE = Template("""
wordMap buffer[BUFFER_SIZE];
const wordMap expected[] = ${expected};
const size_t arr_length = ARRAY_SIZE(expected);

TEST_ASSERT_EQUAL_UINT64(arr_length, ${prop}(buffer, "${sentence}"));
for (size_t i = 0; i < arr_length; ++i) {
    bool flag = false;
    for (size_t j = 0; j < arr_length && !flag; ++j) {
        flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
    }
    TEST_ASSERT_EQUAL(true, flag);
}
""")


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    sentence = str(inp["sentence"]).replace("\n", "\\n")
    expected_list = []
    for key, value in expected.items():
        expected_list.append("{" + f'"{key}", {value}' + "}")
    expected = re.sub(r"(?<!\\)'", "", array_literal(expected_list))
    expected = re.sub(r"\\'", "'", expected)
    return FUNC_GEN_TEMPLATE.substitute(expected=expected, prop=prop, sentence=sentence)
