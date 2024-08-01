#include "test.h"

void run_testcase(Suite *testcase) {
  SRunner *sr = srunner_create(testcase);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

void run_all_tests(void) {
  Suite *list_cases[] = {
      // arithmetic
      suite_s21_add(), suite_s21_div(), suite_s21_mul(), suite_s21_sub(),
      // comparison
      suite_s21_is_equal(), suite_s21_is_greater_or_equal(),
      suite_s21_is_greater(), suite_s21_is_less_or_equal(), suite_s21_is_less(),
      suite_s21_is_not_equal(),
      // convertation
      suite_s21_from_float_to_decimal(), suite_s21_from_int_to_decimal(),
      suite_s21_from_decimal_to_float(), suite_s21_from_decimal_to_int(),
      // other
      suite_s21_negate(), suite_s21_floor(), suite_s21_round(),
      suite_s21_truncate(),
      // common
      suite_s21_bit_operations(), NULL};

  for (int i = 0; list_cases[i] != NULL; i++) {
    run_testcase(list_cases[i]);
  }
}

int main(void) {
  run_all_tests();
  return 0;
}