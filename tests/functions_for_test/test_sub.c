#include "../test.h"

// тесты Ани

START_TEST(sub_1) {
  s21_decimal src1, src2, origin;
  src1.bits[0] = 6;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src2.bits[0] = 5;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);
  origin.bits[0] = 1;
  origin.bits[1] = 0;
  origin.bits[2] = 0;
  origin.bits[3] = 0;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(sub_2) {
  s21_decimal src1, src2, origin;
  src1.bits[0] = 5;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src2.bits[0] = 6;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);
  origin.bits[0] = 1;
  origin.bits[1] = 0;
  origin.bits[2] = 0;
  origin.bits[3] = 0x80000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(sub_3) {
  s21_decimal src1, src2, origin;
  src1.bits[0] = 0;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;

  src2.bits[0] = 3;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 3;
  origin.bits[1] = 0;
  origin.bits[2] = 0;
  origin.bits[3] = 0x80000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(sub_4) {
  s21_decimal src1, src2, origin;
  src1.bits[0] = 3;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;

  src2.bits[0] = 0;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);

  origin.bits[0] = 3;
  origin.bits[1] = 0;
  origin.bits[2] = 0;
  origin.bits[3] = 0;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(sub_5) {
  s21_decimal src1, src2, origin;
  src1.bits[0] = -1;
  src1.bits[1] = -1;
  src1.bits[2] = -1;
  src1.bits[3] = 0;
  src2.bits[0] = -1;
  src2.bits[1] = -1;
  src2.bits[2] = -1;
  src2.bits[3] = 0;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &result);
  origin.bits[0] = 0;
  origin.bits[1] = 0;
  origin.bits[2] = 0;
  origin.bits[3] = 0;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

// тесты dobbyfer

START_TEST(sub_6)  // вычитание отрицательного числа
{
  s21_decimal val1 = {1, 0, 0, 0x0};    // 1
  s21_decimal val2 = {1, 0, 0, MINUS};  //- -1
  s21_decimal expected = {2, 0, 0, 0};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(sub_7)  // вычитание нулей с разным знаком
{
  s21_decimal val1 = {0, 0, 0, 0x0};    //+0
  s21_decimal val2 = {0, 0, 0, MINUS};  //-0
  s21_decimal expected = {0};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
}
END_TEST

START_TEST(sub_8)  // вычитание максимального значения unsigned int (255)
{
  s21_decimal val1 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal val2 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal actual = {0};
  s21_decimal expected = {0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(sub_9)  // результирующее число выходит за границы децимала (+)
{
  s21_decimal val1 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal val2 = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  s21_decimal actual = {0};
  ck_assert_int_eq(1, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
}
END_TEST

START_TEST(sub_10)  // результирующее число выходит за границы децимала (-)
{
  s21_decimal val1 = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  s21_decimal val2 = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  s21_decimal actual = {0};
  ck_assert_int_eq(
      2, s21_sub(val1, val2, &actual));  // проверка успешности выполнения
}
END_TEST

START_TEST(sub_11)  // переход через границы инта вправо
{
  s21_decimal val1 = {MAX_UINT, 0, 0, 0};
  s21_decimal val2 = {1, 0, 0, MINUS};
  s21_decimal actual = {0};
  s21_decimal expected = {0, 1, 0, 0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(sub_12)  // переход через границы двух интов вправо
{
  s21_decimal val1 = {MAX_UINT, MAX_UINT, 0, 0};
  s21_decimal val2 = {1, 0, 0, MINUS};
  s21_decimal actual = {0};
  s21_decimal expected = {0, 0, 1, 0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(sub_13)  // переход через границу инта влево (при вычитании)
{
  s21_decimal val1 = {0, 0, ONE, 0};
  s21_decimal val2 = {0, ONE, 0, 0};
  s21_decimal actual = {0};
  s21_decimal expected = {0, MAX_UINT, 0, 0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(sub_14)  // переход через границы двух интов влево
{
  s21_decimal val1 = {0, 0, 1, 0};
  s21_decimal val2 = {1, 0, 0, MINUS};
  s21_decimal actual = {0};
  s21_decimal expected = {MAX_UINT, MAX_UINT, 0, 0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(sub_15)  // вычитание отрицательных нулей
{
  s21_decimal val1 = {0, 0, 0, MINUS};  //-0
  s21_decimal val2 = {0, 0, 0, MINUS};
  s21_decimal expected = {0};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
}
END_TEST

START_TEST(sub_16)  // вычитание отрицательных чисел
{
  s21_decimal val1 = {10, 0, 0, MINUS};
  s21_decimal val2 = {5, 0, 0, MINUS};
  s21_decimal expected = {5, 0, 0, MINUS};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(sub_17)  // смена знака
{
  s21_decimal val1 = {0, 0, 0, 0};
  s21_decimal val2 = {5, 0, 0, 0};
  s21_decimal expected = {5, 0, 0, MINUS};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(sub_18)  // вычитание с одинаковой экспонентой
{
  s21_decimal val1 = {1, 0, 0, MAX_EXPONENT};
  s21_decimal val2 = {5, 0, 0, MINUS_AND_MAX_EXPONENT};
  s21_decimal expected = {6, 0, 0, MAX_EXPONENT};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(sub_19)  // вычитание с разной экспонентой
{
  s21_decimal val1 = {15, 0, 0, MAX_EXPONENT};
  s21_decimal val2 = {1, 0, 0, EXPONENT_27};
  s21_decimal expected = {5, 0, 0, MAX_EXPONENT};
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(sub_20)  // вычитание с разной экспонентой и разным знаком
{
  s21_decimal val1 = {1, 0, 0, MINUS_AND_MAX_EXPONENT};
  // остается экспонента 28, число -1
  s21_decimal val2 = {1, 0, 0, EXPONENT_27};
  // домножается на 10, число будет -10
  s21_decimal expected = {11, 0, 0, MINUS_AND_MAX_EXPONENT};
  // 10 - 1 = 9
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

START_TEST(sub_21)  // вычитание с экспонентой больше 28
{
  s21_decimal val1 = {5, 0, 0, MAX_EXPONENT};
  s21_decimal val2 = {10, 0, 0, TOO_MUCH_EXPONENT};  // 10 / 10 = 1
  s21_decimal expected = {4, 0, 0, MAX_EXPONENT};    // 5 - 1 = 4
  s21_decimal actual = {0};
  ck_assert_int_eq(0, s21_sub(val1, val2, &actual));
  // проверка успешности выполнения
  // проверка правильности сравнения
  ck_assert_int_eq(expected.bits[0], actual.bits[0]);
  ck_assert_int_eq(expected.bits[1], actual.bits[1]);
  ck_assert_int_eq(expected.bits[2], actual.bits[2]);
  ck_assert_int_eq(expected.bits[3], actual.bits[3]);
}
END_TEST

Suite *suite_s21_sub(void) {
  Suite *s1 = suite_create("s21_sub");
  TCase *tc1_1 = tcase_create("base");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, sub_1);
  tcase_add_test(tc1_1, sub_2);
  tcase_add_test(tc1_1, sub_3);
  tcase_add_test(tc1_1, sub_4);
  tcase_add_test(tc1_1, sub_5);
  tcase_add_test(tc1_1, sub_6);
  tcase_add_test(tc1_1, sub_7);
  tcase_add_test(tc1_1, sub_8);
  tcase_add_test(tc1_1, sub_9);
  tcase_add_test(tc1_1, sub_10);
  tcase_add_test(tc1_1, sub_11);
  tcase_add_test(tc1_1, sub_12);
  tcase_add_test(tc1_1, sub_13);
  tcase_add_test(tc1_1, sub_14);
  tcase_add_test(tc1_1, sub_15);
  tcase_add_test(tc1_1, sub_16);
  tcase_add_test(tc1_1, sub_17);
  tcase_add_test(tc1_1, sub_18);
  tcase_add_test(tc1_1, sub_19);
  tcase_add_test(tc1_1, sub_20);
  tcase_add_test(tc1_1, sub_21);

  return s1;
}
