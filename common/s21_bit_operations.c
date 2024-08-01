#include "../s21_decimal.h"

/*
void s21_print_binary(unsigned int value) {
  for (int i = 31; i >= 0; i--) printf("%u", ((value >> i) & 1));
  printf(" ");
}

void s21_print_decimal(s21_decimal value) {
  for (int i = SERVICE_WORD; i >= 0; i--) s21_print_binary(value.bits[i]);
}

void s21_print_decimal_long(s21_decimal_long value) {
  for (int i = SERVICE_WORD_LONG; i >= 0; i--) s21_print_binary(value.bits[i]);
}  */

int s21_is_decimal(s21_decimal value) {
  int exit_code = BOOL_YES;
  // Умножим на маску пустых битов для проверки корректности числа
  if ((value.bits[SERVICE_WORD] & MASK_EMPTY) != 0)
    exit_code = BOOL_NO;
  else  // Проверим корректность степени
    if (s21_get_exponent(value) > EXPONENT_MAX) exit_code = BOOL_NO;
  return exit_code;
}

int s21_is_decimal_long(s21_decimal_long value) {
  int exit_code = BOOL_YES;
  // Умножим на маску пустых битов для проверки корректности числа
  if ((value.bits[SERVICE_WORD_LONG] & MASK_EMPTY) != 0)
    exit_code = BOOL_NO;
  else  // Проверим корректность степени
    if (s21_get_exponent_long(value) > EXPONENT_MAX_LONG) exit_code = BOOL_NO;
  return exit_code;
}

int s21_get_sign(s21_decimal value) {
  return (value.bits[SERVICE_WORD] & MASK_SIGN) >> 31;
}

int s21_get_sign_long(s21_decimal_long value) {
  return (value.bits[SERVICE_WORD_LONG] & MASK_SIGN) >> 31;
}

int s21_set_sign(s21_decimal *value, int sign) {
  int exit_code = CODE_OK;
  if (sign == SIGN_PLUS)
    value->bits[SERVICE_WORD] &= ~MASK_SIGN;
  else if (sign == SIGN_MINUS)
    value->bits[SERVICE_WORD] |= MASK_SIGN;
  else
    exit_code = CODE_ERR;
  return exit_code;
}

int s21_set_sign_long(s21_decimal_long *value, int sign) {
  int exit_code = CODE_OK;
  if (sign == SIGN_PLUS)
    value->bits[SERVICE_WORD_LONG] &= ~MASK_SIGN;
  else if (sign == SIGN_MINUS)
    value->bits[SERVICE_WORD_LONG] |= MASK_SIGN;
  else
    exit_code = CODE_ERR;
  return exit_code;
}

int s21_get_exponent(s21_decimal value) {
  return (value.bits[SERVICE_WORD] & MASK_EXPONENT) >> 16;
}

int s21_get_exponent_long(s21_decimal_long value) {
  return (value.bits[SERVICE_WORD_LONG] & MASK_EXPONENT) >> 16;
}

int s21_set_exponent(s21_decimal *value, int exponent) {
  int exit_code = CODE_OK;
  if (exponent >= 0 && exponent <= EXPONENT_MAX) {
    int sign = s21_get_sign(*value);
    value->bits[SERVICE_WORD] = 0;
    value->bits[SERVICE_WORD] |= exponent << 16;
    exit_code = s21_set_sign(value, sign);
  } else
    exit_code = CODE_ERR;
  return exit_code;
}

int s21_set_exponent_long(s21_decimal_long *value, int exponent) {
  int exit_code = CODE_OK;
  if (exponent >= 0 && exponent <= EXPONENT_MAX_LONG) {
    int sign = s21_get_sign_long(*value);
    value->bits[SERVICE_WORD_LONG] = 0;
    value->bits[SERVICE_WORD_LONG] |= exponent << 16;
    exit_code = s21_set_sign_long(value, sign);
  } else
    exit_code = CODE_ERR;
  return exit_code;
}

s21_decimal s21_abs(s21_decimal value) {
  s21_decimal result = value;
  s21_set_sign(&result, SIGN_PLUS);
  return result;
}

s21_decimal_long s21_abs_long(s21_decimal_long value) {
  s21_decimal_long result = value;
  s21_set_sign_long(&result, SIGN_PLUS);
  return result;
}

s21_decimal_long s21_decimal_to_long(s21_decimal value) {
  s21_decimal_long buffer = {
      {value.bits[0], value.bits[1], value.bits[2], 0, 0, 0, 0, value.bits[3]}};
  return buffer;
}

s21_decimal s21_long_to_decimal(s21_decimal_long value) {
  s21_decimal buffer = {
      {value.bits[0], value.bits[1], value.bits[2], value.bits[7]}};
  return buffer;
}

int s21_get_bit(s21_decimal value, int pos) {
  int result = -1;  // заведомо некорректное значение в случае ошибки
  int i = pos / 32;
  if (pos >= 0 && i <= SERVICE_WORD) {
    result = value.bits[i] >> (pos - 32 * i) & 1;
  }
  return result;
}

int s21_get_bit_long(s21_decimal_long value, int pos) {
  int result = -1;  // заведомо некорректное значение в случае ошибки
  int i = pos / 32;
  if (pos >= 0 && i <= SERVICE_WORD_LONG) {
    result = value.bits[i] >> (pos - 32 * i) & 1;
  }
  return result;
}

int s21_set_bit(s21_decimal *value, int pos, int bit) {
  int exit_code = CODE_OK;
  int i = pos / 32;
  if (pos >= 0 && i <= SERVICE_WORD)
    if (bit == 1)
      value->bits[i] |= 1 << (pos - 32 * i);
    else if (bit == 0)
      value->bits[i] = ~(~value->bits[i] | 1 << (pos - 32 * i));
    else
      exit_code = CODE_ERR;
  else
    exit_code = CODE_ERR;
  return exit_code;
}

int s21_set_bit_long(s21_decimal_long *value, int pos, int bit) {
  int exit_code = CODE_OK;
  int i = pos / 32;
  if (pos >= 0 && i <= SERVICE_WORD_LONG && (bit == 0 || bit == 1))
    if (bit == 1)
      value->bits[i] |= 1 << (pos - 32 * i);
    else if (bit == 0)
      value->bits[i] = ~(~value->bits[i] | 1 << (pos - 32 * i));
    else
      exit_code = CODE_ERR;
  else
    exit_code = CODE_ERR;
  return exit_code;
}

void s21_init_zero(s21_decimal *value) {
  for (int i = 0; i <= SERVICE_WORD; i++) value->bits[i] = 0;
}

void s21_init_zero_long(s21_decimal_long *value) {
  for (int i = 0; i <= SERVICE_WORD_LONG; i++) value->bits[i] = 0;
}

void s21_init_inf(s21_decimal *value) {
  value->bits[SERVICE_WORD] |= MASK_INFINITY;
}

void s21_init_inf_long(s21_decimal_long *value) {
  value->bits[SERVICE_WORD_LONG] |= MASK_INFINITY;
}

void s21_init_nan(s21_decimal *value) { value->bits[SERVICE_WORD] |= MASK_NAN; }

void s21_init_nan_long(s21_decimal_long *value) {
  value->bits[SERVICE_WORD_LONG] |= MASK_NAN;
}

int s21_is_zero(s21_decimal value) {
  int exit_code = BOOL_YES;
  if (!s21_is_nan(value))
    for (int i = 0; i < SERVICE_WORD; i++)
      if (value.bits[i] != MASK_ZERO) exit_code = BOOL_NO;
  return exit_code;
}
int s21_is_zero_long(s21_decimal_long value) {
  int exit_code = BOOL_YES;
  if (!s21_is_nan_long(value))
    for (int i = 0; i < SERVICE_WORD_LONG; i++)
      if (value.bits[i] != MASK_ZERO) exit_code = BOOL_NO;
  return exit_code;
}

int s21_is_nan(s21_decimal value) {
  int exit_code = BOOL_NO;
  if ((value.bits[SERVICE_WORD] & MASK_NAN) != 0) exit_code = BOOL_YES;
  return exit_code;
}
int s21_is_nan_long(s21_decimal_long value) {
  int exit_code = BOOL_NO;
  if ((value.bits[SERVICE_WORD_LONG] & MASK_NAN) != 0) exit_code = BOOL_YES;
  return exit_code;
}

int s21_is_inf(s21_decimal value) {
  int exit_code = BOOL_NO;
  if ((value.bits[SERVICE_WORD] & MASK_INFINITY) != 0) exit_code = BOOL_YES;
  return exit_code;
}
int s21_is_inf_long(s21_decimal_long value) {
  int exit_code = BOOL_NO;
  if ((value.bits[SERVICE_WORD_LONG] & MASK_INFINITY) != 0)
    exit_code = BOOL_YES;
  return exit_code;
}