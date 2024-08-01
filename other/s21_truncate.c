#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int exit_code = CODE_ERR;
  // проверим корректность числа и указателя
  if (result && s21_is_decimal(value)) {
    *result = value;
    int exp = s21_get_exponent(*result);
    // пока экспонента больше нуля, делим все на 10
    while (exp > 0) {
      downscale(result);
      exp = s21_get_exponent(*result);
    }
    exit_code = CODE_OK;
  }
  return exit_code;
}