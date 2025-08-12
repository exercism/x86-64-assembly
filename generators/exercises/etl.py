FUNC_PROTO = """\
#include "stdint.h"
#include "vendor/unity.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define ALPHABET_SIZE 26

typedef struct {
    int32_t key;
    uint8_t values_size;
    char values[ALPHABET_SIZE];
} LegacyMap;

typedef struct {
    char key;
    int32_t value;
} NewMapEntry;

extern size_t transform(NewMapEntry *output, const LegacyMap *input, size_t input_size);
"""

def gen_func_body(prop, inp, expected):
    legacy = inp["legacy"]
    legacy_size = len(legacy)

    input_str = "const LegacyMap input[] = {\n"
    for key, values in legacy.items():
        input_str += "    {" + f'{key}, '
        input_str += f'{len(values)}, '
        input_str += f'{values}'.replace("[", "{").replace("]", "}") + "},\n"
    input_str += "};\n"

    input_str += "NewMapEntry buffer[ALPHABET_SIZE];\n"
    input_str += "const NewMapEntry expected[] = {\n"
    for key, value in expected.items():
        input_str += "    {" + "'" + f'{key}' "', " + f'{value}' + "},\n"
    input_str += "};\n\n"

    input_str += f"const size_t length = transform(buffer, input, {legacy_size});\n\n"
    input_str += "TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);\n"
    input_str += "for (size_t i = 0; i < length; ++i) {\n"
    input_str += "    TEST_ASSERT_EQUAL_UINT8(expected[i].key, buffer[i].key);\n"
    input_str += "    TEST_ASSERT_EQUAL_INT32(expected[i].value, buffer[i].value);\n"
    input_str += "}\n"
        
    return input_str

