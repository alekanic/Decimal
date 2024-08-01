#include "../test.h"

START_TEST(div_1)  // деление одного инта
{
  s21_decimal a = {100, 0, 0, 0};
  s21_decimal b = {50, 0, 0, 0};
  s21_decimal expected = {2, 0, 0, 0};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_div(a, b, &actual));  // проверка выполнения деления
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(div_2)  // деление 3-х интов
{
  s21_decimal dec1 = {100, 1000, 100, 0};
  s21_decimal dec2 = {5, 0, 0, 0};
  s21_decimal actual = {0};
  s21_decimal expected = {20, 200, 20, 0};
  ck_assert_int_eq(0, s21_div(dec1, dec2, &actual));
  // проверка выполнения деления
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(div_3)  // деление со сменой знака
{
  s21_decimal dec1 = {100, 0, 0, 0};
  s21_decimal dec2 = {1, 0, 0, MINUS};
  s21_decimal actual = {0};
  s21_decimal expected = {100, 0, 0, MINUS};
  ck_assert_int_eq(0, s21_div(dec1, dec2, &actual));
  // проверка выполнения деления
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(div_4)  // деление на ноль
{
  s21_decimal dec1 = {100, 0, 0, 0};
  s21_decimal dec2 = {0};
  s21_decimal actual = {0};
  ck_assert_int_eq(3, s21_div(dec1, dec2, &actual));
  // проверка выполнения деления
}
END_TEST

START_TEST(div_5)  // деление нуля на какое-то число
{
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {50, 0, 0, 0};
  s21_decimal expected = {0};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_div(dec1, dec2, &actual));
  // проверка выполнения деления
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(div_6)  // деление на максимальное число
{
  s21_decimal dec1 = {1, 0, 0, 0};
  s21_decimal dec2 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal actual = {0};
  ck_assert_int_eq(2, s21_div(dec1, dec2, &actual));
  // проверка выполнения деления
}
END_TEST

START_TEST(div_7)  // деление на минимальное число
{
  s21_decimal dec1 = {1, 0, 0, 0};
  s21_decimal dec2 = {1, 0, 0, MAX_EXPONENT};  // очень маленькое число
  s21_decimal actual = {0};
  ck_assert_int_eq(1, s21_div(dec1, dec2, &actual));
  // проверка выполнения деления
}
END_TEST

START_TEST(div_8)  // деление отрицательного числа на отрицательное
{
  s21_decimal dec1 = {1, 0, 0, MINUS};
  s21_decimal dec2 = {1, 0, 0, MINUS};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, 0};
  ck_assert_int_eq(0, s21_div(dec1, dec2, &actual));
  // проверка выполнения деления
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(div_9)  // деление чисел с разной экспонентой (делитель меньше)
{
  s21_decimal dec1 = {100, 0, 0, MAX_EXPONENT};
  s21_decimal dec2 = {10, 0, 0, EXPONENT_27};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, MAX_EXPONENT};
  ck_assert_int_eq(0, s21_div(dec1, dec2, &actual));
  // проверка выполнения деления
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(div_10)  // деление чисел с разной экспонентой (делитель больше)
{
  s21_decimal dec1 = {10, 0, 0, EXPONENT_27};
  s21_decimal dec2 = {100, 0, 0, MAX_EXPONENT};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, MAX_EXPONENT};
  ck_assert_int_eq(0, s21_div(dec1, dec2, &actual));
  // проверка выполнения деления
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(div_11)  // экспонента у делимого больше 28
{
  s21_decimal dec1 = {100, 0, 0, TOO_MUCH_EXPONENT};
  s21_decimal dec2 = {10, 0, 0, MAX_EXPONENT};
  s21_decimal actual = {0};
  s21_decimal expected = {1, 0, 0, MAX_EXPONENT};
  ck_assert_int_eq(0, s21_div(dec1, dec2, &actual));
  // проверка выполнения деления
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(div_12)  // деление нуля на число с другой экспонентой
{
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {1, 0, 0, TOO_MUCH_EXPONENT};
  s21_decimal expected = {0};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_div(dec1, dec2, &actual));
  // проверка выполнения деления
  // сравнение expected и actual
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

// Далее тесты Ани

START_TEST(div_13) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{50, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_div(a, b, &res);
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_14) {
  s21_decimal dec1 = {{100, 1000, 100, 0}};
  s21_decimal dec2 = {{5, 0, 0, 0}};
  s21_decimal res = {0};
  s21_div(dec1, dec2, &res);
  ck_assert_int_eq(res.bits[0], 20);
  ck_assert_int_eq(res.bits[1], 200);
  ck_assert_int_eq(res.bits[2], 20);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

Suite *suite_s21_div(void) {
  Suite *s1 = suite_create("s21_div");
  TCase *tc1_1 = tcase_create("base");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, div_1);
  tcase_add_test(tc1_1, div_2);
  tcase_add_test(tc1_1, div_3);
  tcase_add_test(tc1_1, div_4);
  tcase_add_test(tc1_1, div_5);
  tcase_add_test(tc1_1, div_6);
  tcase_add_test(tc1_1, div_7);
  tcase_add_test(tc1_1, div_8);
  tcase_add_test(tc1_1, div_9);
  tcase_add_test(tc1_1, div_10);
  tcase_add_test(tc1_1, div_11);
  tcase_add_test(tc1_1, div_12);
  tcase_add_test(tc1_1, div_13);
  tcase_add_test(tc1_1, div_14);

  return s1;
}
