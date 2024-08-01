#include "../test.h"

START_TEST(truncate_1)  // отбрасывание одной цифры
{
  s21_decimal value = {19, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, 0};
  int result = s21_truncate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(truncate_2)  // отбрасывание двух цифр
{
  s21_decimal value = {199, 0, 0, EXPONENT_2};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, 0};
  int result = s21_truncate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(truncate_3)  // отбрасывание одного нуля
{
  s21_decimal value = {190, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {19, 0, 0, 0};
  int result = s21_truncate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(truncate_4)  // отбрасывание двух нулей
{
  s21_decimal value = {100, 0, 0, EXPONENT_2};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, 0};
  int result = s21_truncate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(truncate_5)  // получение дробного числа, у которого в целой части
                        // только нули
{
  s21_decimal value = {1, 0, 0, EXPONENT_2};
  s21_decimal actual = {0};
  s21_decimal expected = {0, 0, 0, 0};
  int result = s21_truncate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(truncate_6)  // отбрасывание 5-ки
{
  s21_decimal value = {15, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, 0};
  int result = s21_truncate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(truncate_7)  // отбрасывание одной цифры из первого инта
// 276701161170067783695 / 10
// 27670116117006778369
{
  s21_decimal value = {15, 15, 15, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {2147483649, 2147483649, 1, 0};
  int result = s21_truncate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(truncate_8)  // отбрасывание двух цифр из первого инта
// 3670902071522899263687 / 100
// 36709020715228992636
{
  s21_decimal value = {199, 199, 199, EXPONENT_2};
  s21_decimal actual = {0};
  s21_decimal expected = {128849020, 4252017625, 1, 0};
  int result = s21_truncate(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

Suite *suite_s21_truncate(void) {
  Suite *s1 = suite_create("s21_truncate");
  TCase *tc1_1 = tcase_create("base");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, truncate_1);
  tcase_add_test(tc1_1, truncate_2);
  tcase_add_test(tc1_1, truncate_3);
  tcase_add_test(tc1_1, truncate_4);
  tcase_add_test(tc1_1, truncate_5);
  tcase_add_test(tc1_1, truncate_6);
  tcase_add_test(tc1_1, truncate_7);
  tcase_add_test(tc1_1, truncate_8);
  return s1;
}