#include "../s21_decimal.h"

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  // воспользуемся уже готовыми функциями
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}