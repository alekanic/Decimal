#include "../test.h"

// тесты lumpkinh

START_TEST(from_int_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

// тесты dobbyfer

START_TEST(from_int_to_decimal_3) {
  // устанавливаем единицу и проверяем, что
  // точно единица
  int num = 1;
  s21_decimal actual;
  int result = s21_from_int_to_decimal(num, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха выполнения функции
  s21_decimal expected = {ONE, 0, 0, 0};
  ck_assert_int_eq(1, s21_is_equal(actual, expected));
  // проверка получившегося децимала
}
END_TEST

START_TEST(from_int_to_decimal_4) {
  // устанавливаем - единицу и проверяем, что
  // установилась единица и знак
  int num = -1;
  s21_decimal actual;
  int result = s21_from_int_to_decimal(num, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха выполнения функции
  s21_decimal expected = {ONE, 0, 0, MINUS};
  ck_assert_int_eq(1, s21_is_equal(actual, expected));
  // проверка получившегося децимала
}
END_TEST

START_TEST(from_int_to_decimal_5) {
  // максимальное значение инта и знак минус
  int num = -MAX_NUM_INT;  // максимальное число для инт
  s21_decimal actual;
  int result = s21_from_int_to_decimal(num, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха выполнения функции
  s21_decimal expected = {MAX_INT, 0, 0, MINUS};
  ck_assert_int_eq(1, s21_is_equal(actual, expected));
  // проверка получившегося децимала
}
END_TEST

START_TEST(from_int_to_decimal_6) {
  // максимальное значение инта
  int num = MAX_NUM_INT;  // максимальное число для инт
  s21_decimal actual;
  int result = s21_from_int_to_decimal(num, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха выполнения функции
  s21_decimal expected = {MAX_INT, 0, 0, 0};
  ck_assert_int_eq(1, s21_is_equal(actual, expected));
  // проверка получившегося децимала
}
END_TEST

Suite *suite_s21_from_int_to_decimal(void) {
  Suite *s1 = suite_create("s21_from_int_to_decimal");
  TCase *tc1_1 = tcase_create("convertation");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, from_int_to_decimal_1);
  tcase_add_test(tc1_1, from_int_to_decimal_2);
  tcase_add_test(tc1_1, from_int_to_decimal_3);
  tcase_add_test(tc1_1, from_int_to_decimal_4);
  tcase_add_test(tc1_1, from_int_to_decimal_5);
  tcase_add_test(tc1_1, from_int_to_decimal_6);

  return s1;
}
