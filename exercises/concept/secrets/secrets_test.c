#include "vendor/unity.h"

#include <stdint.h>

extern uint8_t extract_higher_bits(uint16_t code);
extern uint8_t extract_lower_bits(uint16_t code);
extern uint8_t extract_redundant_bits(uint16_t code);
extern uint8_t set_message_bits(uint16_t code);
extern uint16_t rotate_private_key(uint16_t code);
extern uint8_t format_private_key(uint16_t code);
extern uint16_t decrypt_message(uint16_t code);

void setUp(void) {
}

void tearDown(void) {
}

void test_higher_bits_0b1010_0100_1100_0101(void) {
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(164, extract_higher_bits(42181), "The function was called with argument: 0b1010_0100_1100_0101.");
}

void test_higher_bits_0b0001_1100_0001_1100(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(28, extract_higher_bits(7196), "The function was called with argument: 0b0001_1100_0001_1100.");
}

void test_higher_bits_0b0000_0000_1111_1111(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, extract_higher_bits(255), "The function was called with argument: 0b0000_0000_1111_1111.");
}

void test_higher_bits_0b1111_1111_0000_0000(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(255, extract_higher_bits(65280), "The function was called with argument: 0b1111_1111_0000_0000.");
}

void test_lower_bits_0b1010_0100_1100_0101(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(197, extract_lower_bits(42181), "The function was called with argument: 0b1010_0100_1100_0101.");
}

void test_lower_bits_0b0001_1100_0001_1100(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(28, extract_lower_bits(7196), "The function was called with argument: 0b0001_1100_0001_1100.");
}

void test_lower_bits_0b0000_0000_1111_1111(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(255, extract_lower_bits(255), "The function was called with argument: 0b0000_0000_1111_1111.");
}

void test_lower_bits_0b1111_1111_0000_0000(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, extract_lower_bits(65280), "The function was called with argument: 0b1111_1111_0000_0000.");
}

void test_redundant_bits_0b1010_0100_1100_0101(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(132, extract_redundant_bits(42181), "The function was called with argument: 0b1010_0100_1100_0101.");
}

void test_redundant_bits_0b0001_1100_0001_1100(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(28, extract_redundant_bits(7196), "The function was called with argument: 0b0001_1100_0001_1100.");
}

void test_redundant_bits_0b0000_0000_1111_1111(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, extract_redundant_bits(255), "The function was called with argument: 0b0000_0000_1111_1111.");
}

void test_redundant_bits_0b1111_1111_0000_0000(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, extract_redundant_bits(65280), "The function was called with argument: 0b1111_1111_0000_0000.");
}

void test_set_message_bits_0b1010_0100_1100_0101(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(229, set_message_bits(42181), "The function was called with argument: 0b1010_0100_1100_0101.");
}

void test_set_message_bits_0b0001_1100_0001_1100(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(28, set_message_bits(7196), "The function was called with argument: 0b0001_1100_0001_1100.");
}

void test_set_message_bits_0b0000_0000_1111_1111(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(255, set_message_bits(255), "The function was called with argument: 0b0000_0000_1111_1111.");
}

void test_set_message_bits_0b1111_1111_0000_0000(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(255, set_message_bits(65280), "The function was called with argument: 0b1111_1111_0000_0000.");
}

void test_rotate_private_key_0b1010_0100_1100_0101(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(52466, rotate_private_key(42181), "The function was called with argument: 0b1010_0100_1100_0101.");
}

void test_rotate_private_key_0b0001_1100_0001_1100(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(39397, rotate_private_key(7196), "The function was called with argument: 0b0001_1100_0001_1100.");
}

void test_rotate_private_key_0b0000_0000_1111_1111(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(45884, rotate_private_key(255), "The function was called with argument: 0b0000_0000_1111_1111.");
}

void test_rotate_private_key_0b1111_1111_0000_0000(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(45884, rotate_private_key(65280), "The function was called with argument: 0b1111_1111_0000_0000.");
}

void test_format_private_key_0b1010_0100_1100_0101(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(193, format_private_key(42181), "The function was called with argument: 0b1010_0100_1100_0101.");
}

void test_format_private_key_0b0001_1100_0001_1100(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(131, format_private_key(7196), "The function was called with argument: 0b0001_1100_0001_1100.");
}

void test_format_private_key_0b0000_0000_1111_1111(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(112, format_private_key(255), "The function was called with argument: 0b0000_0000_1111_1111.");
}

void test_format_private_key_0b1111_1111_0000_0000(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(112, format_private_key(65280), "The function was called with argument: 0b1111_1111_0000_0000.");
}

void test_decrypt_message_0b1010_0100_1100_0101(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(49637, decrypt_message(42181), "The function was called with argument: 0b1010_0100_1100_0101.");
}

void test_decrypt_message_0b0001_1100_0001_1100(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(33564, decrypt_message(7196), "The function was called with argument: 0b0001_1100_0001_1100.");
}

void test_decrypt_message_0b0000_0000_1111_1111(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(28927, decrypt_message(255), "The function was called with argument: 0b0000_0000_1111_1111.");
}

void test_decrypt_message_0b1111_1111_0000_0000(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(28927, decrypt_message(65280), "The function was called with argument: 0b1111_1111_0000_0000.");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_higher_bits_0b1010_0100_1100_0101);
    RUN_TEST(test_higher_bits_0b0001_1100_0001_1100);
    RUN_TEST(test_higher_bits_0b0000_0000_1111_1111);
    RUN_TEST(test_higher_bits_0b1111_1111_0000_0000);
    RUN_TEST(test_lower_bits_0b1010_0100_1100_0101);
    RUN_TEST(test_lower_bits_0b0001_1100_0001_1100);
    RUN_TEST(test_lower_bits_0b0000_0000_1111_1111);
    RUN_TEST(test_lower_bits_0b1111_1111_0000_0000);
    RUN_TEST(test_redundant_bits_0b1010_0100_1100_0101);
    RUN_TEST(test_redundant_bits_0b0001_1100_0001_1100);
    RUN_TEST(test_redundant_bits_0b0000_0000_1111_1111);
    RUN_TEST(test_redundant_bits_0b1111_1111_0000_0000);
    RUN_TEST(test_set_message_bits_0b1010_0100_1100_0101);
    RUN_TEST(test_set_message_bits_0b0001_1100_0001_1100);
    RUN_TEST(test_set_message_bits_0b0000_0000_1111_1111);
    RUN_TEST(test_set_message_bits_0b1111_1111_0000_0000);
    RUN_TEST(test_rotate_private_key_0b1010_0100_1100_0101);
    RUN_TEST(test_rotate_private_key_0b0001_1100_0001_1100);
    RUN_TEST(test_rotate_private_key_0b0000_0000_1111_1111);
    RUN_TEST(test_rotate_private_key_0b1111_1111_0000_0000);
    RUN_TEST(test_format_private_key_0b1010_0100_1100_0101);
    RUN_TEST(test_format_private_key_0b0001_1100_0001_1100);
    RUN_TEST(test_format_private_key_0b0000_0000_1111_1111);
    RUN_TEST(test_format_private_key_0b1111_1111_0000_0000);
    RUN_TEST(test_decrypt_message_0b1010_0100_1100_0101);
    RUN_TEST(test_decrypt_message_0b0001_1100_0001_1100);
    RUN_TEST(test_decrypt_message_0b0000_0000_1111_1111);
    RUN_TEST(test_decrypt_message_0b1111_1111_0000_0000);
    return UNITY_END();
}
