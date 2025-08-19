#include "vendor/unity.h"

#define BUFFER_SIZE 256

extern void encode(char *buffer, const char *phrase, int a, int b);
extern void decode(char *buffer, const char *phrase, int a, int b);

void setUp(void) {
}

void tearDown(void) {
}

void test_encode_yes(void) {
    char buffer[BUFFER_SIZE];

    encode(buffer, "yes", 5, 7);
    TEST_ASSERT_EQUAL_STRING("xbt", buffer);
}

void test_encode_no(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "no", 15, 18);
    TEST_ASSERT_EQUAL_STRING("fu", buffer);
}

void test_encode_omg(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "OMG", 21, 3);
    TEST_ASSERT_EQUAL_STRING("lvz", buffer);
}

void test_encode_o_m_g(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "O M G", 25, 47);
    TEST_ASSERT_EQUAL_STRING("hjp", buffer);
}

void test_encode_mindblowingly(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "mindblowingly", 11, 15);
    TEST_ASSERT_EQUAL_STRING("rzcwa gnxzc dgt", buffer);
}

void test_encode_numbers(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "Testing,1 2 3, testing.", 3, 4);
    TEST_ASSERT_EQUAL_STRING("jqgjc rw123 jqgjc rw", buffer);
}

void test_encode_deep_thought(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "Truth is fiction.", 5, 17);
    TEST_ASSERT_EQUAL_STRING("iynia fdqfb ifje", buffer);
}

void test_encode_all_the_letters(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "The quick brown fox jumps over the lazy dog.", 17, 33);
    TEST_ASSERT_EQUAL_STRING("swxtj npvyk lruol iejdc blaxk swxmh qzglf", buffer);
}

void test_encode_with_a_not_coprime_to_m(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "This is a test.", 6, 17);
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_decode_exercism(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "tytgn fjr", 3, 7);
    TEST_ASSERT_EQUAL_STRING("exercism", buffer);
}

void test_decode_a_sentence(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "qdwju nqcro muwhn odqun oppmd aunwd o", 19, 16);
    TEST_ASSERT_EQUAL_STRING("anobstacleisoftenasteppingstone", buffer);
}

void test_decode_numbers(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "odpoz ub123 odpoz ub", 25, 7);
    TEST_ASSERT_EQUAL_STRING("testing123testing", buffer);
}

void test_decode_all_the_letters(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "swxtj npvyk lruol iejdc blaxk swxmh qzglf", 17, 33);
    TEST_ASSERT_EQUAL_STRING("thequickbrownfoxjumpsoverthelazydog", buffer);
}

void test_decode_with_no_spaces_in_input(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "swxtjnpvyklruoliejdcblaxkswxmhqzglf", 17, 33);
    TEST_ASSERT_EQUAL_STRING("thequickbrownfoxjumpsoverthelazydog", buffer);
}

void test_decode_with_too_many_spaces(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "vszzm    cly   yd cg    qdp", 15, 16);
    TEST_ASSERT_EQUAL_STRING("jollygreengiant", buffer);
}

void test_decode_with_a_not_coprime_to_m(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "Test", 13, 5);
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_encode_yes);
    RUN_TEST(test_encode_no);
    RUN_TEST(test_encode_omg);
    RUN_TEST(test_encode_o_m_g);
    RUN_TEST(test_encode_mindblowingly);
    RUN_TEST(test_encode_numbers);
    RUN_TEST(test_encode_deep_thought);
    RUN_TEST(test_encode_all_the_letters);
    RUN_TEST(test_encode_with_a_not_coprime_to_m);
    RUN_TEST(test_decode_exercism);
    RUN_TEST(test_decode_a_sentence);
    RUN_TEST(test_decode_numbers);
    RUN_TEST(test_decode_all_the_letters);
    RUN_TEST(test_decode_with_no_spaces_in_input);
    RUN_TEST(test_decode_with_too_many_spaces);
    RUN_TEST(test_decode_with_a_not_coprime_to_m);
    return UNITY_END();
}
