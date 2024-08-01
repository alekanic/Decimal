#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int exit_code = CODE_ERR;
  // проверим корректность числа и указателя
  if (s21_is_decimal(value) && result) {
    int sign = s21_get_sign(value);
    // для положительного достаточно отбросить дробную часть
    s21_truncate(value, result);
    s21_decimal res = *result;
    if (sign && !s21_is_equal(value, res)) {
      // если отрицательное не было целым - надо еще отнять единицу
      s21_decimal one = {{1, 0, 0, 0}};
      s21_sub(*result, one, result);
    }
    exit_code = CODE_OK;
  }
  return exit_code;
}