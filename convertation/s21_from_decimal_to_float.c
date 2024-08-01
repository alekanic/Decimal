#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int exit_code = CODE_ERR;
  // проверим корректность числа и указателя
  if (s21_is_decimal(src) && dst) {
    exit_code = CODE_OK;
    double result = 0;
    // пройдемся по каждому биту мантиссы
    for (int i = 0; i < MANTISSA_LENGTH; i++)
      // если установлен - возводим в степень двойки и прибавляем к результату
      if (s21_get_bit(src, i) == 1) result += pow(2, i);
    int exp = s21_get_exponent(src);
    // результат уменьшим кратно экспоненте, если она есть
    for (int i = 0; i < exp; i++) result /= 10.0;
    // если число отрицательное - сменим знак
    if (s21_get_sign(src)) result *= -1;
    // конвертируем результат в нужный тип и запишем
    *dst = (float)result;
  }
  return exit_code;
}