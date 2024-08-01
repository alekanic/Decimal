#include "../test.h"

// тесты Ани

START_TEST(mul_1) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  a.bits[0] = 10;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0x80000000;
  b.bits[0] = 10;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = 0x80000000;
  s21_decimal res = {{0, 0, 0, 0}};
  s21_mul(a, b, &res);
  ck_assert_int_eq(res.bits[0], 100);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(mul_2) {
  int num1 = -20;
  int num2 = 20;
  int prod_int = -400;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_3) {
  int num1 = 3333;
  int num2 = 546;
  int res_origin = 1819818;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_4) {
  int num1 = -3333;
  int num2 = 4;
  int res_origin = -13332;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_5) {
  s21_decimal a = {{1213, 0, 0, 0}};
  s21_decimal b = {{5555, 0, 0, 0}};
  s21_decimal res;
  s21_set_exponent(&a, 2);
  s21_set_exponent(&b, 2);
  s21_decimal c = {{6738215, 0, 0, 0}};
  s21_set_exponent(&c, 4);
  s21_mul(a, b, &res);
  ck_assert_int_eq(c.bits[0], res.bits[0]);
  ck_assert_int_eq(c.bits[1], res.bits[1]);
  ck_assert_int_eq(c.bits[2], res.bits[2]);
  ck_assert_int_eq(c.bits[3], res.bits[3]);
}
END_TEST

// тесты dobbyfer

START_TEST(mul_6)  // умножение одного инта
{
  s21_decimal a = {100, 0, 0, 0};
  s21_decimal b = {2, 0, 0, 0};
  s21_decimal expected = {200, 0, 0, 0};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_mul(a, b, &actual));  // проверка выполнения
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(mul_7)  // умножение 3-х интов
{
  s21_decimal dec1 = {100, 1000, 100, 0};
  s21_decimal dec2 = {5, 0, 0, 0};
  s21_decimal actual = {0};
  s21_decimal expected = {500, 5000, 500, 0};
  ck_assert_int_eq(0, s21_mul(dec1, dec2, &actual));  // проверка выполнения
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(mul_8)  // умножение со сменой знака
{
  s21_decimal dec1 = {100, 0, 0, 0};
  s21_decimal dec2 = {1, 0, 0, MINUS};
  s21_decimal actual = {0};
  s21_decimal expected = {100, 0, 0, MINUS};
  ck_assert_int_eq(0, s21_mul(dec1, dec2, &actual));  // проверка выполнения
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(mul_9)  // умножение на ноль
{
  s21_decimal dec1 = {100, 0, 0, 0};
  s21_decimal dec2 = {0};
  s21_decimal actual = {0};
  s21_decimal expected = {0};
  ck_assert_int_eq(0, s21_mul(dec1, dec2, &actual));  // проверка выполнения
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(mul_10)  // умножение нуля на какое-то число
{
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {50, 0, 0, 0};
  s21_decimal expected = {0};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_mul(dec1, dec2, &actual));  // проверка выполнения
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(mul_11)  // граница сверху
{
  s21_decimal dec1 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal dec2 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal actual = {0};
  ck_assert_int_eq(1, s21_mul(dec1, dec2, &actual));  // проверка выполнения
}
END_TEST

START_TEST(mul_12)  // граница снизу
{
  s21_decimal dec1 = {1, 0, 0, MAX_EXPONENT};
  s21_decimal dec2 = {1, 0, 0, MAX_EXPONENT};  // очень маленькое число
  s21_decimal actual = {0};
  ck_assert_int_eq(2, s21_mul(dec1, dec2, &actual));  // проверка выполнения
}
END_TEST

START_TEST(mul_13)  // умножение отрицательного числа на отрицательное
{
  s21_decimal dec1 = {1, 0, 0, MINUS};
  s21_decimal dec2 = {1, 0, 0, MINUS};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, 0};
  ck_assert_int_eq(0, s21_mul(dec1, dec2, &actual));  // проверка выполнения
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(mul_14)  // умножение чисел с разной экспонентой (делитель меньше)
{
  s21_decimal dec1 = {10, 0, 0, MAX_EXPONENT};
  s21_decimal dec2 = {10, 0, 0, EXPONENT_27};  // 100
  s21_decimal actual = {0};
  s21_decimal expected = {1000, 0, 0, MAX_EXPONENT};
  ck_assert_int_eq(0, s21_mul(dec1, dec2, &actual));  // проверка выполнения
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(mul_15)  // умножение чисел с разной экспонентой (делитель больше)
{
  s21_decimal dec1 = {10, 0, 0, EXPONENT_27};  // 100
  s21_decimal dec2 = {10, 0, 0, MAX_EXPONENT};
  s21_decimal actual = {0};
  s21_decimal expected = {1000, 0, 0, MAX_EXPONENT};
  ck_assert_int_eq(0, s21_mul(dec1, dec2, &actual));  // проверка выполнения
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(mul_16)  // экспонента у множителя больше 28
{
  s21_decimal dec1 = {100, 0, 0, TOO_MUCH_EXPONENT};
  s21_decimal dec2 = {10, 0, 0, MAX_EXPONENT};
  s21_decimal actual = {0};
  s21_decimal expected = {100, 0, 0, MAX_EXPONENT};
  ck_assert_int_eq(0, s21_mul(dec1, dec2, &actual));  // проверка выполнения
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(mul_17)  // умножение нуля на число с другой экспонентой
{
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {1, 0, 0, TOO_MUCH_EXPONENT};
  s21_decimal expected = {0};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_mul(dec1, dec2, &actual));  // проверка выполнения
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

Suite *suite_s21_mul(void) {
  Suite *s1 = suite_create("s21_mul");
  TCase *tc1_1 = tcase_create("base");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, mul_1);
  tcase_add_test(tc1_1, mul_2);
  tcase_add_test(tc1_1, mul_4);
  tcase_add_test(tc1_1, mul_5);
  tcase_add_test(tc1_1, mul_6);
  tcase_add_test(tc1_1, mul_7);
  tcase_add_test(tc1_1, mul_8);
  tcase_add_test(tc1_1, mul_9);
  tcase_add_test(tc1_1, mul_10);
  tcase_add_test(tc1_1, mul_11);
  tcase_add_test(tc1_1, mul_12);
  tcase_add_test(tc1_1, mul_13);
  tcase_add_test(tc1_1, mul_14);
  tcase_add_test(tc1_1, mul_15);
  tcase_add_test(tc1_1, mul_16);
  tcase_add_test(tc1_1, mul_17);

  return s1;
}
