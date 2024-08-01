#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int exit_code = BOOL_NO;
  // проверим, сравнимые ли это числа вообще
  if (s21_is_decimal(value_1) && s21_is_decimal(value_2)) {
    // если числа, предположим равенство для компактности дальнейших проверок
    exit_code = BOOL_YES;

    // нулевые числа равны без учета знака
    if (!(s21_is_zero(value_1) && s21_is_zero(value_2))) {
      // если не нулевые числа, ищем другие отличия
      if (s21_get_sign(value_1) != s21_get_sign(value_2))  // разные знаки
        exit_code = BOOL_NO;
      else {  // одинаковые знаки
        s21_decimal_long val_1 = s21_decimal_to_long(value_1),
                         val_2 = s21_decimal_to_long(value_2);
        alignment_long(&val_1, &val_2);
        for (int i = 0; i <= SERVICE_WORD_LONG; i++) {
          if (val_1.bits[i] != val_2.bits[i]) exit_code = BOOL_NO;
        }
      }
    }
  }
  return exit_code;
}