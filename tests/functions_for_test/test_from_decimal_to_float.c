#include "../test.h"

// тесты lumpkinh

START_TEST(from_decimal_to_float_1) {
  s21_decimal decimal = {{1, 0, 0, 0}};
  float number = 0;
  int result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(number, 1);
}
END_TEST

START_TEST(from_decimal_to_float_2) {
  s21_decimal decimal = (s21_decimal){{654321, 0, 0, 0}};
  float number = 0;
  int result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(number, 654321);
}
END_TEST

START_TEST(from_decimal_to_float_3) {
  s21_decimal decimal = (s21_decimal){{654321, 0, 0, 0}};
  s21_set_exponent(&decimal, 3);
  float number = 0;
  int result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(number, 654.321);
}
END_TEST

START_TEST(from_decimal_to_float_4) {
  s21_decimal decimal = (s21_decimal){{654321, 0, 0, 0}};
  s21_set_exponent(&decimal, 3);
  s21_set_sign(&decimal, 1);
  float number = 0;
  int result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(number, -654.321);
}
END_TEST

START_TEST(from_decimal_to_float_5) {
  s21_decimal decimal =
      (s21_decimal){{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int result = s21_from_decimal_to_float(decimal, NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(from_decimal_to_float_6) {
  s21_decimal decimal = (s21_decimal){{-1, 0, 0, 0x1D0000}};
  float number = 0;
  int result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(from_decimal_to_float_7) {
  s21_decimal decimal = (s21_decimal){{-1, 0, 0, 0x1C8000}};
  float number = 0;
  int result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(from_decimal_to_float_8) {
  s21_decimal decimal = (s21_decimal){{-1, 0, 0, 0x11C0000}};
  float number = 0;
  int result = s21_from_decimal_to_float(decimal, &number);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite *suite_s21_from_decimal_to_float(void) {
  Suite *s1 = suite_create("s21_from_decimal_to_float");
  TCase *tc1_1 = tcase_create("convertation");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, from_decimal_to_float_1);
  tcase_add_test(tc1_1, from_decimal_to_float_2);
  tcase_add_test(tc1_1, from_decimal_to_float_3);
  tcase_add_test(tc1_1, from_decimal_to_float_4);
  tcase_add_test(tc1_1, from_decimal_to_float_5);
  tcase_add_test(tc1_1, from_decimal_to_float_6);
  tcase_add_test(tc1_1, from_decimal_to_float_7);
  tcase_add_test(tc1_1, from_decimal_to_float_8);

  return s1;
}
