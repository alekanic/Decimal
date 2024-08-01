#include "../test.h"

// тесты dobbyfer

START_TEST(floor_1)  // значение 1
{
  s21_decimal value = {1, 0, 0, 0};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, 0};
  int result = s21_floor(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(floor_2)  // значение 101 и экспонента 1 (округление)
{
  s21_decimal value = {101, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {10, 0, 0, 0};
  int result = s21_floor(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(floor_3)  // округление и установка знака -
{
  s21_decimal value = {101, 0, 0, MINUS_AND_EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {11, 0, 0, MINUS};
  int result = s21_floor(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(floor_4)  // округление 5 в меньшую сторону
{
  s21_decimal value = {15, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, 0};
  int result = s21_floor(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(floor_5)  // округление 6 в меньшую сторону
{
  s21_decimal value = {16, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, 0};
  int result = s21_floor(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(floor_6)  // округление 9 в меньшую сторону
{
  s21_decimal value = {19, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, 0};
  int result = s21_floor(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(floor_7)  // округление -9 в меньшую сторону
{
  s21_decimal value = {19, 0, 0, MINUS_AND_EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {2, 0, 0, MINUS};
  int result = s21_floor(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(floor_8)  // округление -1 в меньшую сторону
{
  s21_decimal value = {11, 0, 0, MINUS_AND_EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {2, 0, 0, MINUS};
  int result = s21_floor(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

Suite *suite_s21_floor(void) {
  Suite *s1 = suite_create("s21_floor");
  TCase *tc1_1 = tcase_create("base");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, floor_1);
  tcase_add_test(tc1_1, floor_2);
  tcase_add_test(tc1_1, floor_3);
  tcase_add_test(tc1_1, floor_4);
  tcase_add_test(tc1_1, floor_5);
  tcase_add_test(tc1_1, floor_6);
  tcase_add_test(tc1_1, floor_7);
  tcase_add_test(tc1_1, floor_8);
  return s1;
}