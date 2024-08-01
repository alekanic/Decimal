#include <limits.h>

#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int exit_code = CODE_ERR;
  // проверим корректность числа и указателя
  if (s21_is_decimal(src) && dst) {
    // отбросим дробную часть числа
    s21_truncate(src, &src);
    // проверим, влезет ли целая часть в int
    if ((src.bits[1] == 0) && (src.bits[2] == 0)) {
      if (s21_get_sign(src)) {
        if (src.bits[0] <= INT_MAX) {
          // отрицательное надо проверить с учетом диапазона int
          // диапазон int = -2147483648..2147483647
          *dst = -src.bits[0];
          exit_code = CODE_OK;
        } else if ((int)src.bits[0] == INT_MIN) {
          *dst = src.bits[0];
          exit_code = CODE_OK;
        }
      } else {  // любое положительное в пределах int - просто запишем
        *dst = src.bits[0];
        exit_code = CODE_OK;
      }
    }
  }
  return exit_code;
}