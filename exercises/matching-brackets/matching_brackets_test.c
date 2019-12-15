// Version: 2.0.0

#include "vendor/unity.h"

extern int is_paired(const char *str);

void setUp(void) {
}

void tearDown(void) {
}

void test_paired_square_brackets(void) {
    const char *str = "[]";

    TEST_ASSERT_TRUE(is_paired(str));
}

void test_empty_string(void) {
    const char *str = "";

    TEST_ASSERT_TRUE(is_paired(str));
}

void test_unpaired_brackets(void) {
    const char *str = "[[";

    TEST_ASSERT_FALSE(is_paired(str));
}

void test_wrong_ordered_brackets(void) {
    const char *str = "}{";

    TEST_ASSERT_FALSE(is_paired(str));
}

void test_wrong_closing_bracket(void) {
    const char *str = "{]";

    TEST_ASSERT_FALSE(is_paired(str));
}

void test_paired_with_whitespace(void) {
    const char *str = "{ }";

    TEST_ASSERT_TRUE(is_paired(str));
}

void test_partially_paired_brackets(void) {
    const char *str = "{[])";

    TEST_ASSERT_FALSE(is_paired(str));
}

void test_simple_nested_brackets(void) {
    const char *str = "{[]}";

    TEST_ASSERT_TRUE(is_paired(str));
}

void test_several_paired_brackets(void) {
    const char *str = "{}[]";

    TEST_ASSERT_TRUE(is_paired(str));
}

void test_paired_and_nested_brackets(void) {
    const char *str = "([{}({}[])])";

    TEST_ASSERT_TRUE(is_paired(str));
}

void test_unopened_closing_brackets(void) {
    const char *str = "{[)][]}";

    TEST_ASSERT_FALSE(is_paired(str));
}

void test_unpaired_and_nested_brackets(void) {
    const char *str = "([{])";

    TEST_ASSERT_FALSE(is_paired(str));
}

void test_paired_and_wrong_nested_brackets(void) {
    const char *str = "[({]})";

    TEST_ASSERT_FALSE(is_paired(str));
}

void test_paired_and_incomplete_brackets(void) {
    const char *str = "{}[";

    TEST_ASSERT_FALSE(is_paired(str));
}

void test_too_many_closing_brackets(void) {
    const char *str = "[]]";

    TEST_ASSERT_FALSE(is_paired(str));
}

void test_math_expression(void) {
    const char *str = "(((185 + 223.85) * 15) - 543)/2";

    TEST_ASSERT_TRUE(is_paired(str));
}

void test_complex_latex_expression(void) {
    const char *str = "\\left(\\begin{array}{cc} \\frac{1}{3} & x\\\\ \\mathrm{e}^{x} &... x^2 \\end{array}\\right)";

    TEST_ASSERT_TRUE(is_paired(str));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_paired_square_brackets);
    RUN_TEST(test_empty_string);
    RUN_TEST(test_unpaired_brackets);
    RUN_TEST(test_wrong_ordered_brackets);
    RUN_TEST(test_wrong_closing_bracket);
    RUN_TEST(test_paired_with_whitespace);
    RUN_TEST(test_partially_paired_brackets);
    RUN_TEST(test_simple_nested_brackets);
    RUN_TEST(test_several_paired_brackets);
    RUN_TEST(test_paired_and_nested_brackets);
    RUN_TEST(test_unopened_closing_brackets);
    RUN_TEST(test_unpaired_and_nested_brackets);
    RUN_TEST(test_paired_and_wrong_nested_brackets);
    RUN_TEST(test_paired_and_incomplete_brackets);
    RUN_TEST(test_too_many_closing_brackets);
    RUN_TEST(test_math_expression);
    RUN_TEST(test_complex_latex_expression);
    return UNITY_END();
}
