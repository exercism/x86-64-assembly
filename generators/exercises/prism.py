FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>

#define BUFFER_SIZE 128
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef struct {
    float x;
    float y;
    float angle;
} coordinate_t;

typedef struct {
    uint32_t id;
    coordinate_t coordinates;
} prism_t;

extern size_t find_sequence(uint32_t buffer[], const coordinate_t start, const prism_t *prisms, size_t num_prisms);
"""


def get_coordinate(obj):
    return f"{{ .x = {obj['x']}, .y = {obj['y']}, .angle = {obj['angle']} }}"


def get_prism(obj):
    coordinate = get_coordinate(obj)
    return f"{{ .id = {obj['id']}, .coordinates = {coordinate} }}"


def array_literal(array):
    return str(array).replace("[", "{").replace("]", "}")


def string_literal(array):
    return array_literal(array).replace("'", "")


def gen_func_body(prop, inp, expected):
    str_list = []
    start = get_coordinate(inp["start"])
    prisms = [get_prism(prism) for prism in inp["prisms"]]
    sequence = expected["sequence"]
    str_list.append(f"const coordinate_t start = {start};")
    str_list.append("alignas(64) uint32_t buffer[BUFFER_SIZE];")
    if len(prisms) > 0:
        str_list.append(
            f"alignas(64) const prism_t prisms[] = {string_literal(prisms)};"
        )
        str_list.append(
            f"const size_t result = {prop}(buffer, start, prisms, ARRAY_SIZE(prisms));"
        )
    else:
        str_list.append(f"const size_t result = {prop}(buffer, start, NULL, 0);")
    if len(sequence) > 0:
        str_list.append(f"const uint32_t expected[] = {array_literal(sequence)};")
        str_list.append("TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), result);")
        str_list.append(
            "TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));"
        )
    else:
        str_list.append("TEST_ASSERT_EQUAL_UINT64(0, result);")
    return "\n".join(str_list)
