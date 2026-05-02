#include "vendor/unity.h"

#define BUFFER_SIZE 64

extern void encode(char message[], size_t rails);
extern void decode(char message[], size_t rails);

void setUp(void) {
}

void tearDown(void) {
}

void test_encode_with_two_rails(void) {
    char message[BUFFER_SIZE] = "XOXOXOXOXOXOXOXOXO";
    encode(message, 2);
    TEST_ASSERT_EQUAL_STRING("XXXXXXXXXOOOOOOOOO", message);
}

void test_encode_with_three_rails(void) {
    TEST_IGNORE();
    char message[BUFFER_SIZE] = "WEAREDISCOVEREDFLEEATONCE";
    encode(message, 3);
    TEST_ASSERT_EQUAL_STRING("WECRLTEERDSOEEFEAOCAIVDEN", message);
}

void test_encode_with_ending_in_the_middle(void) {
    TEST_IGNORE();
    char message[BUFFER_SIZE] = "EXERCISES";
    encode(message, 4);
    TEST_ASSERT_EQUAL_STRING("ESXIEECSR", message);
}

void test_decode_with_three_rails(void) {
    TEST_IGNORE();
    char message[BUFFER_SIZE] = "TEITELHDVLSNHDTISEIIEA";
    decode(message, 3);
    TEST_ASSERT_EQUAL_STRING("THEDEVILISINTHEDETAILS", message);
}

void test_decode_with_five_rails(void) {
    TEST_IGNORE();
    char message[BUFFER_SIZE] = "EIEXMSMESAORIWSCE";
    decode(message, 5);
    TEST_ASSERT_EQUAL_STRING("EXERCISMISAWESOME", message);
}

void test_decode_with_six_rails(void) {
    TEST_IGNORE();
    char message[BUFFER_SIZE] = "133714114238148966225439541018335470986172518171757571896261";
    decode(message, 6);
    TEST_ASSERT_EQUAL_STRING("112358132134558914423337761098715972584418167651094617711286", message);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_encode_with_two_rails);
    RUN_TEST(test_encode_with_three_rails);
    RUN_TEST(test_encode_with_ending_in_the_middle);
    RUN_TEST(test_decode_with_three_rails);
    RUN_TEST(test_decode_with_five_rails);
    RUN_TEST(test_decode_with_six_rails);
    return UNITY_END();
}
