#include "../test.h"

START_TEST(is_greater_or_equal_1)  // сравнение нулей с разным знаком
{
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, MINUS};
  int actual = s21_is_greater_or_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_greater_or_equal_2)  // сравнение децималов с разным знаком
                                   // (второй меньше)
{
  s21_decimal val1 = {10, 0, 0, 0};
  s21_decimal val2 = {10, 0, 0, MINUS};
  int actual = s21_is_greater_or_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(
    is_greater_or_equal_3)  // сравнение нулей с разным знаком и экспонентой
{
  s21_decimal val1 = {0, 0, 0, MINUS_AND_MAX_EXPONENT};
  s21_decimal val2 = {0, 0, 0, EXPONENT_27};
  int actual = s21_is_greater_or_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_greater_or_equal_4)  // второй децимал больше
{
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {100, 0, 0, 0};
  int actual = s21_is_greater_or_equal(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_greater_or_equal_5)  // второй децимал меньше
{
  s21_decimal val1 = {100, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  int actual = s21_is_greater_or_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_greater_or_equal_6)  // сравнение децималов с разным знаком
                                   // (второй больше)
{
  s21_decimal val1 = {10, 0, 0, MINUS};
  s21_decimal val2 = {10, 0, 0, 0};
  int actual = s21_is_greater_or_equal(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_greater_or_equal_7)  // сравнение минимального значения
{
  s21_decimal val1 = {1, 0, 0, MAX_EXPONENT};
  s21_decimal val2 = {1, 0, 0, MAX_EXPONENT};
  int actual = s21_is_greater_or_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_greater_or_equal_8)  // cравнение максимального значения
{
  s21_decimal val1 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal val2 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  int actual = s21_is_greater_or_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_greater_or_equal_9)  // сравнение отрицательных децималов
{
  s21_decimal val1 = {0, 0, MAX_UINT, MINUS};
  s21_decimal val2 = {0, 0, MAX_UINT, MINUS};
  int actual = s21_is_greater_or_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_greater_or_equal_10)  // сравнение отрицательных децималов (второй
                                    // больше)
{
  s21_decimal val1 = {0, MAX_UINT, MAX_UINT, MINUS};
  s21_decimal val2 = {0, 0, MAX_UINT, MINUS};
  int actual = s21_is_greater_or_equal(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_greater_or_equal_11)  // сравнение отрицательных децималов (второй
                                    // меньше)
{
  s21_decimal val1 = {0, 0, MAX_UINT, MINUS};
  s21_decimal val2 = {0, MAX_UINT, MAX_UINT, MINUS};
  int actual = s21_is_greater_or_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_greater_or_equal_12)  // второй децимал больше, разные экспоненты
{
  s21_decimal val1 = {1, 0, 0, EXPONENT_27};  // домножится на 10, будет 10
  s21_decimal val2 = {100, 0, 0, MAX_EXPONENT};
  int actual = s21_is_greater_or_equal(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_greater_or_equal_13)  // второй децимал меньше, разные экспоненты
{
  s21_decimal val1 = {100, 0, 0, EXPONENT_27};
  s21_decimal val2 = {1, 0, 0, MAX_EXPONENT};
  int actual = s21_is_greater_or_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

// далее тесты Ани

START_TEST(is_greater_or_equal_14) {
  float num1 = 1.156432;
  float num2 = 1.15;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_or_equal_15) {
  int num1 = 2;
  int num2 = -2;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_or_equal_16) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_or_equal_17) {
  int num1 = 2;
  int num2 = 5;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_or_equal_18) {
  float num1 = 12345.12345;
  float num2 = 1.12345;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_or_equal_19) {
  float num1 = -1.12345;
  float num2 = -1.12345;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite *suite_s21_is_greater_or_equal(void) {
  Suite *s1 = suite_create("s21_is_greater_or_equal");
  TCase *tc1_1 = tcase_create("base");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, is_greater_or_equal_1);
  tcase_add_test(tc1_1, is_greater_or_equal_2);
  tcase_add_test(tc1_1, is_greater_or_equal_3);
  tcase_add_test(tc1_1, is_greater_or_equal_4);
  tcase_add_test(tc1_1, is_greater_or_equal_5);
  tcase_add_test(tc1_1, is_greater_or_equal_6);
  tcase_add_test(tc1_1, is_greater_or_equal_7);
  tcase_add_test(tc1_1, is_greater_or_equal_8);
  tcase_add_test(tc1_1, is_greater_or_equal_9);
  tcase_add_test(tc1_1, is_greater_or_equal_10);
  tcase_add_test(tc1_1, is_greater_or_equal_11);
  tcase_add_test(tc1_1, is_greater_or_equal_12);
  tcase_add_test(tc1_1, is_greater_or_equal_13);
  tcase_add_test(tc1_1, is_greater_or_equal_14);
  tcase_add_test(tc1_1, is_greater_or_equal_15);
  tcase_add_test(tc1_1, is_greater_or_equal_16);
  tcase_add_test(tc1_1, is_greater_or_equal_17);
  tcase_add_test(tc1_1, is_greater_or_equal_18);
  tcase_add_test(tc1_1, is_greater_or_equal_19);

  return s1;
}
