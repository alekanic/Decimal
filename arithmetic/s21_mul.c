#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_code = CODE_OK;

  // для этих случаев ошибка не определена
  // if(!s21_is_decimal(value_1) || !s21_is_decimal(value_2) || !result)

  // если есть нули, нечего считать, результат сразу ноль
  if (s21_is_zero(value_1) || s21_is_zero(value_2))
    s21_init_zero(result);
  else {  // основная часть случаев умножения
    exit_code = s21_mul_positive(value_1, value_2, result);
    // установим знак результата
    if (s21_get_sign(value_1) == s21_get_sign(value_2)) {  // ++ => -- => +
      s21_set_sign(result, 0);
    } else {  // +- => -+ => -
      s21_set_sign(result, 1);
    }
  }
  return exit_code;
}

int s21_mul_positive(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  int exit_code = CODE_OK;
  s21_init_zero(result);  // инициализируем нулем результат
  //  запишем переменные в длинные
  s21_decimal_long value_1_long = s21_decimal_to_long(value_1),
                   value_2_long = s21_decimal_to_long(value_2),
                   result_long = s21_decimal_to_long(*result);
  int exp_1 = s21_get_exponent(value_1), exp_2 = s21_get_exponent(value_2),
      exp_res = exp_1 * exp_2;
  exit_code = just_mul_long(value_1_long, value_2_long, &result_long);
  *result = s21_long_to_decimal(result_long);
  s21_set_exponent(result, exp_res);  // нужна проверка

  return exit_code;
}

int just_mul_long(s21_decimal_long value_1, s21_decimal_long value_2,
                  s21_decimal_long *result) {
  int carry_bit = 0;  // флаг переноса при сложении разрядов
  for (int i = 0; i < MANTISSA_LENGTH; i++) {
    s21_decimal_long shifted_long = s21_shift_left_long(value_1, i);
    for (int j = 0; j < MANTISSA_LENGTH_LONG; j++) {
      s21_set_bit_long(
          &shifted_long, j,
          s21_get_bit_long(shifted_long, j) & s21_get_bit_long(value_2, i));
    }
    carry_bit = just_add_long(shifted_long, *result, result);
  }
  return carry_bit;
}

s21_decimal s21_shift_left(s21_decimal value, int pos) {
  s21_decimal result = value;
  if (pos > 0) {
    for (int j = 0; j < pos; j++) {
      for (int i = MANTISSA_LENGTH; i > 0; i--) {
        s21_set_bit(&result, i, s21_get_bit(result, i - 1));
      }
      s21_set_bit(&result, 0, 0);  // занулим младший бит
    }
  }
  return result;
}

s21_decimal_long s21_shift_left_long(s21_decimal_long value, int pos) {
  s21_decimal_long result = value;
  if (pos > 0) {
    for (int j = 0; j < pos; j++) {
      for (int i = MANTISSA_LENGTH_LONG; i > 0; i--) {
        s21_set_bit_long(&result, i, s21_get_bit_long(result, i - 1));
      }
      s21_set_bit_long(&result, 0, 0);  // занулим младший бит
    }
  }
  return result;
}