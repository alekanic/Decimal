#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_code = CODE_OK;
  // в ТЗ не определена ошибка некорректных значений или указателей
  // if (!result || !s21_is_decimal(value_1) || !s21_is_decimal(value_2))
  //  exit_code = CODE_ERR;

  // Здесь сложение
  s21_init_zero(result);
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  s21_decimal abs_1 = s21_abs(value_1), abs_2 = s21_abs(value_2);

  // если одно слагаемое ноль, то записываем результат без вычислений
  if (s21_is_zero(value_1))
    *result = value_2;
  else if (s21_is_zero(value_2))
    *result = value_1;
  else if (!sign_1 && !sign_2) {  // ++
    // v1 + v2
    *result = s21_add_positive(value_1, value_2);
  } else if ((!sign_1 && sign_2) || (sign_1 && !sign_2)) {  // +- // -+
    // GREATER_SIGN(|GREATER| - |LOWER|)
    if (s21_is_greater(abs_1, abs_2)) {
      exit_code = sub_from_greater(abs_1, abs_2, result);
      s21_set_sign(result, sign_1);
    } else if (s21_is_greater(abs_2, abs_1)) {
      exit_code = sub_from_greater(abs_2, abs_1, result);
      s21_set_sign(result, sign_2);
    }
    // условие ниже НЕ НУЖНО, оставляю закомментированным для наглядности:
    // else if (s21_is_equal(abs_1, abs_2))
    //   ;  // ничего не делаем - ноль уже записан в результат
  } else if (sign_1 && sign_2) {  // --
                                  // -(|v1| + |v2|)
    *result = s21_add_positive(abs_1, abs_2);
    s21_negate(*result, result);
  }
  // проверим, что там за число получилось
  // если inf - выдать ошибку, для nan - ошибка не определена
  if (s21_is_inf(*result)) {  // бесконечность ли?
    if (s21_get_sign(*result))
      exit_code = CODE_ERR_TOO_SMALL;  // отрицательная
    else
      exit_code = CODE_ERR_TOO_BIG;  // положительная
  }
  return exit_code;
}

int just_add_long(s21_decimal_long value_1, s21_decimal_long value_2,
                  s21_decimal_long *result) {
  int carry_bit = 0;  // флаг переноса при сложении разрядов
  // дальше эмуляция логического полного сумматора
  for (int i = 0; i < MANTISSA_LENGTH_LONG; i++) {
    // запишем результат сложения битов с учетом входящего переноса
    // S[i] = A[i] ^ B[i] ^ Pin
    s21_set_bit_long(result, i,
                     s21_get_bit_long(value_1, i) ^
                         s21_get_bit_long(value_2, i) ^ carry_bit);
    // обновим значение исходящего переноса (для следующего разряда)
    // Pout = (A[i] & B[i]) | (Pin & (A[i] ^ B[i]))
    carry_bit = (s21_get_bit_long(value_1, i) & s21_get_bit_long(value_2, i)) |
                (carry_bit &
                 (s21_get_bit_long(value_1, i) ^ s21_get_bit_long(value_2, i)));
  }
  return carry_bit;
}

s21_decimal s21_add_positive(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal result = {0};  // инициализируем нулем результат
  //  запишем переменные в длинные
  s21_decimal_long value_1_long = s21_decimal_to_long(value_1),
                   value_2_long = s21_decimal_to_long(value_2),
                   result_long = s21_decimal_to_long(result);
  // выровняем по экспоненте
  alignment_long(&value_1_long, &value_2_long);
  // непосредственно сложим два лонга
  int overflow = add_aligned_long(value_1_long, value_2_long, &result_long);
  // запишем служебную часть из любого слагаемого
  result_long.bits[SERVICE_WORD_LONG] = value_1_long.bits[SERVICE_WORD_LONG];
  // если переполнение, запишем бесконечность (временно)
  // todo - переделать на банковское округление
  if (overflow)
    s21_init_inf(&result);
  else
    for (int i = 3; i < SERVICE_WORD_LONG; i++)
      if (result_long.bits[i] != 0) s21_init_inf(&result);

  // если не было переполнения, конвертируем из лонга
  if (s21_is_decimal(result)) result = s21_long_to_decimal(result_long);
  return result;
}

int is_div_by_ten(s21_decimal value) {
  int exit_code = BOOL_NO;
  if (s21_get_bit(value, 0) == 0) {  // первый признак - число четное
    int tmp = 0;
    for (int i = 0; i < MANTISSA_LENGTH; i += 4) {
      for (int j = i; j < i + 4; j++)
        if (s21_get_bit(value, j)) tmp += pow(2, j % 4);
      tmp %= 5;  // сумму шестнадцатеричных знаков числа делим на пять по модулю
    }  // если в остатке ноль, выполняется второй признак:
    if (!tmp) exit_code = BOOL_YES;  // второй признак - делится на пять
  }  // этого достаточно, чтобы утверждать, что число делится на 10
  return exit_code;
}

int is_div_by_ten_long(s21_decimal_long value) {
  int exit_code = BOOL_NO;
  if (s21_get_bit_long(value, 0) == 0) {  // первый признак - число четное
    int tmp = 0;
    for (int i = 0; i < MANTISSA_LENGTH_LONG; i += 4) {
      for (int j = i; j < i + 4; j++)
        if (s21_get_bit_long(value, j)) tmp += pow(2, j % 4);
      tmp %= 5;  // сумму шестнадцатеричных знаков числа делим на пять по модулю
    }  // если в остатке ноль, выполняется второй признак:
    if (!tmp) exit_code = BOOL_YES;  // второй признак - делится на пять
  }  // этого достаточно, чтобы утверждать, что число делится на 10
  return exit_code;
}

void remove_trailing_zeros(s21_decimal *value) {
  s21_decimal_long val = s21_decimal_to_long(*value);
  remove_trailing_zeros_long(&val);
  *value = s21_long_to_decimal(val);
}

void remove_trailing_zeros_long(s21_decimal_long *value) {
  int exp = s21_get_exponent_long(*value);
  //  если экспонента больше нуля и мантисса делится на 10
  while ((exp > 0) && (is_div_by_ten_long(*value))) {
    // уменьшим и запишем новую экспоненту
    downscale_long(value);
    exp = s21_get_exponent_long(*value);
  }
}

void downscale(s21_decimal *value) {
  s21_decimal result = {0};
  int tmp = 0;
  // cлужебную часть - в результат
  result.bits[SERVICE_WORD] = value->bits[SERVICE_WORD];
  // экспоненту уменьшить на единицу
  s21_set_exponent(&result, s21_get_exponent(*value) - 1);
  // пройдемся по всей мантиссе
  for (int i = MANTISSA_LENGTH - 1; i >= 0; i--) {
    tmp *= 2;  // удвоим временную сумму
    tmp += s21_get_bit(*value, i);  // прибавим текущий бит
    result = s21_shift_left(result, 1);  // сдвинем результат влево
    if (tmp >= 10) {        // если сумма больше десяти
      result.bits[0] += 1;  // прибавим единицу
      tmp -= 10;            // и уменьшим сумму
    }
  }
  *value = result;  // копирует result -> value
}

void downscale_long(s21_decimal_long *value) {
  s21_decimal_long result = {0};
  int tmp = 0;
  // cлужебную часть - в результат
  result.bits[SERVICE_WORD_LONG] = value->bits[SERVICE_WORD_LONG];
  // экспоненту уменьшить на единицу
  s21_set_exponent_long(&result, s21_get_exponent_long(*value) - 1);
  // пройдемся по всей мантиссе
  for (int i = MANTISSA_LENGTH_LONG - 1; i >= 0; i--) {
    tmp *= 2;  // удвоим временную сумму
    tmp += s21_get_bit_long(*value, i);  // прибавим текущий бит
    result = s21_shift_left_long(result, 1);  // сдвинем результат влево
    if (tmp >= 10) {        // если сумма больше десяти
      result.bits[0] += 1;  // прибавим единицу
      tmp -= 10;            // и уменьшим сумму
    }
  }
  *value = result;  // копирует result -> value
}

void alignment_long(s21_decimal_long *value_1_long,
                    s21_decimal_long *value_2_long) {
  // убрать незначащие нули, чтобы степени уменьшить до вычислений
  remove_trailing_zeros_long(value_1_long);
  remove_trailing_zeros_long(value_2_long);
  /*
    s21_print_decimal_long(*value_1_long);
    printf(" >> value_1_long sign = %i exp = %i v1 = %u \n",
           s21_get_sign_long(*value_1_long),
    s21_get_exponent_long(*value_1_long), value_1_long->bits[0]);
    s21_print_decimal_long(*value_2_long);
    printf(" >> value_2_long sign = %i exp = %i v1 = %u \n",
           s21_get_sign_long(*value_2_long),
    s21_get_exponent_long(*value_2_long), value_2_long->bits[0]);
  */
  int exp1 = s21_get_exponent_long(*value_1_long),
      exp2 = s21_get_exponent_long(*value_2_long);

  if (exp1 > exp2) {
    upscale_long(value_2_long, exp1);
  } else if (exp1 < exp2) {
    upscale_long(value_1_long, exp2);
  }
  // если степени равны, нечего выравнивать
}

int upscale_long(s21_decimal_long *value, int new_exponent) {
  int old_exponent = s21_get_exponent_long(*value);
  s21_decimal_long result = {0};
  int overflow = 0;
  // для увеличения экспоненты на единицу, мантиссу надо увелиxить в 10 раз
  for (int i = old_exponent; i < new_exponent; i++) {
    for (int j = 0; j < 10; j++)
      overflow = just_add_long(result, *value, &result);
    // запишем новое значение и новую экспоненту
    *value = result;
    s21_init_zero_long(&result);
  }
  s21_set_exponent_long(value, new_exponent);
  return overflow;
}

int add_aligned_long(s21_decimal_long value_1, s21_decimal_long value_2,
                     s21_decimal_long *result) {
  int carry_bit = just_add_long(value_1, value_2, result);
  // если мантисса не влезла в лонг - использовать банковское округление
  // todo
  // по возможности - уменьшим разрядность записи
  remove_trailing_zeros_long(result);
  return carry_bit;
}
