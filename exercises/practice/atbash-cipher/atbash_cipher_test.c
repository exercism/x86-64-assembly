#include "vendor/unity.h"

#include <stdalign.h>

#define BUFFER_SIZE 256

extern void encode(char buffer[], const char phrase[]);
extern void decode(char buffer[], const char phrase[]);

void setUp(void) {
}

void tearDown(void) {
}

void test_encode_yes(void) {
    alignas(16) const char phrase[] = "yes";
    char buffer[BUFFER_SIZE];

    encode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("bvh", buffer);
}

void test_encode_no(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "no";
    char buffer[BUFFER_SIZE];

    encode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("ml", buffer);
}

void test_encode_omg(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "OMG";
    char buffer[BUFFER_SIZE];

    encode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("lnt", buffer);
}

void test_encode_spaces(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "O M G";
    char buffer[BUFFER_SIZE];

    encode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("lnt", buffer);
}

void test_encode_mindblowingly(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "mindblowingly";
    char buffer[BUFFER_SIZE];

    encode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("nrmwy oldrm tob", buffer);
}

void test_encode_numbers(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "Testing,1 2 3, testing.";
    char buffer[BUFFER_SIZE];

    encode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("gvhgr mt123 gvhgr mt", buffer);
}

void test_encode_deep_thought(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "Truth is fiction.";
    char buffer[BUFFER_SIZE];

    encode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("gifgs rhurx grlm", buffer);
}

void test_encode_all_the_letters(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "The quick brown fox jumps over the lazy dog.";
    char buffer[BUFFER_SIZE];

    encode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("gsvjf rxpyi ldmul cqfnk hlevi gsvoz abwlt", buffer);
}

void test_decode_exercism(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "vcvix rhn";
    char buffer[BUFFER_SIZE];

    decode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("exercism", buffer);
}

void test_decode_a_sentence(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "zmlyh gzxov rhlug vmzhg vkkrm thglm v";
    char buffer[BUFFER_SIZE];

    decode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("anobstacleisoftenasteppingstone", buffer);
}

void test_decode_numbers(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "gvhgr mt123 gvhgr mt";
    char buffer[BUFFER_SIZE];

    decode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("testing123testing", buffer);
}

void test_decode_all_the_letters(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "gsvjf rxpyi ldmul cqfnk hlevi gsvoz abwlt";
    char buffer[BUFFER_SIZE];

    decode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("thequickbrownfoxjumpsoverthelazydog", buffer);
}

void test_decode_with_too_many_spaces(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "vc vix    r hn";
    char buffer[BUFFER_SIZE];

    decode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("exercism", buffer);
}

void test_decode_with_no_spaces(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "zmlyhgzxovrhlugvmzhgvkkrmthglmv";
    char buffer[BUFFER_SIZE];

    decode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("anobstacleisoftenasteppingstone", buffer);
}

void test_encode_boundary_characters(void) {
    TEST_IGNORE();
    alignas(16) const char phrase[] = "/09:@AMNZ[`amnz{";
    char buffer[BUFFER_SIZE];

    encode(buffer, phrase);
    TEST_ASSERT_EQUAL_STRING("09znm aznma", buffer);
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
    RUN_TEST(test_encode_boundary_characters);
    return UNITY_END();
}
