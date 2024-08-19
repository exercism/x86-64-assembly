// Version: 1.0.0

#include "vendor/unity.h"

#define BUFFER_SIZE 256

extern void encode(char *buffer, const char *phrase);
extern void decode(char *buffer, const char *phrase);

void setUp(void) {
}

void tearDown(void) {
}

void test_encode_yes(void) {
    char buffer[BUFFER_SIZE];

    encode(buffer, "yes");
    TEST_ASSERT_EQUAL_STRING("bvh", buffer);
}

void test_encode_no(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "no");
    TEST_ASSERT_EQUAL_STRING("ml", buffer);
}

void test_encode_omg(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "OMG");
    TEST_ASSERT_EQUAL_STRING("lnt", buffer);
}

void test_encode_spaces(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "O M G");
    TEST_ASSERT_EQUAL_STRING("lnt", buffer);
}

void test_encode_mindblowingly(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "mindblowingly");
    TEST_ASSERT_EQUAL_STRING("nrmwy oldrm tob", buffer);
}

void test_encode_numbers(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "Testing,1 2 3, testing.");
    TEST_ASSERT_EQUAL_STRING("gvhgr mt123 gvhgr mt", buffer);
}

void test_encode_deep_thought(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "Truth is fiction.");
    TEST_ASSERT_EQUAL_STRING("gifgs rhurx grlm", buffer);
}

void test_encode_all_the_letters(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "The quick brown fox jumps over the lazy dog.");
    TEST_ASSERT_EQUAL_STRING("gsvjf rxpyi ldmul cqfnk hlevi gsvoz abwlt", buffer);
}

void test_decode_exercism(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "vcvix rhn");
    TEST_ASSERT_EQUAL_STRING("exercism", buffer);
}

void test_decode_a_sentence(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "zmlyh gzxov rhlug vmzhg vkkrm thglm v");
    TEST_ASSERT_EQUAL_STRING("anobstacleisoftenasteppingstone", buffer);
}

void test_decode_numbers(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "gvhgr mt123 gvhgr mt");
    TEST_ASSERT_EQUAL_STRING("testing123testing", buffer);
}

void test_decode_all_the_letters(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "gsvjf rxpyi ldmul cqfnk hlevi gsvoz abwlt");
    TEST_ASSERT_EQUAL_STRING("thequickbrownfoxjumpsoverthelazydog", buffer);
}

void test_decode_with_too_many_spaces(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "vc vix    r hn");
    TEST_ASSERT_EQUAL_STRING("exercism", buffer);
}

void test_decode_with_no_spaces(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "zmlyhgzxovrhlugvmzhgvkkrmthglmv");
    TEST_ASSERT_EQUAL_STRING("anobstacleisoftenasteppingstone", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_encode_yes);
    RUN_TEST(test_encode_no);
    RUN_TEST(test_encode_omg);
    RUN_TEST(test_encode_spaces);
    RUN_TEST(test_encode_mindblowingly);
    RUN_TEST(test_encode_numbers);
    RUN_TEST(test_encode_deep_thought);
    RUN_TEST(test_encode_all_the_letters);
    RUN_TEST(test_decode_exercism);
    RUN_TEST(test_decode_a_sentence);
    RUN_TEST(test_decode_numbers);
    RUN_TEST(test_decode_all_the_letters);
    RUN_TEST(test_decode_with_too_many_spaces);
    RUN_TEST(test_decode_with_no_spaces);
    return UNITY_END();
}
