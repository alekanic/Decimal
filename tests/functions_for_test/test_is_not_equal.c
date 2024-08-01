#include "../test.h"

START_TEST(is_not_equal_1)  // cравнение нулей с разным знаком
{
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {0, 0, 0, MINUS};
  int actual = s21_is_not_equal(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(
    is_not_equal_2)  // сравнение одинаковых децималов с одинаковой экспонентой
{
  s21_decimal val1 = {0, 0, MAX_UINT, MAX_EXPONENT};
  s21_decimal val2 = {0, 0, MAX_UINT, MAX_EXPONENT};
  int actual = s21_is_not_equal(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_not_equal_3)  // сравнение децималов с одинаковой экспонентой и с
                            // разным знаком
{
  s21_decimal val1 = {0, 0, MAX_UINT, MAX_EXPONENT};
  s21_decimal val2 = {0, 0, MAX_UINT, MINUS_AND_MAX_EXPONENT};
  int actual = s21_is_not_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_not_equal_4)  // сравнение децималов с экспонентами 28 и 29
{
  s21_decimal val1 = {0, 0, MAX_UINT, MAX_EXPONENT};
  s21_decimal val2 = {0, 0, MAX_UINT, TOO_MUCH_EXPONENT};
  int actual = s21_is_not_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_not_equal_5)  // сравнение децималов с разным знаком
{
  s21_decimal val1 = {0, 0, MAX_UINT, 0};
  s21_decimal val2 = {0, 0, MAX_UINT, MINUS};
  int actual = s21_is_not_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_not_equal_6)  // сравнение отрицательных децималов
{
  s21_decimal val1 = {0, 0, MAX_UINT, MINUS};
  s21_decimal val2 = {0, 0, MAX_UINT, MINUS};
  int actual = s21_is_not_equal(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_not_equal_7)  // сравнение максимального значения
{
  s21_decimal val1 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal val2 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  int actual = s21_is_not_equal(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_not_equal_8)  // сравнение максимального значения с разным знаком
{
  s21_decimal val1 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal val2 = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  int actual = s21_is_not_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_not_equal_9)  // сравнение минимального значения
{
  s21_decimal val1 = {1, 0, 0, MAX_EXPONENT};
  s21_decimal val2 = {1, 0, 0, MAX_EXPONENT};
  int actual = s21_is_not_equal(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_not_equal_10)  // сравнение минимального значения с разным знаком
{
  s21_decimal val1 = {1, 0, 0, MAX_EXPONENT};
  s21_decimal val2 = {1, 0, 0, MINUS_AND_MAX_EXPONENT};
  int actual = s21_is_not_equal(val1, val2);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
  END_TEST
}

START_TEST(is_not_equal_11)  // cравнение нулей с разной экспонентой
{
  s21_decimal val1 = {0, 0, 0, MAX_EXPONENT};
  s21_decimal val2 = {0, 0, 0, EXPONENT_27};
  int actual = s21_is_not_equal(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(is_not_equal_12)  // cравнение нулей с разной экспонентой и знаком
{
  s21_decimal val1 = {0, 0, 0, MINUS_AND_MAX_EXPONENT};
  s21_decimal val2 = {0, 0, 0, EXPONENT_27};
  int actual = s21_is_not_equal(val1, val2);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

// далее тесты Ани

START_TEST(is_not_equal_13) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_not_equal_14) {
  float num1 = 1.15;
  float num2 = -1.15;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_not_equal_15) {
  int num1 = 2;
  int num2 = 5;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_not_equal_16) {
  s21_decimal dec1 = {{12345, 0, 0, 0b00000000000001000000000000000000}};
  //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b10000000000000010000000000000000}};
  // -1.2;
  ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 1);
}
END_TEST

START_TEST(is_not_equal_17) {
  s21_decimal dec1 = {{120000, 0, 0, 0b00000000000001000000000000000000}};
  //  12.0000
  s21_decimal dec2 = {{12, 0, 0, 0b00000000000000000000000000000000}};
  // 12
  ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 0);
}
END_TEST

Suite *suite_s21_is_not_equal(void) {
  Suite *s1 = suite_create("s21_is_not_equal");
  TCase *tc1_1 = tcase_create("base");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, is_not_equal_1);
  tcase_add_test(tc1_1, is_not_equal_2);
  tcase_add_test(tc1_1, is_not_equal_3);
  tcase_add_test(tc1_1, is_not_equal_4);
  tcase_add_test(tc1_1, is_not_equal_5);
  tcase_add_test(tc1_1, is_not_equal_6);
  tcase_add_test(tc1_1, is_not_equal_7);
  tcase_add_test(tc1_1, is_not_equal_8);
  tcase_add_test(tc1_1, is_not_equal_9);
  tcase_add_test(tc1_1, is_not_equal_10);
  tcase_add_test(tc1_1, is_not_equal_11);
  tcase_add_test(tc1_1, is_not_equal_12);
  tcase_add_test(tc1_1, is_not_equal_13);
  tcase_add_test(tc1_1, is_not_equal_14);
  tcase_add_test(tc1_1, is_not_equal_15);
  tcase_add_test(tc1_1, is_not_equal_16);
  tcase_add_test(tc1_1, is_not_equal_17);

  return s1;
}
