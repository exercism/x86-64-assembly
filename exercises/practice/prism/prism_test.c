#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>

#define BUFFER_SIZE 128
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef struct {
    float x;
    float y;
    float angle;
} coordinate_t;

typedef struct {
    uint32_t id;
    coordinate_t coordinates;
} prism_t;

extern size_t find_sequence(uint32_t buffer[], const coordinate_t start, const prism_t *prisms, size_t num_prisms);

void setUp(void) {
}

void tearDown(void) {
}

void test_zero_prisms(void) {
    const coordinate_t start = {.x = 0, .y = 0, .angle = 0};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    const size_t result = find_sequence(buffer, start, NULL, 0);
    TEST_ASSERT_EQUAL_UINT64(0, result);
}

void test_one_prism_one_hit(void) {
    TEST_IGNORE();
    const coordinate_t start = {.x = 0, .y = 0, .angle = 0};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    alignas(64) const prism_t prisms[] = {{.id = 1, .coordinates = {.x = 10, .y = 0, .angle = 0}}};
    const size_t result = find_sequence(buffer, start, prisms, ARRAY_SIZE(prisms));
    const uint32_t expected[] = {1};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), result);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_one_prism_zero_hits(void) {
    TEST_IGNORE();
    const coordinate_t start = {.x = 0, .y = 0, .angle = 0};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    alignas(64) const prism_t prisms[] = {{.id = 1, .coordinates = {.x = -10, .y = 0, .angle = 0}}};
    const size_t result = find_sequence(buffer, start, prisms, ARRAY_SIZE(prisms));
    TEST_ASSERT_EQUAL_UINT64(0, result);
}

void test_going_up_zero_hits(void) {
    TEST_IGNORE();
    const coordinate_t start = {.x = 0, .y = 0, .angle = 90};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    alignas(64) const prism_t prisms[] = {{.id = 3, .coordinates = {.x = 0, .y = -10, .angle = 0}},
                                          {.id = 1, .coordinates = {.x = -10, .y = 0, .angle = 0}},
                                          {.id = 2, .coordinates = {.x = 10, .y = 0, .angle = 0}}};
    const size_t result = find_sequence(buffer, start, prisms, ARRAY_SIZE(prisms));
    TEST_ASSERT_EQUAL_UINT64(0, result);
}

void test_going_down_zero_hits(void) {
    TEST_IGNORE();
    const coordinate_t start = {.x = 0, .y = 0, .angle = -90};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    alignas(64) const prism_t prisms[] = {{.id = 1, .coordinates = {.x = 10, .y = 0, .angle = 0}},
                                          {.id = 2, .coordinates = {.x = 0, .y = 10, .angle = 0}},
                                          {.id = 3, .coordinates = {.x = -10, .y = 0, .angle = 0}}};
    const size_t result = find_sequence(buffer, start, prisms, ARRAY_SIZE(prisms));
    TEST_ASSERT_EQUAL_UINT64(0, result);
}

void test_going_left_zero_hits(void) {
    TEST_IGNORE();
    const coordinate_t start = {.x = 0, .y = 0, .angle = 180};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    alignas(64) const prism_t prisms[] = {{.id = 2, .coordinates = {.x = 0, .y = 10, .angle = 0}},
                                          {.id = 3, .coordinates = {.x = 10, .y = 0, .angle = 0}},
                                          {.id = 1, .coordinates = {.x = 0, .y = -10, .angle = 0}}};
    const size_t result = find_sequence(buffer, start, prisms, ARRAY_SIZE(prisms));
    TEST_ASSERT_EQUAL_UINT64(0, result);
}

void test_negative_angle(void) {
    TEST_IGNORE();
    const coordinate_t start = {.x = 0, .y = 0, .angle = -180};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    alignas(64) const prism_t prisms[] = {{.id = 1, .coordinates = {.x = 0, .y = -10, .angle = 0}},
                                          {.id = 2, .coordinates = {.x = 0, .y = 10, .angle = 0}},
                                          {.id = 3, .coordinates = {.x = 10, .y = 0, .angle = 0}}};
    const size_t result = find_sequence(buffer, start, prisms, ARRAY_SIZE(prisms));
    TEST_ASSERT_EQUAL_UINT64(0, result);
}

void test_large_angle(void) {
    TEST_IGNORE();
    const coordinate_t start = {.x = 0, .y = 0, .angle = 2340};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    alignas(64) const prism_t prisms[] = {{.id = 1, .coordinates = {.x = 10, .y = 0, .angle = 0}}};
    const size_t result = find_sequence(buffer, start, prisms, ARRAY_SIZE(prisms));
    TEST_ASSERT_EQUAL_UINT64(0, result);
}

void test_upward_refraction_two_hits(void) {
    TEST_IGNORE();
    const coordinate_t start = {.x = 0, .y = 0, .angle = 0};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    alignas(64) const prism_t prisms[] = {{.id = 1, .coordinates = {.x = 10, .y = 10, .angle = 0}},
                                          {.id = 2, .coordinates = {.x = 10, .y = 0, .angle = 90}}};
    const size_t result = find_sequence(buffer, start, prisms, ARRAY_SIZE(prisms));
    const uint32_t expected[] = {2, 1};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), result);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_downward_refraction_two_hits(void) {
    TEST_IGNORE();
    const coordinate_t start = {.x = 0, .y = 0, .angle = 0};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    alignas(64) const prism_t prisms[] = {{.id = 1, .coordinates = {.x = 10, .y = 0, .angle = -90}},
                                          {.id = 2, .coordinates = {.x = 10, .y = -10, .angle = 0}}};
    const size_t result = find_sequence(buffer, start, prisms, ARRAY_SIZE(prisms));
    const uint32_t expected[] = {1, 2};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), result);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_same_prism_twice(void) {
    TEST_IGNORE();
    const coordinate_t start = {.x = 0, .y = 0, .angle = 0};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    alignas(64) const prism_t prisms[] = {{.id = 2, .coordinates = {.x = 10, .y = 0, .angle = 0}},
                                          {.id = 1, .coordinates = {.x = 20, .y = 0, .angle = -180}}};
    const size_t result = find_sequence(buffer, start, prisms, ARRAY_SIZE(prisms));
    const uint32_t expected[] = {2, 1, 2};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), result);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_simple_path(void) {
    TEST_IGNORE();
    const coordinate_t start = {.x = 0, .y = 0, .angle = 0};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    alignas(64) const prism_t prisms[] = {{.id = 3, .coordinates = {.x = 30, .y = 10, .angle = 45}},
                                          {.id = 1, .coordinates = {.x = 10, .y = 10, .angle = -90}},
                                          {.id = 2, .coordinates = {.x = 10, .y = 0, .angle = 90}},
                                          {.id = 4, .coordinates = {.x = 20, .y = 0, .angle = 0}}};
    const size_t result = find_sequence(buffer, start, prisms, ARRAY_SIZE(prisms));
    const uint32_t expected[] = {2, 1, 3};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), result);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_multiple_prisms_floating_point_precision(void) {
    TEST_IGNORE();
    const coordinate_t start = {.x = 0, .y = 0, .angle = -6.429};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    alignas(64) const prism_t prisms[] = {{.id = 26, .coordinates = {.x = 5.8, .y = 73.4, .angle = 6.555}},
                                          {.id = 24, .coordinates = {.x = 36.2, .y = 65.2, .angle = -0.304}},
                                          {.id = 20, .coordinates = {.x = 20.4, .y = 82.8, .angle = 45.17}},
                                          {.id = 31, .coordinates = {.x = -20.2, .y = 48.8, .angle = 30.615}},
                                          {.id = 30, .coordinates = {.x = 24.0, .y = 0.6, .angle = 28.771}},
                                          {.id = 29, .coordinates = {.x = 31.4, .y = 79.4, .angle = 61.327}},
                                          {.id = 28, .coordinates = {.x = 36.4, .y = 31.4, .angle = -18.157}},
                                          {.id = 22, .coordinates = {.x = 47.0, .y = 57.8, .angle = 54.745}},
                                          {.id = 38, .coordinates = {.x = 36.4, .y = 79.2, .angle = 49.05}},
                                          {.id = 10, .coordinates = {.x = 37.8, .y = 55.2, .angle = 11.978}},
                                          {.id = 18, .coordinates = {.x = -26.0, .y = 42.6, .angle = 22.661}},
                                          {.id = 25, .coordinates = {.x = 38.8, .y = 76.2, .angle = 51.958}},
                                          {.id = 2, .coordinates = {.x = 0.0, .y = 42.4, .angle = -21.817}},
                                          {.id = 35, .coordinates = {.x = 21.4, .y = 44.8, .angle = -171.579}},
                                          {.id = 7, .coordinates = {.x = 14.2, .y = -1.6, .angle = 19.081}},
                                          {.id = 33, .coordinates = {.x = 11.2, .y = 44.4, .angle = -165.941}},
                                          {.id = 11, .coordinates = {.x = 15.4, .y = 82.6, .angle = 66.262}},
                                          {.id = 16, .coordinates = {.x = 30.8, .y = 6.6, .angle = 35.852}},
                                          {.id = 15, .coordinates = {.x = -3.0, .y = 79.2, .angle = 53.782}},
                                          {.id = 4, .coordinates = {.x = 29.0, .y = 75.4, .angle = 17.016}},
                                          {.id = 23, .coordinates = {.x = 41.6, .y = 59.8, .angle = 70.763}},
                                          {.id = 8, .coordinates = {.x = -10.0, .y = 15.8, .angle = -9.24}},
                                          {.id = 13, .coordinates = {.x = 48.6, .y = 51.8, .angle = 45.812}},
                                          {.id = 1, .coordinates = {.x = 13.2, .y = 77.0, .angle = 17.937}},
                                          {.id = 34, .coordinates = {.x = -8.8, .y = 36.8, .angle = -4.199}},
                                          {.id = 21, .coordinates = {.x = 24.4, .y = 75.8, .angle = 20.783}},
                                          {.id = 17, .coordinates = {.x = -4.4, .y = 74.6, .angle = 24.709}},
                                          {.id = 9, .coordinates = {.x = 30.8, .y = 41.8, .angle = -165.413}},
                                          {.id = 32, .coordinates = {.x = 4.2, .y = 78.6, .angle = 40.892}},
                                          {.id = 37, .coordinates = {.x = -15.8, .y = 47.0, .angle = 33.29}},
                                          {.id = 6, .coordinates = {.x = 1.0, .y = 80.6, .angle = 51.295}},
                                          {.id = 36, .coordinates = {.x = -27.0, .y = 47.8, .angle = 92.52}},
                                          {.id = 14, .coordinates = {.x = -2.0, .y = 34.4, .angle = -52.001}},
                                          {.id = 5, .coordinates = {.x = 23.2, .y = 80.2, .angle = 31.866}},
                                          {.id = 27, .coordinates = {.x = -5.6, .y = 32.8, .angle = -75.303}},
                                          {.id = 12, .coordinates = {.x = -1.0, .y = 0.2, .angle = 0.0}},
                                          {.id = 3, .coordinates = {.x = -6.6, .y = 3.2, .angle = 46.72}},
                                          {.id = 19, .coordinates = {.x = -13.8, .y = 24.2, .angle = -9.205}}};
    const size_t result = find_sequence(buffer, start, prisms, ARRAY_SIZE(prisms));
    const uint32_t expected[] = {7, 30, 16, 28, 13, 22, 23, 10, 9,  24, 25, 38, 29, 4,  35, 21, 5, 20, 11,
                                 1, 33, 26, 32, 6,  15, 17, 2,  14, 27, 34, 37, 31, 36, 18, 19, 8, 3,  12};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), result);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_complex_path_with_multiple_prisms_floating_point_precision(void) {
    TEST_IGNORE();
    const coordinate_t start = {.x = 0, .y = 0, .angle = 0.0};
    alignas(64) uint32_t buffer[BUFFER_SIZE];
    alignas(64) const prism_t prisms[] = {{.id = 46, .coordinates = {.x = 37.4, .y = 20.6, .angle = -88.332}},
                                          {.id = 72, .coordinates = {.x = -24.2, .y = 23.4, .angle = -90.774}},
                                          {.id = 25, .coordinates = {.x = 78.6, .y = 7.8, .angle = 98.562}},
                                          {.id = 60, .coordinates = {.x = -58.8, .y = 31.6, .angle = 115.56}},
                                          {.id = 22, .coordinates = {.x = 75.2, .y = 28.0, .angle = 63.515}},
                                          {.id = 2, .coordinates = {.x = 89.8, .y = 27.8, .angle = 91.176}},
                                          {.id = 23, .coordinates = {.x = 9.8, .y = 30.8, .angle = 30.829}},
                                          {.id = 69, .coordinates = {.x = 22.8, .y = 20.6, .angle = -88.315}},
                                          {.id = 44, .coordinates = {.x = -0.8, .y = 15.6, .angle = -116.565}},
                                          {.id = 36, .coordinates = {.x = -24.2, .y = 8.2, .angle = -90.0}},
                                          {.id = 53, .coordinates = {.x = -1.2, .y = 0.0, .angle = 0.0}},
                                          {.id = 52, .coordinates = {.x = 14.2, .y = 24.0, .angle = -143.896}},
                                          {.id = 5, .coordinates = {.x = -65.2, .y = 21.6, .angle = 93.128}},
                                          {.id = 66, .coordinates = {.x = 5.4, .y = 15.6, .angle = 31.608}},
                                          {.id = 51, .coordinates = {.x = -72.6, .y = 21.0, .angle = -100.976}},
                                          {.id = 65, .coordinates = {.x = 48.0, .y = 10.2, .angle = 87.455}},
                                          {.id = 21, .coordinates = {.x = -41.8, .y = 0.0, .angle = 68.352}},
                                          {.id = 18, .coordinates = {.x = -46.2, .y = 19.2, .angle = -128.362}},
                                          {.id = 10, .coordinates = {.x = 74.4, .y = 0.4, .angle = 90.939}},
                                          {.id = 15, .coordinates = {.x = 67.6, .y = 0.4, .angle = 84.958}},
                                          {.id = 35, .coordinates = {.x = 14.8, .y = -0.4, .angle = 89.176}},
                                          {.id = 1, .coordinates = {.x = 83.0, .y = 0.2, .angle = 89.105}},
                                          {.id = 68, .coordinates = {.x = 14.6, .y = 28.0, .angle = -29.867}},
                                          {.id = 67, .coordinates = {.x = 79.8, .y = 18.6, .angle = -136.643}},
                                          {.id = 38, .coordinates = {.x = 53.0, .y = 14.6, .angle = -90.848}},
                                          {.id = 31, .coordinates = {.x = -58.0, .y = 6.6, .angle = -61.837}},
                                          {.id = 74, .coordinates = {.x = -30.8, .y = 0.4, .angle = 85.966}},
                                          {.id = 48, .coordinates = {.x = -4.6, .y = 10.0, .angle = -161.222}},
                                          {.id = 12, .coordinates = {.x = 59.0, .y = 5.0, .angle = -91.164}},
                                          {.id = 33, .coordinates = {.x = -16.4, .y = 18.4, .angle = 90.734}},
                                          {.id = 4, .coordinates = {.x = 82.6, .y = 27.6, .angle = 71.127}},
                                          {.id = 75, .coordinates = {.x = -10.2, .y = 30.6, .angle = -1.108}},
                                          {.id = 28, .coordinates = {.x = 38.0, .y = 0.0, .angle = 86.863}},
                                          {.id = 11, .coordinates = {.x = 64.4, .y = -0.2, .angle = 92.353}},
                                          {.id = 9, .coordinates = {.x = -51.4, .y = 31.6, .angle = 67.249}},
                                          {.id = 26, .coordinates = {.x = -39.8, .y = 30.8, .angle = 61.113}},
                                          {.id = 30, .coordinates = {.x = -34.2, .y = 0.6, .angle = 111.33}},
                                          {.id = 56, .coordinates = {.x = -51.0, .y = 0.2, .angle = 70.445}},
                                          {.id = 41, .coordinates = {.x = -12.0, .y = 0.0, .angle = 91.219}},
                                          {.id = 24, .coordinates = {.x = 63.8, .y = 14.4, .angle = 86.586}},
                                          {.id = 70, .coordinates = {.x = -72.8, .y = 13.4, .angle = -87.238}},
                                          {.id = 3, .coordinates = {.x = 22.4, .y = 7.0, .angle = -91.685}},
                                          {.id = 13, .coordinates = {.x = 34.4, .y = 7.0, .angle = 90.0}},
                                          {.id = 16, .coordinates = {.x = -47.4, .y = 11.4, .angle = -136.02}},
                                          {.id = 6, .coordinates = {.x = 90.0, .y = 0.2, .angle = 90.415}},
                                          {.id = 54, .coordinates = {.x = 44.0, .y = 27.8, .angle = 85.969}},
                                          {.id = 32, .coordinates = {.x = -9.0, .y = 0.0, .angle = 91.615}},
                                          {.id = 8, .coordinates = {.x = -31.6, .y = 30.8, .angle = 0.535}},
                                          {.id = 39, .coordinates = {.x = -12.0, .y = 8.2, .angle = 90.0}},
                                          {.id = 14, .coordinates = {.x = -79.6, .y = 32.4, .angle = 92.342}},
                                          {.id = 42, .coordinates = {.x = 65.8, .y = 20.8, .angle = -85.867}},
                                          {.id = 40, .coordinates = {.x = -65.0, .y = 14.0, .angle = 87.109}},
                                          {.id = 45, .coordinates = {.x = 10.6, .y = 18.8, .angle = 23.697}},
                                          {.id = 71, .coordinates = {.x = -24.2, .y = 18.6, .angle = -88.531}},
                                          {.id = 7, .coordinates = {.x = -72.6, .y = 6.4, .angle = -89.148}},
                                          {.id = 62, .coordinates = {.x = -32.0, .y = 24.8, .angle = -140.8}},
                                          {.id = 49, .coordinates = {.x = 34.4, .y = -0.2, .angle = 89.415}},
                                          {.id = 63, .coordinates = {.x = 74.2, .y = 12.6, .angle = -138.429}},
                                          {.id = 59, .coordinates = {.x = 82.8, .y = 13.0, .angle = -140.177}},
                                          {.id = 34, .coordinates = {.x = -9.4, .y = 23.2, .angle = -88.238}},
                                          {.id = 76, .coordinates = {.x = -57.6, .y = 0.0, .angle = 1.2}},
                                          {.id = 43, .coordinates = {.x = 7.0, .y = 0.0, .angle = 116.565}},
                                          {.id = 20, .coordinates = {.x = 45.8, .y = -0.2, .angle = 1.469}},
                                          {.id = 37, .coordinates = {.x = -16.6, .y = 13.2, .angle = 84.785}},
                                          {.id = 58, .coordinates = {.x = -79.0, .y = -0.2, .angle = 89.481}},
                                          {.id = 50, .coordinates = {.x = -24.2, .y = 12.8, .angle = -86.987}},
                                          {.id = 64, .coordinates = {.x = 59.2, .y = 10.2, .angle = -92.203}},
                                          {.id = 61, .coordinates = {.x = -72.0, .y = 26.4, .angle = -83.66}},
                                          {.id = 47, .coordinates = {.x = 45.4, .y = 5.8, .angle = -82.992}},
                                          {.id = 17, .coordinates = {.x = -52.2, .y = 17.8, .angle = -52.938}},
                                          {.id = 57, .coordinates = {.x = -61.8, .y = 32.0, .angle = 84.627}},
                                          {.id = 29, .coordinates = {.x = 47.2, .y = 28.2, .angle = 92.954}},
                                          {.id = 27, .coordinates = {.x = -4.6, .y = 0.2, .angle = 87.397}},
                                          {.id = 55, .coordinates = {.x = -61.4, .y = 26.4, .angle = 94.086}},
                                          {.id = 73, .coordinates = {.x = -40.4, .y = 13.4, .angle = -62.229}},
                                          {.id = 19, .coordinates = {.x = 53.2, .y = 20.6, .angle = -87.181}}};
    const size_t result = find_sequence(buffer, start, prisms, ARRAY_SIZE(prisms));
    const uint32_t expected[] = {43, 44, 66, 45, 52, 35, 49, 13, 3,  69, 46, 28, 20, 11, 24, 38, 19, 42, 15, 10, 63, 25, 59, 1,  6,  2,
                                 4,  67, 22, 29, 65, 64, 12, 47, 54, 68, 23, 75, 8,  26, 18, 9,  60, 17, 31, 7,  70, 40, 5,  51, 61, 55,
                                 57, 14, 58, 76, 56, 16, 21, 30, 73, 62, 74, 41, 39, 36, 50, 37, 33, 71, 72, 34, 32, 27, 48, 53};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), result);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_zero_prisms);
    RUN_TEST(test_one_prism_one_hit);
    RUN_TEST(test_one_prism_zero_hits);
    RUN_TEST(test_going_up_zero_hits);
    RUN_TEST(test_going_down_zero_hits);
    RUN_TEST(test_going_left_zero_hits);
    RUN_TEST(test_negative_angle);
    RUN_TEST(test_large_angle);
    RUN_TEST(test_upward_refraction_two_hits);
    RUN_TEST(test_downward_refraction_two_hits);
    RUN_TEST(test_same_prism_twice);
    RUN_TEST(test_simple_path);
    RUN_TEST(test_multiple_prisms_floating_point_precision);
    RUN_TEST(test_complex_path_with_multiple_prisms_floating_point_precision);
    return UNITY_END();
}
