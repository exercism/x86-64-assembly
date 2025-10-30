#include "vendor/unity.h"

#include <stdint.h>

#define BUFFER_SIZE 50

extern char front_door_response(const char *line);
extern void front_door_password(char *letters);
extern char back_door_response(const char *line);
extern void back_door_password(char *buffer, char *letters);

void setUp(void) {
}

void tearDown(void) {
}

void test_front_door_response_s1(void) {
    TEST_ASSERT_EQUAL_INT8_MESSAGE('S', front_door_response("Sunshine warming my toes,"), "Passed line: Sunshine warming my toes,");
}

void test_front_door_response_u1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('U', front_door_response("Underwater fun with my friends."),
                                   "Passed line: Underwater fun with my friends.");
}

void test_front_door_response_m1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('M', front_door_response("Making homemade ice cream on the porch,"),
                                   "Passed line: Making homemade ice cream on the porch,");
}

void test_front_door_response_m2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('M', front_door_response("Many long nights catching fireflies."),
                                   "Passed line: Many long nights catching fireflies.");
}

void test_front_door_response_e1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('E', front_door_response("Early morning walks to the creek,"),
                                   "Passed line: Early morning walks to the creek,");
}

void test_front_door_response_r1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('R', front_door_response("Reveling in the freedom of lazy days."),
                                   "Passed line: Reveling in the freedom of lazy days.");
}

void test_front_door_response_s2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('S', front_door_response("Serene, calming quality"), "Passed line: Serene, calming quality");
}

void test_front_door_response_o1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('O', front_door_response("Organized, you always have it together"),
                                   "Passed line: Organized, you always have it together");
}

void test_front_door_response_p1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('P', front_door_response("Picturesque, strikingly beautiful"),
                                   "Passed line: Picturesque, strikingly beautiful");
}

void test_front_door_response_h1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('H', front_door_response("Honest, so genuine"), "Passed line: Honest, so genuine");
}

void test_front_door_response_i1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('I', front_door_response("Imaginative, a creative mind"), "Passed line: Imaginative, a creative mind");
}

void test_front_door_response_a1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('A', front_door_response("Alluring, so attractive"), "Passed line: Alluring, so attractive");
}

void test_front_door_response_c1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('C', front_door_response("Compilers intensily bestow"), "Passed line: Compilers intensily bestow");
}

void test_front_door_response_o2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('O', front_door_response("On commencing without ego"), "Passed line: On commencing without ego");
}

void test_front_door_response_d1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('D', front_door_response("Different processes ajar"), "Passed line: Different processes ajar");
}

void test_front_door_response_e2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('E', front_door_response("Exit with zero quick"), "Passed line: Exit with zero quick");
}

void test_front_door_password_summer(void) {
    TEST_IGNORE();
    char letters[] = "SUMMER";
    front_door_password(letters);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Summer", letters, "Combined letters are: SUMMER");
}

void test_front_door_password_sophia(void) {
    TEST_IGNORE();
    char letters[] = "sophia";
    front_door_password(letters);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Sophia", letters, "Combined letters are: sophia");
}

void test_front_door_password_code(void) {
    TEST_IGNORE();
    char letters[] = "Code";
    front_door_password(letters);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Code", letters, "Combined letters are: Code");
}

void test_back_door_response_w1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('w', back_door_response("Compilers intensily bestow"), "Passed line: Compilers intensily bestow");
}

void test_back_door_response_o1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('o', back_door_response("On commencing without ego"), "Passed line: On commencing without ego");
}

void test_back_door_response_r1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('r', back_door_response("Different processes ajar"), "Passed line: Different processes ajar");
}

void test_back_door_response_k1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('k', back_door_response("Exit with zero quick"), "Passed line: Exit with zero quick");
}

void test_back_door_response_h1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('H', back_door_response("Stands so HIGH   "), "Passed line: Stands so HIGH   ");
}

void test_back_door_response_o2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('o', back_door_response("	Huge ... hooves ... too!"), "Passed line: 	Huge ... hooves ... too!");
}

void test_back_door_response_r2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('r', back_door_response("Impatiently waits for... 	 	"),
                                   "Passed line: Impatiently waits for... 	 	");
}

void test_back_door_response_s1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('s', back_door_response("    Reins and harness    "), "Passed line:     Reins and harness    ");
}

void test_back_door_response_e1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8_MESSAGE('E', back_door_response("Eager to LEAVE!!!"), "Passed line: Eager to LEAVE!!!");
}

void test_back_door_password_work(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    char letters[] = "work";
    back_door_password(buffer, letters);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Work, please.", buffer, "Combined letters are: work");
}

void test_back_door_password_horse(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    char letters[] = "horse";
    back_door_password(buffer, letters);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Horse, please.", buffer, "Combined letters are: horse");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_front_door_response_s1);
    RUN_TEST(test_front_door_response_u1);
    RUN_TEST(test_front_door_response_m1);
    RUN_TEST(test_front_door_response_m2);
    RUN_TEST(test_front_door_response_e1);
    RUN_TEST(test_front_door_response_r1);
    RUN_TEST(test_front_door_response_s2);
    RUN_TEST(test_front_door_response_o1);
    RUN_TEST(test_front_door_response_p1);
    RUN_TEST(test_front_door_response_h1);
    RUN_TEST(test_front_door_response_i1);
    RUN_TEST(test_front_door_response_a1);
    RUN_TEST(test_front_door_response_c1);
    RUN_TEST(test_front_door_response_o2);
    RUN_TEST(test_front_door_response_d1);
    RUN_TEST(test_front_door_response_e2);
    RUN_TEST(test_front_door_password_summer);
    RUN_TEST(test_front_door_password_sophia);
    RUN_TEST(test_front_door_password_code);
    RUN_TEST(test_back_door_response_w1);
    RUN_TEST(test_back_door_response_o1);
    RUN_TEST(test_back_door_response_r1);
    RUN_TEST(test_back_door_response_k1);
    RUN_TEST(test_back_door_response_h1);
    RUN_TEST(test_back_door_response_o2);
    RUN_TEST(test_back_door_response_r2);
    RUN_TEST(test_back_door_response_s1);
    RUN_TEST(test_back_door_response_e1);
    RUN_TEST(test_back_door_password_work);
    RUN_TEST(test_back_door_password_horse);
    return UNITY_END();
}
