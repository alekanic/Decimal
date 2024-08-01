#include "../test.h"

START_TEST(add_1)  // просто сложение
{
  s21_decimal val1 = {1, 0, 0, 0x0};    // 1
  s21_decimal val2 = {1, 0, 0, MINUS};  //-1
  s21_decimal expected = {0};
  s21_decimal actual = {0};
  ck_assert_int_eq(
      0,
      s21_add(val1, val2, &actual));  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(add_2)  // сложение нулей с разным знаком
{
  s21_decimal val1 = {0, 0, 0, 0x0};    //+0
  s21_decimal val2 = {0, 0, 0, MINUS};  //-0
  s21_decimal expected = {0};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
}
END_TEST

START_TEST(add_3)
// сложение максимального значения unsigned int (255) с
// разным знаком
{
  s21_decimal val1 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal val2 = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  s21_decimal actual = {0};
  s21_decimal expected = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(add_4)  // результирующее число выходит за границы децимала (+)
{
  s21_decimal val1 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal val2 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal actual = {0};
  ck_assert_int_eq(1, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
}
END_TEST

START_TEST(add_5)  // результирующее число выходит за границы децимала (-)
{
  s21_decimal val1 = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  s21_decimal val2 = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  s21_decimal actual = {0};
  ck_assert_int_eq(2, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
}
END_TEST

START_TEST(add_6)  // переход через границы инта вправо
{
  s21_decimal val1 = {MAX_UINT, 0, 0, 0};
  s21_decimal val2 = {1, 0, 0, 0};
  s21_decimal actual = {0};
  s21_decimal expected = {0, 1, 0, 0};
  ck_assert_int_eq(0, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(add_7)  // переход через границы двух интов вправо
{
  s21_decimal val1 = {MAX_UINT, MAX_UINT, 0, 0};
  s21_decimal val2 = {1, 0, 0, 0};
  s21_decimal actual = {0};
  s21_decimal expected = {0, 0, 1, 0};
  ck_assert_int_eq(0, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(add_8)  // переход через границу инта влево (при вычитании)
{
  s21_decimal val1 = {0, 0, ONE, 0};
  s21_decimal val2 = {0, ONE, 0, MINUS};
  s21_decimal actual = {0};
  s21_decimal expected = {0, MAX_UINT, 0, 0};
  ck_assert_int_eq(0, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(add_9)  // переход через границы двух интов влево
{
  s21_decimal val1 = {0, 0, 1, 0};
  s21_decimal val2 = {1, 0, 0, MINUS};
  s21_decimal actual = {0};
  s21_decimal expected = {MAX_UINT, MAX_UINT, 0, 0};
  ck_assert_int_eq(0, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(add_10)  // сложение отрицательных нулей
{
  s21_decimal val1 = {0, 0, 0, MINUS};  //-0
  s21_decimal val2 = {0, 0, 0, MINUS};  //-0
  s21_decimal expected = {0};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
}
END_TEST

START_TEST(add_11)  // сложение отрицательных чисел
{
  s21_decimal val1 = {10, 0, 0, MINUS};
  s21_decimal val2 = {5, 0, 0, MINUS};
  s21_decimal expected = {15, 0, 0, MINUS};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(add_12)  // смена знака
{
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {5, 0, 0, MINUS};
  s21_decimal expected = {5, 0, 0, MINUS};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(add_13)  // сложение с одинаковой экспонентой
{
  s21_decimal val1 = {1, 0, 0, MAX_EXPONENT};
  s21_decimal val2 = {5, 0, 0, MAX_EXPONENT};
  s21_decimal expected = {6, 0, 0, MAX_EXPONENT};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(add_14)  // сложение с разной экспонентой
{
  s21_decimal val1 = {5, 0, 0, MAX_EXPONENT};
  s21_decimal val2 = {1, 0, 0, EXPONENT_27};
  s21_decimal expected = {15, 0, 0, MAX_EXPONENT};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(add_15)  // сложение с разной экспонентой и разным знаком
{
  s21_decimal val1 = {1, 0, 0, MINUS_AND_MAX_EXPONENT};
  // остается экспонента 28, число -1
  s21_decimal val2 = {1, 0, 0, EXPONENT_27};
  // домножается на 10, число будет 10
  s21_decimal expected = {9, 0, 0, MAX_EXPONENT};  // 10 - 1 = 9
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(add_16)  // сложение с экспонентой больше 28
{
  s21_decimal val1 = {5, 0, 0, MAX_EXPONENT};
  s21_decimal val2 = {0, 0, 0, TOO_MUCH_EXPONENT};
  s21_decimal expected = {5, 0, 0, MAX_EXPONENT};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &actual));
  // проверка успешности выполнения s21_add
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

// далее тесты Ани

START_TEST(add_17) {
  s21_decimal val1 = {{15, 0, 0, 0x0}};         // 15
  s21_decimal val2 = {{15, 0, 0, 0x80000000}};  //-15
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_18) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 6);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(add_19) {
  s21_decimal val1 = {{4, 0, 0, 0x80000000}};  // -4
  s21_decimal val2 = {{2, 0, 0, 0x0}};         // 2
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0x80000000);
}
END_TEST

START_TEST(add_20) {
  s21_decimal val1 = {{0, 2, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(res.bits[1], 2);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(add_21) {
  s21_decimal val1 = {{5, 0, 4, 0x0}};
  s21_decimal val2 = {{5, 0, 4, 0x80000000}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

Suite *suite_s21_add(void) {
  Suite *s1 = suite_create("s21_add");
  TCase *tc1_1 = tcase_create("base");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, add_1);
  tcase_add_test(tc1_1, add_2);
  tcase_add_test(tc1_1, add_3);
  tcase_add_test(tc1_1, add_4);
  tcase_add_test(tc1_1, add_5);
  tcase_add_test(tc1_1, add_6);
  tcase_add_test(tc1_1, add_7);
  tcase_add_test(tc1_1, add_8);
  tcase_add_test(tc1_1, add_9);
  tcase_add_test(tc1_1, add_10);
  tcase_add_test(tc1_1, add_11);
  tcase_add_test(tc1_1, add_12);
  tcase_add_test(tc1_1, add_13);
  tcase_add_test(tc1_1, add_14);
  tcase_add_test(tc1_1, add_15);
  tcase_add_test(tc1_1, add_16);
  tcase_add_test(tc1_1, add_17);
  tcase_add_test(tc1_1, add_18);
  tcase_add_test(tc1_1, add_19);
  tcase_add_test(tc1_1, add_20);
  tcase_add_test(tc1_1, add_21);

  return s1;
}
