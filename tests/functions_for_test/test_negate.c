#include "../test.h"

// тесты lumpkinh

START_TEST(test_negate_1) {
  int true_res = 0;
  s21_decimal val1 = {{0x0D002B08, 0x2E8F72FC, 0x36DBE597, 0x800F0000}};
  s21_decimal result = {{0x0D002B08, 0x2E8F72FC, 0x36DBE597, 0x000F0000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_negate(val1, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(result.bits[i], output.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(test_negate_2) {
  int true_res = 0;
  s21_decimal val1 = {{0x4016945A, 0xC024AC55, 0x7AD7D5C0, 0x00050000}};
  s21_decimal result = {{0x4016945A, 0xC024AC55, 0x7AD7D5C0, 0x80050000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_negate(val1, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(result.bits[i], output.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

// тесты dobbyfer

START_TEST(negate_3)  // а что будет с нулем ?
{
  s21_decimal value = {0, 0, 0, 0};
  s21_decimal actual = {0};
  s21_decimal expected = {0, 0, 0, MINUS};
  int result = s21_negate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(negate_4)  // установка 1
{
  s21_decimal value = {1, 0, 0, 0};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, MINUS};
  int result = s21_negate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(negate_5)  // установка значения в каждый бит
{
  s21_decimal value = {199, 199, 199, 0};
  s21_decimal actual = {0};
  s21_decimal expected = {199, 199, 199, MINUS};
  int result = s21_negate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(negate_6)  // установка максимального значения
{
  s21_decimal value = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal actual = {0};
  s21_decimal expected = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  int result = s21_negate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(negate_7)  // изначально знак -
{
  s21_decimal value = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  s21_decimal actual = {0};
  s21_decimal expected = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  int result = s21_negate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(negate_8)  // изначально знак - и есть ненулевая экспонента
{
  s21_decimal value = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS_AND_EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {MAX_UINT, MAX_UINT, MAX_UINT, EXPONENT_1};
  int result = s21_negate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(negate_9)  // изначально знак + и есть ненулевая экспонента
{
  s21_decimal value = {MAX_UINT, MAX_UINT, MAX_UINT, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS_AND_EXPONENT_1};
  int result = s21_negate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

Suite *suite_s21_negate(void) {
  Suite *s1 = suite_create("negate");
  TCase *tc1_1 = tcase_create("negate");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_negate_1);
  tcase_add_test(tc1_1, test_negate_2);
  tcase_add_test(tc1_1, negate_3);
  tcase_add_test(tc1_1, negate_4);
  tcase_add_test(tc1_1, negate_5);
  tcase_add_test(tc1_1, negate_6);
  tcase_add_test(tc1_1, negate_7);
  tcase_add_test(tc1_1, negate_8);
  tcase_add_test(tc1_1, negate_9);
  return s1;
}
