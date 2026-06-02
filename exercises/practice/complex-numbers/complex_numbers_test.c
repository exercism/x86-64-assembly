#include "vendor/unity.h"

#include <stddef.h>

#define ASSERT_FLOAT(x, y)                            \
    do {                                              \
        float _dt = 0.0001f * ((x) < 0 ? -(x) : (x)); \
        float _tl = _dt > 0.00001f ? _dt : 0.00001f;  \
        TEST_ASSERT_FLOAT_WITHIN(_tl, (x), (y));      \
    } while (0)

#define ASSERT_COMPLEX(xr, xi, yr, yi)               \
    do {                                             \
        float _abxr = (xr) < 0 ? -(xr) : (xr);       \
        float _abxi = (xi) < 0 ? -(xi) : (xi);       \
        float _dist = _abxr > _abxi ? _abxr : _abxi; \
        float _dt = 0.0001f * _dist;                 \
        float _tl = _dt > 0.00001f ? _dt : 0.00001f; \
        TEST_ASSERT_FLOAT_WITHIN(_tl, (xr), (yr));   \
        TEST_ASSERT_FLOAT_WITHIN(_tl, (xi), (yi));   \
    } while (0)

typedef struct {
    float real;
    float imag;
} complex_t;

extern float complex_real(complex_t z);
extern float complex_imaginary(complex_t z);
extern complex_t complex_mul(complex_t z1, complex_t z2);
extern complex_t complex_add(complex_t z1, complex_t z2);
extern complex_t complex_sub(complex_t z1, complex_t z2);
extern complex_t complex_div(complex_t z1, complex_t z2);
extern float complex_abs(complex_t z);
extern complex_t complex_conjugate(complex_t z);
extern complex_t complex_exp(complex_t z);
extern complex_t complex_real_add(complex_t z1, float z2);
extern complex_t real_complex_add(float z1, complex_t z2);
extern complex_t complex_real_sub(complex_t z1, float z2);
extern complex_t real_complex_sub(float z1, complex_t z2);
extern complex_t complex_real_mul(complex_t z1, float z2);
extern complex_t real_complex_mul(float z1, complex_t z2);
extern complex_t complex_real_div(complex_t z1, float z2);
extern complex_t real_complex_div(float z1, complex_t z2);

void setUp(void) {
}

void tearDown(void) {
}

void test_real_part_of_a_purely_real_number(void) {
    const complex_t z = {1, 0};
    const float result = complex_real(z);
    const float expected = 1;

    ASSERT_FLOAT(expected, result);
}

void test_real_part_of_a_purely_imaginary_number(void) {
    TEST_IGNORE();

    const complex_t z = {0, 1};
    const float result = complex_real(z);
    const float expected = 0;

    ASSERT_FLOAT(expected, result);
}

void test_real_part_of_a_number_with_real_and_imaginary_part(void) {
    TEST_IGNORE();

    const complex_t z = {1, 2};
    const float result = complex_real(z);
    const float expected = 1;

    ASSERT_FLOAT(expected, result);
}

void test_imaginary_part_of_a_purely_real_number(void) {
    TEST_IGNORE();

    const complex_t z = {1, 0};
    const float result = complex_imaginary(z);
    const float expected = 0;

    ASSERT_FLOAT(expected, result);
}

void test_imaginary_part_of_a_purely_imaginary_number(void) {
    TEST_IGNORE();

    const complex_t z = {0, 1};
    const float result = complex_imaginary(z);
    const float expected = 1;

    ASSERT_FLOAT(expected, result);
}

void test_imaginary_part_of_a_number_with_real_and_imaginary_part(void) {
    TEST_IGNORE();

    const complex_t z = {1, 2};
    const float result = complex_imaginary(z);
    const float expected = 2;

    ASSERT_FLOAT(expected, result);
}

void test_imaginary_unit(void) {
    TEST_IGNORE();

    const complex_t z1 = {0, 1};
    const complex_t z2 = {0, 1};
    const complex_t result = complex_mul(z1, z2);
    const complex_t expected = {-1, 0};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_add_purely_real_numbers(void) {
    TEST_IGNORE();

    const complex_t z1 = {1, 0};
    const complex_t z2 = {2, 0};
    const complex_t result = complex_add(z1, z2);
    const complex_t expected = {3, 0};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_add_purely_imaginary_numbers(void) {
    TEST_IGNORE();

    const complex_t z1 = {0, 1};
    const complex_t z2 = {0, 2};
    const complex_t result = complex_add(z1, z2);
    const complex_t expected = {0, 3};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_add_numbers_with_real_and_imaginary_part(void) {
    TEST_IGNORE();

    const complex_t z1 = {1, 2};
    const complex_t z2 = {3, 4};
    const complex_t result = complex_add(z1, z2);
    const complex_t expected = {4, 6};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_subtract_purely_real_numbers(void) {
    TEST_IGNORE();

    const complex_t z1 = {1, 0};
    const complex_t z2 = {2, 0};
    const complex_t result = complex_sub(z1, z2);
    const complex_t expected = {-1, 0};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_subtract_purely_imaginary_numbers(void) {
    TEST_IGNORE();

    const complex_t z1 = {0, 1};
    const complex_t z2 = {0, 2};
    const complex_t result = complex_sub(z1, z2);
    const complex_t expected = {0, -1};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_subtract_numbers_with_real_and_imaginary_part(void) {
    TEST_IGNORE();

    const complex_t z1 = {1, 2};
    const complex_t z2 = {3, 4};
    const complex_t result = complex_sub(z1, z2);
    const complex_t expected = {-2, -2};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_multiply_purely_real_numbers(void) {
    TEST_IGNORE();

    const complex_t z1 = {1, 0};
    const complex_t z2 = {2, 0};
    const complex_t result = complex_mul(z1, z2);
    const complex_t expected = {2, 0};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_multiply_purely_imaginary_numbers(void) {
    TEST_IGNORE();

    const complex_t z1 = {0, 1};
    const complex_t z2 = {0, 2};
    const complex_t result = complex_mul(z1, z2);
    const complex_t expected = {-2, 0};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_multiply_numbers_with_real_and_imaginary_part(void) {
    TEST_IGNORE();

    const complex_t z1 = {1, 2};
    const complex_t z2 = {3, 4};
    const complex_t result = complex_mul(z1, z2);
    const complex_t expected = {-5, 10};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_divide_purely_real_numbers(void) {
    TEST_IGNORE();

    const complex_t z1 = {1, 0};
    const complex_t z2 = {2, 0};
    const complex_t result = complex_div(z1, z2);
    const complex_t expected = {0.5, 0};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_divide_purely_imaginary_numbers(void) {
    TEST_IGNORE();

    const complex_t z1 = {0, 1};
    const complex_t z2 = {0, 2};
    const complex_t result = complex_div(z1, z2);
    const complex_t expected = {0.5, 0};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_divide_numbers_with_real_and_imaginary_part(void) {
    TEST_IGNORE();

    const complex_t z1 = {1, 2};
    const complex_t z2 = {3, 4};
    const complex_t result = complex_div(z1, z2);
    const complex_t expected = {0.44, 0.08};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_absolute_value_of_a_positive_purely_real_number(void) {
    TEST_IGNORE();

    const complex_t z = {5, 0};
    const float result = complex_abs(z);
    const float expected = 5;

    ASSERT_FLOAT(expected, result);
}

void test_absolute_value_of_a_negative_purely_real_number(void) {
    TEST_IGNORE();

    const complex_t z = {-5, 0};
    const float result = complex_abs(z);
    const float expected = 5;

    ASSERT_FLOAT(expected, result);
}

void test_absolute_value_of_a_purely_imaginary_number_with_positive_imaginary_part(void) {
    TEST_IGNORE();

    const complex_t z = {0, 5};
    const float result = complex_abs(z);
    const float expected = 5;

    ASSERT_FLOAT(expected, result);
}

void test_absolute_value_of_a_purely_imaginary_number_with_negative_imaginary_part(void) {
    TEST_IGNORE();

    const complex_t z = {0, -5};
    const float result = complex_abs(z);
    const float expected = 5;

    ASSERT_FLOAT(expected, result);
}

void test_absolute_value_of_a_number_with_real_and_imaginary_part(void) {
    TEST_IGNORE();

    const complex_t z = {3, 4};
    const float result = complex_abs(z);
    const float expected = 5;

    ASSERT_FLOAT(expected, result);
}

void test_conjugate_a_purely_real_number(void) {
    TEST_IGNORE();

    const complex_t z = {5, 0};
    const complex_t result = complex_conjugate(z);
    const complex_t expected = {5, 0};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_conjugate_a_purely_imaginary_number(void) {
    TEST_IGNORE();

    const complex_t z = {0, 5};
    const complex_t result = complex_conjugate(z);
    const complex_t expected = {0, -5};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_conjugate_a_number_with_real_and_imaginary_part(void) {
    TEST_IGNORE();

    const complex_t z = {1, 1};
    const complex_t result = complex_conjugate(z);
    const complex_t expected = {1, -1};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_eulers_identityformula(void) {
    TEST_IGNORE();

    const complex_t z = {0, 3.141592653589793};
    const complex_t result = complex_exp(z);
    const complex_t expected = {-1, 0};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_exponential_of_0(void) {
    TEST_IGNORE();

    const complex_t z = {0, 0};
    const complex_t result = complex_exp(z);
    const complex_t expected = {1, 0};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_exponential_of_a_purely_real_number(void) {
    TEST_IGNORE();

    const complex_t z = {1, 0};
    const complex_t result = complex_exp(z);
    const complex_t expected = {2.718281828459045, 0};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_exponential_of_a_number_with_real_and_imaginary_part(void) {
    TEST_IGNORE();

    const complex_t z = {0.6931471805599453, 3.141592653589793};
    const complex_t result = complex_exp(z);
    const complex_t expected = {-2, 0};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_exponential_resulting_in_a_number_with_real_and_imaginary_part(void) {
    TEST_IGNORE();

    const complex_t z = {0.6931471805599453 / 2, 3.141592653589793 / 4};
    const complex_t result = complex_exp(z);
    const complex_t expected = {1, 1};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_add_real_number_to_complex_number(void) {
    TEST_IGNORE();

    const complex_t z1 = {1, 2};
    const float z2 = 5;
    const complex_t result = complex_real_add(z1, z2);
    const complex_t expected = {6, 2};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_add_complex_number_to_real_number(void) {
    TEST_IGNORE();

    const float z1 = 5;
    const complex_t z2 = {1, 2};
    const complex_t result = real_complex_add(z1, z2);
    const complex_t expected = {6, 2};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_subtract_real_number_from_complex_number(void) {
    TEST_IGNORE();

    const complex_t z1 = {5, 7};
    const float z2 = 4;
    const complex_t result = complex_real_sub(z1, z2);
    const complex_t expected = {1, 7};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_subtract_complex_number_from_real_number(void) {
    TEST_IGNORE();

    const float z1 = 4;
    const complex_t z2 = {5, 7};
    const complex_t result = real_complex_sub(z1, z2);
    const complex_t expected = {-1, -7};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_multiply_complex_number_by_real_number(void) {
    TEST_IGNORE();

    const complex_t z1 = {2, 5};
    const float z2 = 5;
    const complex_t result = complex_real_mul(z1, z2);
    const complex_t expected = {10, 25};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_multiply_real_number_by_complex_number(void) {
    TEST_IGNORE();

    const float z1 = 5;
    const complex_t z2 = {2, 5};
    const complex_t result = real_complex_mul(z1, z2);
    const complex_t expected = {10, 25};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_divide_complex_number_by_real_number(void) {
    TEST_IGNORE();

    const complex_t z1 = {10, 100};
    const float z2 = 10;
    const complex_t result = complex_real_div(z1, z2);
    const complex_t expected = {1, 10};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_divide_real_number_by_complex_number(void) {
    TEST_IGNORE();

    const float z1 = 5;
    const complex_t z2 = {1, 1};
    const complex_t result = real_complex_div(z1, z2);
    const complex_t expected = {2.5, -2.5};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_exponential_with_a_large_real_part_magnitude_e5_both_components_sizable(void) {
    TEST_IGNORE();

    const complex_t z = {5, 1};
    const complex_t result = complex_exp(z);
    const complex_t expected = {80.187972, 124.885367};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_exponential_with_a_large_real_part_magnitude_e7_secondquadrant_angle(void) {
    TEST_IGNORE();

    const complex_t z = {7, 2};
    const complex_t result = complex_exp(z);
    const complex_t expected = {-456.36042, 997.165709};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_exponential_with_a_large_real_part_magnitude_e6_negative_angle(void) {
    TEST_IGNORE();

    const complex_t z = {6, -2};
    const complex_t result = complex_exp(z);
    const complex_t expected = {-167.885616, -366.836764};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_exponential_with_a_large_real_part_magnitude_e4_fourthquadrant_angle(void) {
    TEST_IGNORE();

    const complex_t z = {4, -2.5};
    const complex_t result = complex_exp(z);
    const complex_t expected = {-43.740959, -32.675472};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_regression_residual_angle_near_pi2_failed_before_sincos_fix(void) {
    TEST_IGNORE();

    const complex_t z = {-0.3, 1.5};
    const complex_t result = complex_exp(z);
    const complex_t expected = {0.052403, 0.738962};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_regression_residual_angle_near_pi2_second_case(void) {
    TEST_IGNORE();

    const complex_t z = {-0.2, 1.5};
    const complex_t result = complex_exp(z);
    const complex_t expected = {0.057915, 0.81668};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_regression_thirdquadrant_angle_nearzero_second_component(void) {
    TEST_IGNORE();

    const complex_t z = {-0.1, -3.25};
    const complex_t result = complex_exp(z);
    const complex_t expected = {-0.899526, 0.097899};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

void test_regression_residual_angle_near_pi2_third_case(void) {
    TEST_IGNORE();

    const complex_t z = {-0.1, 1.5};
    const complex_t result = complex_exp(z);
    const complex_t expected = {0.064006, 0.902571};

    ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_real_part_of_a_purely_real_number);
    RUN_TEST(test_real_part_of_a_purely_imaginary_number);
    RUN_TEST(test_real_part_of_a_number_with_real_and_imaginary_part);
    RUN_TEST(test_imaginary_part_of_a_purely_real_number);
    RUN_TEST(test_imaginary_part_of_a_purely_imaginary_number);
    RUN_TEST(test_imaginary_part_of_a_number_with_real_and_imaginary_part);
    RUN_TEST(test_imaginary_unit);
    RUN_TEST(test_add_purely_real_numbers);
    RUN_TEST(test_add_purely_imaginary_numbers);
    RUN_TEST(test_add_numbers_with_real_and_imaginary_part);
    RUN_TEST(test_subtract_purely_real_numbers);
    RUN_TEST(test_subtract_purely_imaginary_numbers);
    RUN_TEST(test_subtract_numbers_with_real_and_imaginary_part);
    RUN_TEST(test_multiply_purely_real_numbers);
    RUN_TEST(test_multiply_purely_imaginary_numbers);
    RUN_TEST(test_multiply_numbers_with_real_and_imaginary_part);
    RUN_TEST(test_divide_purely_real_numbers);
    RUN_TEST(test_divide_purely_imaginary_numbers);
    RUN_TEST(test_divide_numbers_with_real_and_imaginary_part);
    RUN_TEST(test_absolute_value_of_a_positive_purely_real_number);
    RUN_TEST(test_absolute_value_of_a_negative_purely_real_number);
    RUN_TEST(test_absolute_value_of_a_purely_imaginary_number_with_positive_imaginary_part);
    RUN_TEST(test_absolute_value_of_a_purely_imaginary_number_with_negative_imaginary_part);
    RUN_TEST(test_absolute_value_of_a_number_with_real_and_imaginary_part);
    RUN_TEST(test_conjugate_a_purely_real_number);
    RUN_TEST(test_conjugate_a_purely_imaginary_number);
    RUN_TEST(test_conjugate_a_number_with_real_and_imaginary_part);
    RUN_TEST(test_eulers_identityformula);
    RUN_TEST(test_exponential_of_0);
    RUN_TEST(test_exponential_of_a_purely_real_number);
    RUN_TEST(test_exponential_of_a_number_with_real_and_imaginary_part);
    RUN_TEST(test_exponential_resulting_in_a_number_with_real_and_imaginary_part);
    RUN_TEST(test_add_real_number_to_complex_number);
    RUN_TEST(test_add_complex_number_to_real_number);
    RUN_TEST(test_subtract_real_number_from_complex_number);
    RUN_TEST(test_subtract_complex_number_from_real_number);
    RUN_TEST(test_multiply_complex_number_by_real_number);
    RUN_TEST(test_multiply_real_number_by_complex_number);
    RUN_TEST(test_divide_complex_number_by_real_number);
    RUN_TEST(test_divide_real_number_by_complex_number);
    RUN_TEST(test_exponential_with_a_large_real_part_magnitude_e5_both_components_sizable);
    RUN_TEST(test_exponential_with_a_large_real_part_magnitude_e7_secondquadrant_angle);
    RUN_TEST(test_exponential_with_a_large_real_part_magnitude_e6_negative_angle);
    RUN_TEST(test_exponential_with_a_large_real_part_magnitude_e4_fourthquadrant_angle);
    RUN_TEST(test_regression_residual_angle_near_pi2_failed_before_sincos_fix);
    RUN_TEST(test_regression_residual_angle_near_pi2_second_case);
    RUN_TEST(test_regression_thirdquadrant_angle_nearzero_second_component);
    RUN_TEST(test_regression_residual_angle_near_pi2_third_case);
    return UNITY_END();
}
