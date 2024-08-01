#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int exit_code = CODE_ERR;
  // меняем знак, если указатель вывода корректный
  if (result) {
    *result = value;
    s21_set_sign(result, !s21_get_sign(value));
    // если значение исходного числа некорректное
    // после смены знака вернем ошибку
    if (s21_is_decimal(value)) exit_code = CODE_OK;
  }
  return exit_code;
}