FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t strength;
    uint8_t dexterity;
    uint8_t constitution;
    uint8_t intelligence;
    uint8_t wisdom;
    uint8_t charisma;
    uint16_t hitpoints;
} dnd_character_t;

extern int8_t modifier(uint8_t score);
extern uint8_t ability(void);
extern dnd_character_t make_dnd_character(void);

void check_valid_score(uint8_t score) {
    TEST_ASSERT(score >= 3 && score <= 18);
}

"""


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "modifier":
        str_list.append(
            f"TEST_ASSERT_EQUAL_INT8({expected}, {prop}({inp['score']}));\n"
        )
    elif prop == "ability":
        str_list.append("const double expected[16] = " + "{\n")
        str_list.append("7.71, 30.92, 77.12, 162.03, 292.85, 478.45, 701.96, 941.29,")
        str_list.append(
            "1142.66, 1288.6, 1327.06,  1234.4,  1010.08, 725.67, 416.99, 162.16"
        )
        str_list.append("};\n\n")
        str_list.append("double results[16] = " + "{0};\n")
        str_list.append("for (size_t i = 0; i < 10000; ++i) " + "{\n")
        str_list.append("const uint8_t value = ability();\n")
        str_list.append("check_valid_score(value);\n")
        str_list.append("results[value - 3]++;\n")
        str_list.append("}\n\n")
        str_list.append("double sum_of_frequencies = 0;\n")
        str_list.append("for (size_t i = 0; i < 16; ++i) " + "{\n")
        str_list.append(
            "const double squared = (results[i] - expected[i]) * (results[i] - expected[i]);\n"
        )
        str_list.append("sum_of_frequencies += squared / expected[i];\n")
        str_list.append("}\n\n")
        str_list.append(
            "TEST_ASSERT_LESS_OR_EQUAL(37697, (uint32_t)(1000 * sum_of_frequencies));\n"
        )
    else:
        characters = [
            "Wulfgar",
            "Artemis_Entreri",
            "Drizzt_Do_Urden",
            "Elminster",
            "Cattie_Brie",
            "Regis",
        ]
        scores = [
            "strength",
            "dexterity",
            "constitution",
            "intelligence",
            "wisdom",
            "charisma",
        ]
        for index in range(6):
            character = characters[index]
            score = scores[index]
            str_list.append(f"const dnd_character_t {character} = make_dnd_{prop}();\n")
            str_list.append(f"check_valid_score({character}.{score});\n")
            str_list.append(
                f"TEST_ASSERT_EQUAL(10 + modifier({character}.constitution), {character}.hitpoints);\n\n"
            )
    return "".join(str_list)
