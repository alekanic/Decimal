#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

#define MINUS 0b10000000000000000000000000000000
// единица
#define ONE 0b00000000000000000000000000000001
// двойка
#define TWO 0b00000000000000000000000000000010
// 4294967295 (максимальное число для uint)
#define MAX_UINT 0b11111111111111111111111111111111
// 2147483647 (максимальное число для int)
#define MAX_INT 0b01111111111111111111111111111111
// 4294967294 - предпоследнее число для uint
#define PREVIOUS_UINT 0b11111111111111111111111111111110
// экспонента 28
#define MAX_EXPONENT 0b00000000000111000000000000000000
// экспонента 29
#define TOO_MUCH_EXPONENT 0b00000000000111010000000000000000
// экспонента 27
#define EXPONENT_27 0b00000000000110110000000000000000
// экспонента 1
#define EXPONENT_1 0b00000000000000010000000000000000
// экспонента 2
#define EXPONENT_2 0b00000000000000100000000000000000
// экспонента 1 и знак -
#define MINUS_AND_EXPONENT_1 0b10000000000000010000000000000000
#define MINUS_AND_MAX_EXPONENT 0b10000000000111000000000000000000
// максимальное число для инт
#define MAX_NUM_INT 2147483647

// arithmetic
Suite *suite_s21_add(void);
Suite *suite_s21_div(void);
Suite *suite_s21_mul(void);
Suite *suite_s21_sub(void);

// comparison
Suite *suite_s21_is_equal(void);
Suite *suite_s21_is_greater_or_equal(void);
Suite *suite_s21_is_greater(void);
Suite *suite_s21_is_less_or_equal(void);
Suite *suite_s21_is_less(void);
Suite *suite_s21_is_not_equal(void);

// convertation
Suite *suite_s21_from_float_to_decimal(void);
Suite *suite_s21_from_int_to_decimal(void);
Suite *suite_s21_from_decimal_to_float(void);
Suite *suite_s21_from_decimal_to_int(void);

// other
Suite *suite_s21_negate(void);
Suite *suite_s21_floor(void);
Suite *suite_s21_round(void);
Suite *suite_s21_truncate(void);

// common
Suite *suite_s21_bit_operations(void);

void run_all_tests(void);
void run_testcase(Suite *testcase);
