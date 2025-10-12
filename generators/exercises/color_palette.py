FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

static const uint32_t color_table[] = {
    0xFFFFFF00, 0xFFFF0000, 0x00FFFF00,
    0x80008000, 0xA52A2A00,
    0x1C282600, 0xEEF4D400,
    0xC6F91F00,
    0x64453600, 0x7D2E6800,
    0x9C28A600
};

static const uint32_t *white = &color_table[0];
static const uint32_t *yellow = &color_table[1];
static const uint32_t *cyan = &color_table[2];
static const uint32_t *purple = &color_table[3];
static const uint32_t *brown = &color_table[4];
static const uint32_t *gunmetal = &color_table[5];
static const uint32_t *beige = &color_table[6];
static const uint32_t *lime = &color_table[7];
static const uint32_t *coffee = &color_table[8];
static const uint32_t *byzantium = &color_table[9];
static const uint32_t *mauveine = &color_table[10];

extern uint32_t get_color_value(const uint32_t *color_address);
extern uint32_t base_color;
extern void add_base_color(const uint32_t *color_address);
extern void make_color_combination(uint32_t *combined_color, const uint32_t *color_address);
extern const uint32_t RED;
extern const uint32_t GREEN;
extern const uint32_t BLUE;

uint32_t combining_function(uint32_t base, uint32_t sec) {
    uint32_t combination = 0;
    for (size_t i = 0; i < 4; ++i) {
        const uint32_t shift = (24 - (i << 3));
        const uint32_t channel = (((base >> shift) & 255)
                          + ((sec  >> shift) & 255)) & 255;
        combination |= channel << shift;
    }
    return combination;
}
"""


def extra_cases():
    return [
        {
            "description": "get_color_value_cyan",
            "property": "get_color_value",
            "input": "cyan",
            "expected": "cyan",
        },
        {
            "description": "get_color_value_brown",
            "property": "get_color_value",
            "input": "brown",
            "expected": "brown",
        },
        {
            "description": "get_color_value_gunmetal",
            "property": "get_color_value",
            "input": "gunmetal",
            "expected": "gunmetal",
        },
        {
            "description": "get_color_value_byzantium",
            "property": "get_color_value",
            "input": "byzantium",
            "expected": "byzantium",
        },
        {
            "description": "base_color_default",
            "property": "add_base_color",
            "input": None,
            "expected": "white",
        },
        {
            "description": "base_color_beige",
            "property": "add_base_color",
            "input": "beige",
            "expected": "beige",
        },
        {
            "description": "base_color_lime",
            "property": "add_base_color",
            "input": "lime",
            "expected": "lime",
        },
        {
            "description": "base_color_coffee",
            "property": "add_base_color",
            "input": "coffee",
            "expected": "coffee",
        },
        {
            "description": "constant_RED",
            "property": "constant",
            "input": "RED",
            "expected": "0xFF000000",
        },
        {
            "description": "constant_GREEN",
            "property": "constant",
            "input": "GREEN",
            "expected": "0x00FF0000",
        },
        {
            "description": "constant_BLUE",
            "property": "constant",
            "input": "BLUE",
            "expected": "0x0000FF00",
        },
        {
            "description": "combine_red_green_is_yellow",
            "property": "make_color_combination",
            "input": ["&RED", "&GREEN"],
            "expected": "yellow",
        },
        {
            "description": "combine_green_blue_is_cyan",
            "property": "make_color_combination",
            "input": ["&GREEN", "&BLUE"],
            "expected": "cyan",
        },
        {
            "description": "combine_yellow_blue_is_white",
            "property": "make_color_combination",
            "input": ["yellow", "&BLUE"],
            "expected": "white",
        },
        {
            "description": "combine_cyan_red_is_white",
            "property": "make_color_combination",
            "input": ["cyan", "&RED"],
            "expected": "white",
        },
        {
            "description": "combine_purple_gunmetal_is_mauveine",
            "property": "make_color_combination",
            "input": ["purple", "gunmetal"],
            "expected": "mauveine",
        },
    ]


def array_literal(cards):
    return str(cards).replace("[", "{").replace("]", "}").replace("'", "")


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "get_color_value":
        return f"TEST_ASSERT_EQUAL_UINT32(*{expected}, {prop}({inp}));\n"
    if prop == "add_base_color":
        if inp is None:
            return f"TEST_ASSERT_EQUAL(base_color, *{expected});\n"
        str_list = []
        str_list.append(f"{prop}({inp});")
        str_list.append(f"TEST_ASSERT_EQUAL(base_color, *{expected});")
        return "\n".join(str_list)
    if prop == "constant":
        return f"TEST_ASSERT_EQUAL_UINT32({expected}, {inp});\n"
    str_list = []
    str_list.append("uint32_t combined_color;")
    str_list.append(f"add_base_color({inp[0]});")
    str_list.append(f"{prop}(&combined_color, {inp[1]});")
    str_list.append(f"TEST_ASSERT_EQUAL_UINT32(*{expected}, combined_color);")
    return "\n".join(str_list)
