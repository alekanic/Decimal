#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_code = CODE_OK;
  // для этих случаев ошибка не определена
  // if(!s21_is_decimal(value_1) || !s21_is_decimal(value_2) || !result)

  if (s21_is_zero(value_2)) {  // делитель - ноль, выход с ошибкой
    exit_code = CODE_ERR_DIV_BY_ZERO;
    s21_init_nan(result);
  } else if (s21_is_zero(value_1))  // делимое - ноль, результат - ноль
    s21_init_zero(result);
  else {  // основная часть случаев деления
  }

  return exit_code;
}