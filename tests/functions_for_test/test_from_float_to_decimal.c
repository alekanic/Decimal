#include "../test.h"

// тесты lumpkinh

START_TEST(from_float_to_decimal_1) {
  s21_decimal val = {0, 0, 0, 0};
  float res = 0.;
  float tmp = -1234.56789;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_float_to_decimal_2) {
  s21_decimal val = {0, 0, 0, 0};
  float res = 0.;
  float tmp = 1234.56789;
  s21_from_float_to_decimal(tmp, &val);
  s21_from_decimal_to_float(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

// тесты dobbyfer

START_TEST(from_float_to_decimal_3) {  // перевод единицы в децимал
  float val1 = 1.;
  s21_decimal actual;
  int result = s21_from_float_to_decimal(val1, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха выполнения функции
  s21_decimal expected = {1, 0, 0, 0};
  // проверка получившегося децимала
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(
    from_float_to_decimal_4) {  // перевод 0.1 в децимал (проверяем экспоненту)
  float val1 = 0.1;
  s21_decimal actual;
  int result = s21_from_float_to_decimal(val1, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха выполнения функции
  s21_decimal expected = {1, 0, 0, EXPONENT_1};
  // проверка получившегося децимала
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(
    from_float_to_decimal_5) {  // перевод -0.1 в децимал (проверяем экспоненту)
  float val1 = -0.1;
  s21_decimal actual;
  int result = s21_from_float_to_decimal(val1, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха выполнения функции
  s21_decimal expected = {1, 0, 0, MINUS_AND_EXPONENT_1};
  // проверка получившегося децимала
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(from_float_to_decimal_6) {  // устанавливаем максимальную экспоненту
                                       // для единицы
  float val1 = 1e-28;  // 1 / 10^28 степени, то есть единица с экспонентой 28
  s21_decimal actual;
  int result = s21_from_float_to_decimal(val1, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха выполнения функции
  s21_decimal expected = {1, 0, 0, MAX_EXPONENT};
  // проверка получившегося децимала
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(from_float_to_decimal_7) {  // устанавливаем максимальную экспоненту
                                       // для нуля
  float val1 = 0e-28;  // 0 / 10^28 степени, то есть единица с экспонентой 28
  s21_decimal actual;
  int result = s21_from_float_to_decimal(val1, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха выполнения функции
  s21_decimal expected = {0, 0, 0, 0};
  // проверка получившегося децимала
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(from_float_to_decimal_8) {
  // устанавливаем очень маленькое число,
  // которое должно вернуть ошибку
  float val1 = 1e-30;
  // eсли числа слишком малы (0 < |x| < 1e-28), вернуть
  // ошибку и значение, равное 0
  s21_decimal actual;
  int result = s21_from_float_to_decimal(val1, &actual);
  ck_assert_int_eq(1, result);  // проверка успеха выполнения функции
  s21_decimal expected = {0, 0, 0, 0};
  // проверка получившегося децимала
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST
/*
START_TEST(from_float_to_decimal_9) { // устанавливаем очень большое число,
которое должно вернуть ошибку float val1 = 792281625142643375935439503356; //
eсли числа слишком велики (|x| > 79,228,162,514,264,337,593,543,950,335) или
равны бесконечности, вернуть ошибку s21_decimal actual; int result =
s21_from_float_to_decimal(val1, &actual); ck_assert_int_eq(1, result); //
проверка успеха выполнения функции
}
END_TEST

START_TEST(from_float_to_decimal_10) { // устанавливаем очень большое по модулю
число, которое должно вернуть ошибку float val1 = -80; // eсли числа слишком
велики (|x| > 79,228,162,514,264,337,593,543,950,335) или равны бесконечности,
вернуть ошибку s21_decimal actual; int result = s21_from_float_to_decimal(val1,
&actual); ck_assert_int_eq(1, result); // проверка успеха выполнения функции
}
END_TEST
*/

START_TEST(from_float_to_decimal_11) {
  float val1 = -80000000;
  s21_decimal actual;
  int result = s21_from_float_to_decimal(val1, &actual);
  ck_assert_int_eq(0, result);  // проверка успеха выполнения функции
  s21_decimal expected = {80000000, 0, 0, MINUS};
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
}
END_TEST
Suite *suite_s21_from_float_to_decimal(void) {
  Suite *s1 = suite_create("s21_from_float_to_decimal");
  TCase *tc1_1 = tcase_create("convertation");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, from_float_to_decimal_1);
  tcase_add_test(tc1_1, from_float_to_decimal_2);
  tcase_add_test(tc1_1, from_float_to_decimal_3);
  tcase_add_test(tc1_1, from_float_to_decimal_4);
  tcase_add_test(tc1_1, from_float_to_decimal_5);
  tcase_add_test(tc1_1, from_float_to_decimal_6);
  tcase_add_test(tc1_1, from_float_to_decimal_7);
  tcase_add_test(tc1_1, from_float_to_decimal_8);
  // tcase_add_test(tc1_1, from_float_to_decimal_9);
  // tcase_add_test(tc1_1, from_float_to_decimal_10);
  tcase_add_test(tc1_1, from_float_to_decimal_11);

  return s1;
}