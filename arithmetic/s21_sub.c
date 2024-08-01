#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_code = CODE_OK, sign_1 = s21_get_sign(value_1),
      sign_2 = s21_get_sign(value_2);
  s21_decimal abs_1 = s21_abs(value_1), abs_2 = s21_abs(value_2);
  // todo - тут проверить условия выхода за границы
  if (s21_is_equal(abs_1, abs_2)) {
    if (sign_1 == sign_2)
      // 1 - 1 = 0
      // (-1) - (-1) = (-1) + 1 = 0
      s21_init_zero(result);
    else {  // if (sign_1 || sign_2)
      // (-1) - 1 = (-2)
      // 1 - (-1) = 1 + 1 = 2
      s21_add(abs_1, abs_2, result);
      s21_set_sign(result, sign_1);
    }
  } else if (s21_is_greater(abs_1, abs_2)) {
    if (sign_1 == sign_2) {
      // 2 - 1 = 1
      // (-2) - (-1) = -(2 - 1) = (-1)
      sub_from_greater(abs_1, abs_2, result);
    } else {  // if (sign_1 || sign_2)
      // (-2) - 1 = -(2 + 1) = (-3)
      // 2 - (-1) = 2 + 1 = 3
      s21_add(abs_1, abs_2, result);
    }
    s21_set_sign(result, sign_1);
  } else {  // abs_1 < abs_2
    if (sign_1 == sign_2) {
      // 1 - 2 = (-2) - (-1) = -(2 - 1) = (-1)
      // (-1) - (-2) = -(1 - 2) = -(-1) = 1
      sub_from_greater(abs_2, abs_1, result);
      s21_set_sign(result, !sign_1);
    } else {  // if (sign_1 || sign_2)
      // 1 - (-2) = 1 + 2 = 3
      // (-1) - 2 = -(1 + 2) = (-3)
      s21_add(abs_1, abs_2, result);
      s21_set_sign(result, sign_1);
    }
  }
  return exit_code;
}

int sub_from_greater(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  s21_decimal_long val_1 = s21_decimal_to_long(value_1),
                   val_2 = s21_decimal_to_long(value_2),
                   one = {{1, 0, 0, 0, 0, 0, 0, 0}}, res;
  alignment_long(&val_1, &val_2);
  // дальше используем двоичный сумматор для вычитания по формуле дополнения:
  // A - B = A + [~B] + 1
  // например: 13 - 2 = 13 + [13] + 1 = 11
  // 1101 - 0010 = 1101 + [1101] + 0001 = 1010 + 0001 = 1011
  // для этого инвертируем второе слагаемое
  invert_long(&val_2);
  // сложим с первым
  just_add_long(val_1, val_2, &res);
  res.bits[SERVICE_WORD_LONG] = val_1.bits[SERVICE_WORD_LONG];
  // добавим единицу
  just_add_long(res, one, &res);
  // по возможности - уменьшим разрядность итоговой записи
  remove_trailing_zeros_long(&res);
  // todo - тут надо бы округление сделать, если переполнение
  // запишем результат
  *result = s21_long_to_decimal(res);
  return 0;
}

void invert_long(s21_decimal_long *value) {
  for (int i = 0; i < MANTISSA_LENGTH_LONG; i++) {
    s21_set_bit_long(value, i, !s21_get_bit_long(*value, i));
  }
}