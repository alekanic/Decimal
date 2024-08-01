#include "../test.h"

// тесты lumpkinh

START_TEST(from_decimal_to_int_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_set_exponent(&val, 5);
  int res = 1234;
  int tmp = 0;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_int_2) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_set_bit(&val, 127, 1);
  s21_set_exponent(&val, 5);
  int res = -1234;
  int tmp = 0;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

// тесты dobbyfer

START_TEST(from_decimal_to_int_3) {  // устанавливаем максимальный инт
  int actual = 0;
  s21_decimal val = {MAX_NUM_INT, 0, 0, 0};
  int result = s21_from_decimal_to_int(val, &actual);
  int expected = MAX_NUM_INT;
  ck_assert_int_eq(0, result);  // проверка успеха выполнения конвертации
  ck_assert_int_eq(actual, expected);  // проверка значений
}
END_TEST

START_TEST(
    from_decimal_to_int_4) {  // устанавливаем отрицательный максимальный инт
  int actual = 0;
  s21_decimal val = {MAX_NUM_INT, 0, 0, MINUS};
  int result = s21_from_decimal_to_int(val, &actual);
  int expected = -MAX_NUM_INT;
  ck_assert_int_eq(0, result);  // проверка успеха выполнения конвертации
  ck_assert_int_eq(actual, expected);  // проверка значений
}
END_TEST

START_TEST(from_decimal_to_int_5) {  // децимал больше, чем вмещает инт
  int actual = 0;
  s21_decimal val = {MAX_NUM_INT, ONE, 0, 0};
  int result = s21_from_decimal_to_int(val, &actual);
  ck_assert_int_eq(1, result);  // проверка успеха выполнения конвертации
}
END_TEST

START_TEST(from_decimal_to_int_6) {  // децимал больше, чем вмещает инт
  int actual = 0;
  s21_decimal val = {0, ONE, 0, 0};
  int result = s21_from_decimal_to_int(val, &actual);
  ck_assert_int_eq(1, result);  // проверка успеха выполнения конвертации
}
END_TEST

START_TEST(from_decimal_to_int_7) {  // децимал больше, чем вмещает инт
  int actual = 0;
  s21_decimal val = {0, ONE, 0, MINUS};
  int result = s21_from_decimal_to_int(val, &actual);
  ck_assert_int_eq(1, result);  // проверка успеха выполнения конвертации
}
END_TEST

START_TEST(from_decimal_to_int_8) {  // децимал больше, чем вмещает инт
  int actual = 0;
  s21_decimal val = {MAX_UINT, 0, 0, MINUS};
  int result = s21_from_decimal_to_int(val, &actual);
  ck_assert_int_eq(1, result);  // проверка успеха выполнения конвертации
}
END_TEST

START_TEST(from_decimal_to_int_9) {  // есть экспонента
  int actual = 0;
  s21_decimal val = {1000, 0, 0, EXPONENT_1};
  int result = s21_from_decimal_to_int(val, &actual);
  int expected = 100;
  ck_assert_int_eq(0, result);  // проверка успеха выполнения конвертации
  ck_assert_int_eq(actual, expected);  // проверка значений
}
END_TEST

START_TEST(from_decimal_to_int_10) {  // есть экспонента и знак
  int actual = 0;
  s21_decimal val = {1000, 0, 0, MINUS_AND_EXPONENT_1};
  int result = s21_from_decimal_to_int(val, &actual);
  int expected = -100;
  ck_assert_int_eq(0, result);  // проверка успеха выполнения конвертации
  ck_assert_int_eq(actual, expected);  // проверка значений
}
END_TEST

START_TEST(from_decimal_to_int_11) {  // откидываем дробную часть
  int actual = 0;
  s21_decimal val = {1001, 0, 0, MINUS_AND_EXPONENT_1};
  int result = s21_from_decimal_to_int(val, &actual);
  int expected = -100;
  ck_assert_int_eq(0, result);  // проверка успеха выполнения конвертации
  ck_assert_int_eq(actual, expected);  // проверка значений
}
END_TEST

Suite *suite_s21_from_decimal_to_int(void) {
  Suite *s1 = suite_create("s21_from_decimal_to_int");
  TCase *tc1_1 = tcase_create("convertation");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, from_decimal_to_int_1);
  tcase_add_test(tc1_1, from_decimal_to_int_2);
  tcase_add_test(tc1_1, from_decimal_to_int_3);
  tcase_add_test(tc1_1, from_decimal_to_int_4);
  tcase_add_test(tc1_1, from_decimal_to_int_5);
  tcase_add_test(tc1_1, from_decimal_to_int_6);
  tcase_add_test(tc1_1, from_decimal_to_int_7);
  tcase_add_test(tc1_1, from_decimal_to_int_8);
  tcase_add_test(tc1_1, from_decimal_to_int_9);
  tcase_add_test(tc1_1, from_decimal_to_int_10);
  tcase_add_test(tc1_1, from_decimal_to_int_11);

  return s1;
}