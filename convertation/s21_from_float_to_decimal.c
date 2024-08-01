#include <stdlib.h>

#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int exit_code = CODE_OK;
  if (!dst)
    exit_code = CODE_ERR;  // некорректный указатель вывода
  else {
    int sign = signbit(src);
    if (sign) src = fabsf(src);
    s21_init_zero(dst);  // запишем ноль без проверки
    // но проверим другие граничные значения
    if (src == 0)
      ;  // если ноль, не проверяем больше ничего
    else if (src < DEC_EPSILON)
      // слишком малое значение = 0 уже
      exit_code = CODE_ERR;
    else if (isinf(src) || (src > DEC_MAX)) {
      // слишком большое значение = INFINITY
      exit_code = CODE_ERR;
      s21_init_inf(dst);
    } else if (isnan(src)) {
      // не-число
      exit_code = CODE_ERR;
      s21_init_nan(dst);
    } else {  // дальше общее преобразование float в s21_decimal
      f2d(src, dst);
    }
    // удалим незначащие нули
    remove_trailing_zeros(dst);
    //  и запишем минус, если был
    if (sign) s21_set_sign(dst, SIGN_MINUS);
  }
  return exit_code;
}

void f2d(float src, s21_decimal *dst) {
  int exp = 0;
  // получим экспоненту конвертируемого числа
  // и нормализованную мантиссу (вида 1.xxx...)
  double mantissa = get_dec_float_exp(src, &exp);

  // цифры мантиссы после запятой, которые влезут при конвертации
  // не более шести значащих
  int precision = 6;

  // порядок (степень размерности) округления мантиссы
  // для целого числа - 10^0 = единица
  int to_round = pow(10, precision);

  if (exp < -22) {  // exp < -22
    // учтем нижнее ограничение степени типа s21_decimal
    // при семи значащих цифрах
    // 1.234567890 float -22: 0.0000000000000000000001234567...
    // 1234567.. decimal -28: 0.0000000000000000000001234567

    // цифры мантиссы после запятой, которые влезут при конвертации
    precision = exp + EXPONENT_MAX;
    // порядок (степень размерности) округления мантиссы
    to_round = pow(10, precision);
    // переведем мантиссу в пригодную для записи
    dst->bits[0] = (int)round(mantissa * to_round);
    // запишем степень размерности - максимальная в данном случае
    s21_set_exponent(dst, EXPONENT_MAX);
  } else if (exp < 0) {  // exp = -22..0
    // переведем мантиссу в пригодную для записи
    dst->bits[0] = (int)round(mantissa * to_round);
    // 10^(6 + |e|)
    s21_set_exponent(dst, precision + (-exp));
  } else if (exp < 7) {  // exp = 0..7
    // переведем мантиссу в пригодную для записи
    dst->bits[0] = (int)round(mantissa * to_round);
    // 10^(6 + e)
    s21_set_exponent(dst, precision - exp);
  } else {  // exp >= 7
    // тут экпонента уже нулевая, это число - целое
    dst->bits[0] = (int)round(mantissa * to_round);
    //  мантиссу необходимо увеличить кратно степени exp 10^|6 - e|
    s21_decimal tmp;
    s21_from_int_to_decimal((int)pow(10, abs(6 - exp)), &tmp);
    s21_mul(*dst, tmp, dst);
  }
}
/*
s21_decimal s21_dec_pow(s21_decimal src, int pow) {
  s21_decimal tmp = src;
  for (int i = 0; i < pow; i++) s21_mul(tmp, src, &tmp);
  return tmp;
}
*/
double get_dec_float_exp(const double df, int *exp_df) {
  *exp_df = 0;
  double mantissa_df = fabs(df);
  if (df != 0.0) {
    while (mantissa_df > 2) {
      mantissa_df = mantissa_df / 10;
      *exp_df += 1;
    }
    while (mantissa_df < 1) {
      mantissa_df = mantissa_df * 10;
      *exp_df -= 1;
    }
    if (signbit(df)) mantissa_df = -mantissa_df;
  }
  return mantissa_df;
}