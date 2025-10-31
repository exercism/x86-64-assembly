#include "vendor/unity.h"

#include <stdint.h>

static const uint32_t color_table[] = {0xFFFFFF00, 0xFFFF0000, 0x00FFFF00, 0x80008000, 0xA52A2A00, 0x1C282600,
                                       0xEEF4D400, 0xC6F91F00, 0x64453600, 0x7D2E6800, 0x9C28A600};

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
        const uint32_t channel = (((base >> shift) & 255) + ((sec >> shift) & 255)) & 255;
        combination |= channel << shift;
    }
    return combination;
}

void setUp(void) {
}

void tearDown(void) {
}

void test_get_color_value_cyan(void) {
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(*cyan, get_color_value(cyan), "The color value for cyan is different from expected.");
}

void test_get_color_value_brown(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(*brown, get_color_value(brown), "The color value for brown is different from expected.");
}

void test_get_color_value_gunmetal(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(*gunmetal, get_color_value(gunmetal), "The color value for gunmetal is different from expected.");
}

void test_get_color_value_byzantium(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(*byzantium, get_color_value(byzantium), "The color value for byzantium is different from expected.");
}

void test_base_color_default(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_MESSAGE(base_color, *white, "The value for the base color is different from expected.");
}

void test_base_color_beige(void) {
    TEST_IGNORE();
    add_base_color(beige);
    TEST_ASSERT_EQUAL_MESSAGE(base_color, *beige, "The value for the base color is different from expected.");
}

void test_base_color_lime(void) {
    TEST_IGNORE();
    add_base_color(lime);
    TEST_ASSERT_EQUAL_MESSAGE(base_color, *lime, "The value for the base color is different from expected.");
}

void test_base_color_coffee(void) {
    TEST_IGNORE();
    add_base_color(coffee);
    TEST_ASSERT_EQUAL_MESSAGE(base_color, *coffee, "The value for the base color is different from expected.");
}

void test_constant_red(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(0xFF000000, RED, "The value for the constant 0xFF000000 is different from expected.");
}

void test_constant_green(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x00FF0000, GREEN, "The value for the constant 0x00FF0000 is different from expected.");
}

void test_constant_blue(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x0000FF00, BLUE, "The value for the constant 0x0000FF00 is different from expected.");
}

void test_combine_red_green_is_yellow(void) {
    TEST_IGNORE();
    uint32_t combined_color;
    add_base_color(&RED);
    make_color_combination(&combined_color, &GREEN);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(*yellow, combined_color, "The value of the combined color is different than expected.");
}

void test_combine_green_blue_is_cyan(void) {
    TEST_IGNORE();
    uint32_t combined_color;
    add_base_color(&GREEN);
    make_color_combination(&combined_color, &BLUE);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(*cyan, combined_color, "The value of the combined color is different than expected.");
}

void test_combine_yellow_blue_is_white(void) {
    TEST_IGNORE();
    uint32_t combined_color;
    add_base_color(yellow);
    make_color_combination(&combined_color, &BLUE);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(*white, combined_color, "The value of the combined color is different than expected.");
}

void test_combine_cyan_red_is_white(void) {
    TEST_IGNORE();
    uint32_t combined_color;
    add_base_color(cyan);
    make_color_combination(&combined_color, &RED);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(*white, combined_color, "The value of the combined color is different than expected.");
}

void test_combine_purple_gunmetal_is_mauveine(void) {
    TEST_IGNORE();
    uint32_t combined_color;
    add_base_color(purple);
    make_color_combination(&combined_color, gunmetal);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(*mauveine, combined_color, "The value of the combined color is different than expected.");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_color_value_cyan);
    RUN_TEST(test_get_color_value_brown);
    RUN_TEST(test_get_color_value_gunmetal);
    RUN_TEST(test_get_color_value_byzantium);
    RUN_TEST(test_base_color_default);
    RUN_TEST(test_base_color_beige);
    RUN_TEST(test_base_color_lime);
    RUN_TEST(test_base_color_coffee);
    RUN_TEST(test_constant_red);
    RUN_TEST(test_constant_green);
    RUN_TEST(test_constant_blue);
    RUN_TEST(test_combine_red_green_is_yellow);
    RUN_TEST(test_combine_green_blue_is_cyan);
    RUN_TEST(test_combine_yellow_blue_is_white);
    RUN_TEST(test_combine_cyan_red_is_white);
    RUN_TEST(test_combine_purple_gunmetal_is_mauveine);
    return UNITY_END();
}
