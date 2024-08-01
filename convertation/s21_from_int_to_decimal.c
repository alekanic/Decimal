#include <limits.h>

#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int exit_code = CODE_ERR;
  if (dst) {  // конвертируем, если указатель вывода корректный
    s21_init_zero(dst);
    if (src < 0) {
      if (src != INT_MIN)
        // иначе будет ошибочное преобразование
        // диапазон int = -2147483648..2147483647
        dst->bits[0] = -src;
      else
        dst->bits[0] = src;
      s21_negate(*dst, dst);
    } else
      dst->bits[0] = src;
    exit_code = CODE_OK;
  }
  return exit_code;
}