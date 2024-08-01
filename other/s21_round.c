#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int exit_code = CODE_ERR;
  // проверим корректность числа и указателя
  if (s21_is_decimal(value) && result) {
    int sign = s21_get_sign(value);
    // сначала запишем целую часть в результат
    s21_truncate(value, result);
    if (!s21_is_equal(value, *result)) {
      // если была дробная часть, нужно ее выделить
      // и выяснить, куда округлять с учетом знака
      s21_decimal one = {{1, 0, 0, 0}};  // для корректировки результата
      s21_decimal half;  // для сравнения
      s21_from_float_to_decimal(0.5, &half);
      s21_decimal fraction;  // только дробная часть числа
      s21_sub(s21_abs(value), s21_abs(*result), &fraction);

      // корректируем результат по дробной части до целого
      if (s21_is_greater(fraction, half)) {  // дробь больше половины
        if (sign)  // если отрицательное, окрулим на -1 до ближайшего целого
          s21_sub(*result, one, result);
        else  // если положительное округлим на +1 до ближайшего целого
          s21_add(*result, one, result);
      } else if (s21_is_equal(fraction, half)) {  // дробь ровно 0,5
        if (s21_get_bit(*result, 0)) {  // нечетное с половиной
          if (sign)  // отрицательное, округлим на -1 до четного целого
            s21_sub(*result, one, result);
          else  // положительное, округлим на +1 до четного целого
            s21_add(*result, one, result);
        }  // число без дробной части уже записано, ничего не нужно делать
      }
    }
    exit_code = CODE_OK;
  }
  return exit_code;
}
