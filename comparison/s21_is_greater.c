#include "../s21_decimal.h"

// Непосредственно сравнение двух неравных положительных чисел
// Возвращает 1, если value_1 строго больше value_2
// Возвращает 0 в ином случае
int compare_greater(s21_decimal value_1, s21_decimal value_2);

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int exit_code = BOOL_NO;
  // проверим, сравнимые ли это числа вообще
  // и не равны ли они заодно
  if (s21_is_decimal(value_1) && s21_is_decimal(value_2) &&
      !s21_is_equal(value_1, value_2)) {
    int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);

    if (!sign_1 && sign_2)
      // + > - всегда больше
      exit_code = BOOL_YES;
    else if (sign_1 && sign_2)  // - ? -
      // обратное сравнение модулей отрицательных чисел
      exit_code = compare_greater(s21_abs(value_2), s21_abs(value_1));
    else if (!sign_1 && !sign_2)  // + ? +
      // прямое сравнение положительных чисел
      exit_code = compare_greater(value_1, value_2);
    // else // - < + всегда меньше избыточное условие - ноль уже записан
    // exit_code = BOOL_NO
  }
  return exit_code;
}

int compare_greater(s21_decimal value_1, s21_decimal value_2) {
  int exit_code = BOOL_NO;
  s21_decimal_long value_1_long = s21_decimal_to_long(value_1),
                   value_2_long = s21_decimal_to_long(value_2);

  // выровняем числа для дальнейшего сравнения только мантисс
  alignment_long(&value_1_long, &value_2_long);

  // пройдем по двоичным разрядам мантиссы начиная со старшего
  for (int i = MANTISSA_LENGTH_LONG; i >= 0; i--)
    if ((s21_get_bit_long(value_1_long, i) == 1) &&
        (s21_get_bit_long(value_2_long, i) == 0)) {
      // нашли старший разряд первого числа, который больше второго
      // этого достаточно, выходим
      exit_code = BOOL_YES;
      break;
    } else if ((s21_get_bit_long(value_2_long, i) == 1) &&
               (s21_get_bit_long(value_1_long, i) == 0))
      // нашли старший разряд второго числа, который больше первого
      // этого достаточно, выходим
      break;

  return exit_code;
}