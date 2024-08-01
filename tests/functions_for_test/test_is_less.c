#include "../test.h"

START_TEST(is_less_1)  // сравнение нулей с разным знаком
{
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, MINUS};
  int actual = s21_is_less(val1, val2);
  int expected = 0;  // FALSE
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_less_2)  // сравнение децималов с разным знаком (второй меньше)
{
  s21_decimal val1 = {10, 0, 0, 0};
  s21_decimal val2 = {10, 0, 0, MINUS};
  int actual = s21_is_less(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_less_3)  // сравнение нулей с разным знаком и экспонентой
{
  s21_decimal val1 = {0, 0, 0, MINUS_AND_MAX_EXPONENT};
  s21_decimal val2 = {0, 0, 0, EXPONENT_27};
  int actual = s21_is_less(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_less_4)  // второй децимал больше
{
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {100, 0, 0, 0};
  int actual = s21_is_less(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_less_5)  // второй децимал меньше
{
  s21_decimal val1 = {100, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, 0};
  int actual = s21_is_less(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_less_6)  // сравнение децималов с разным знаком (второй больше)
{
  s21_decimal val1 = {10, 0, 0, MINUS};
  s21_decimal val2 = {10, 0, 0, 0};
  int actual = s21_is_less(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_less_7)  // сравнение минимального значения
{
  s21_decimal val1 = {1, 0, 0, MAX_EXPONENT};
  s21_decimal val2 = {1, 0, 0, MAX_EXPONENT};
  int actual = s21_is_less(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_less_8)  // cравнение максимального значения
{
  s21_decimal val1 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal val2 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  int actual = s21_is_less(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_less_9)  // сравнение отрицательных децималов
{
  s21_decimal val1 = {0, 0, MAX_UINT, MINUS};
  s21_decimal val2 = {0, 0, MAX_UINT, MINUS};
  int actual = s21_is_less(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_less_10)  // сравнение отрицательных децималов (второй больше)
{
  s21_decimal val1 = {0, MAX_UINT, MAX_UINT, MINUS};
  s21_decimal val2 = {0, 0, MAX_UINT, MINUS};
  int actual = s21_is_less(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_less_11)  // сравнение отрицательных децималов (второй меньше)
{
  s21_decimal val1 = {0, 0, MAX_UINT, MINUS};
  s21_decimal val2 = {0, MAX_UINT, MAX_UINT, MINUS};
  int actual = s21_is_less_or_equal(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_less_12)  // второй децимал больше, разные экспоненты
{
  s21_decimal val1 = {1, 0, 0, EXPONENT_27};  // 10
  s21_decimal val2 = {100, 0, 0, MAX_EXPONENT};
  int actual = s21_is_less(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_less_13)  // второй децимал меньше, разные экспоненты
{
  s21_decimal val1 = {100, 0, 0,
                      EXPONENT_27};  // приводится к 28, значит число будет 10
  s21_decimal val2 = {1, 0, 0, MAX_EXPONENT};
  int actual = s21_is_less(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

// далее тесты Ани

START_TEST(is_less_14) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_less(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_less_15) {
  float num1 = 1.15;
  float num2 = 1.15;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_less_16) {
  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(s21_is_less(dec1, dec2), 0);
  ck_assert_int_eq(s21_is_less(dec2, dec1), 1);
}
END_TEST

START_TEST(is_less_17) {
  s21_decimal dec1 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal dec2 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //  -1.2;
  ck_assert_int_eq(s21_is_less(dec1, dec2), 1);
  ck_assert_int_eq(s21_is_less(dec2, dec1), 0);
}
END_TEST

START_TEST(is_less_18) {
  float num1 = -12345.12345;
  float num2 = -1.2345;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_less(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite *suite_s21_is_less(void) {
  Suite *s1 = suite_create("s21_is_less");
  TCase *tc1_1 = tcase_create("base");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, is_less_1);
  tcase_add_test(tc1_1, is_less_2);
  tcase_add_test(tc1_1, is_less_3);
  tcase_add_test(tc1_1, is_less_4);
  tcase_add_test(tc1_1, is_less_5);
  tcase_add_test(tc1_1, is_less_6);
  tcase_add_test(tc1_1, is_less_7);
  tcase_add_test(tc1_1, is_less_8);
  tcase_add_test(tc1_1, is_less_9);
  tcase_add_test(tc1_1, is_less_10);
  tcase_add_test(tc1_1, is_less_11);
  tcase_add_test(tc1_1, is_less_12);
  tcase_add_test(tc1_1, is_less_13);
  tcase_add_test(tc1_1, is_less_14);
  tcase_add_test(tc1_1, is_less_15);
  tcase_add_test(tc1_1, is_less_16);
  tcase_add_test(tc1_1, is_less_17);
  tcase_add_test(tc1_1, is_less_18);

  return s1;
}
