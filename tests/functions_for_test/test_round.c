#include "../test.h"

START_TEST(round_1)  // округление 1.9 (нечетное) в большую сторону
{
  s21_decimal value = {19, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {2, 0, 0, 0};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_2)  // округление 2.9 (четное) в большую сторону
{
  s21_decimal value = {29, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {3, 0, 0, 0};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_3)  // округление 1.6 (нечетное) в большую сторону
{
  s21_decimal value = {16, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {2, 0, 0, 0};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_4)  // округление 2.6 (четное) в большую сторону
{
  s21_decimal value = {26, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {3, 0, 0, 0};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_5)  // округление 1.5 - нечетное число (в большую сторону)
{
  s21_decimal value = {15, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {2, 0, 0, 0};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_6)  // округление 2.5 - четное число (в меньшую сторону)
{
  s21_decimal value = {25, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {2, 0, 0, 0};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_7)  // округление 1.1 в меньшую сторону
{
  s21_decimal value = {11, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, 0};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_8)  // округление 2.1 в меньшую сторону
{
  s21_decimal value = {21, 0, 0, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {2, 0, 0, 0};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_9)
// 202914184858049708043 / 10
// 20291418485804970804
{
  s21_decimal value = {11, 11, 11, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {3006477108, 429496730, 1, 0};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_10)
// 387381625638094897173 / 10
// 38738162563809489717
{
  s21_decimal value = {21, 21, 21, EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {3006477109, 429496731, 2, 0};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_11)  // округление 2.1 в большую сторону в нескольких интах
{
  s21_decimal value = {21, 0, 0, MINUS_AND_EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {2, 0, 0, MINUS};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_12)  // округление 2.8 в меньшую сторону
{
  s21_decimal value = {28, 0, 0, MINUS_AND_EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {3, 0, 0, MINUS};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_13)  // округление 1.5 в большую сторону
{
  s21_decimal value = {15, 0, 0, MINUS_AND_EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {2, 0, 0, MINUS};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_14)
// -221360928936054226956 / 10
// -22136092893605422696
{
  s21_decimal value = {12, 12, 12, MINUS_AND_EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {1717986920, 858993460, 1, MINUS};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_15)
// -221360928936054226955 / 10
// -22136092893605422696
{
  s21_decimal value = {11, 12, 12, MINUS_AND_EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {1717986920, 858993460, 1, MINUS};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(round_16)
// -221360928936054226945 / 10
// -22136092893605422694
{
  s21_decimal value = {11, 12, 12, MINUS_AND_EXPONENT_1};
  s21_decimal actual = {0};
  s21_decimal expected = {1717986920, 858993460, 1, MINUS};
  int result = s21_round(value, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха функции
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

Suite *suite_s21_round(void) {
  Suite *s1 = suite_create("s21_round");
  TCase *tc1_1 = tcase_create("base");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, round_1);
  tcase_add_test(tc1_1, round_2);
  tcase_add_test(tc1_1, round_3);
  tcase_add_test(tc1_1, round_4);
  tcase_add_test(tc1_1, round_5);
  tcase_add_test(tc1_1, round_6);
  tcase_add_test(tc1_1, round_7);
  tcase_add_test(tc1_1, round_8);
  tcase_add_test(tc1_1, round_9);
  tcase_add_test(tc1_1, round_10);
  tcase_add_test(tc1_1, round_11);
  tcase_add_test(tc1_1, round_12);
  tcase_add_test(tc1_1, round_13);
  tcase_add_test(tc1_1, round_14);
  tcase_add_test(tc1_1, round_15);
  tcase_add_test(tc1_1, round_16);
  return s1;
}