#include "../test.h"

START_TEST(common_1)  // get_sign плюс
{
  s21_decimal a = {100, 0, 0, 0};
  ck_assert_int_eq(0, s21_get_sign(a));
}
END_TEST

START_TEST(common_2)  // get_sign плюс с наличием экспоненты
{
  s21_decimal a = {100, 0, 0, EXPONENT_1};
  ck_assert_int_eq(0, s21_get_sign(a));
}
END_TEST

START_TEST(common_3)  // get_sign минус
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  ck_assert_int_eq(1, s21_get_sign(a));
}
END_TEST

START_TEST(common_4)  // get_sign минус с наличием экспоненты
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS_AND_EXPONENT_1};
  ck_assert_int_eq(1, s21_get_sign(a));
}
END_TEST

START_TEST(common_5)  // set_sign минус с наличием экспоненты
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS_AND_EXPONENT_1};
  int result = s21_set_sign(&a, 0);
  ck_assert_int_eq(result, 0);  // проверка на успех функции
  ck_assert_int_eq(0, s21_get_sign(a));
}
END_TEST

START_TEST(common_6)  // set_sign плюс с наличием экспоненты
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, EXPONENT_1};
  int result = s21_set_sign(&a, 1);
  ck_assert_int_eq(result, 0);  // проверка на успех функции
  ck_assert_int_eq(1, s21_get_sign(a));
}
END_TEST

START_TEST(common_7)  // get_sign_long плюс
{
  s21_decimal_long a = {100, 0, 0, 0, 0, 0, 0, 0};
  ck_assert_int_eq(0, s21_get_sign_long(a));
}
END_TEST

START_TEST(common_8)  // get_sign_long плюс с наличием экспоненты
{
  s21_decimal_long a = {100, 0, 0, 0, 0, 0, 0, EXPONENT_1};
  ck_assert_int_eq(0, s21_get_sign_long(a));
}
END_TEST

START_TEST(common_9)  // get_sign_long минус
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  ck_assert_int_eq(1, s21_get_sign_long(a));
}
END_TEST

START_TEST(common_10)  // get_sign_long минус с наличием экспоненты
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, MINUS_AND_EXPONENT_1};
  ck_assert_int_eq(1, s21_get_sign_long(a));
}
END_TEST

START_TEST(common_11)  // set_sign_long минус с наличием экспоненты
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, MINUS_AND_EXPONENT_1};
  int result = s21_set_sign_long(&a, 0);
  ck_assert_int_eq(0, s21_get_sign_long(a));
  ck_assert_int_eq(result, 0);  // проверка на успех функции
}
END_TEST

START_TEST(common_12)  // set_sign плюс с наличием экспоненты
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, EXPONENT_1};
  int result = s21_set_sign_long(&a, 1);
  ck_assert_int_eq(1, s21_get_sign_long(a));
  ck_assert_int_eq(result, 0);  // проверка на успех функции
}
END_TEST

START_TEST(common_13)  // get_exponent знак плюс, экспонента 0
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  int actual = s21_get_exponent(a);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_14)  // get_exponent знак минус, экспонента 0
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  int actual = s21_get_exponent(a);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_15)  // get_exponent знак минус, экспонента 1
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS_AND_EXPONENT_1};
  int actual = s21_get_exponent(a);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_16)  // get_exponent знак плюс, экспонента 1
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, EXPONENT_1};
  int actual = s21_get_exponent(a);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_17)  // get_exponent знак плюс, экспонента 28
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_EXPONENT};
  int actual = s21_get_exponent(a);
  int expected = 28;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_18)  // get_exponent знак плюс, экспонента 29
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, TOO_MUCH_EXPONENT};
  int actual = s21_get_exponent(a);
  int expected = 29;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_19)  // get_exponent знак минус, экспонента 28
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS_AND_MAX_EXPONENT};
  int actual = s21_get_exponent(a);
  int expected = 28;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_20)  // set_exponent знак плюс, экспонента 1
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  int result = s21_set_exponent(&a, 1);
  int actual = s21_get_exponent(a);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
  ck_assert_int_eq(result, 0);  // проверка на успех функции
}
END_TEST

START_TEST(common_21)  // set_exponent знак плюс, экспонента 28
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  int result = s21_set_exponent(&a, 28);
  int actual = s21_get_exponent(a);
  int expected = 28;
  ck_assert_int_eq(actual, expected);
  ck_assert_int_eq(result, 0);  // проверка на успех функции
}
END_TEST

START_TEST(common_22)  // set_exponent знак плюс, экспонента 29
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, 0};
  int result = s21_set_exponent(&a, 29);
  ck_assert_int_eq(result, 1);  // проверка на успех функции
}
END_TEST

START_TEST(common_23)  // set_exponent знак минус, экспонента 28
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  int result = s21_set_exponent(&a, 28);
  int actual = s21_get_exponent(a);
  int expected = 28;
  int sign = s21_get_sign(a);
  ck_assert_int_eq(actual, expected);
  ck_assert_int_eq(result, 0);  // проверка на успех функции
  ck_assert_int_eq(sign, 1);  // проверка, что знак остался
}
END_TEST

START_TEST(common_24)  // set_exponent знак минус, экспонента 1
{
  s21_decimal a = {MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  int result = s21_set_exponent(&a, 1);
  int actual = s21_get_exponent(a);
  int expected = 1;
  int sign = s21_get_sign(a);
  ck_assert_int_eq(actual, expected);
  ck_assert_int_eq(result, 0);  // проверка на успех функции
  ck_assert_int_eq(sign, 1);  // проверка, что знак остался
}
END_TEST

START_TEST(common_25)  // get_exponent_long знак плюс, экспонента 0
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, 0};
  int actual = s21_get_exponent_long(a);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_26)  // get_exponent_long знак минус, экспонента 0
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  int actual = s21_get_exponent_long(a);
  int expected = 0;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_27)  // get_exponent_long знак минус, экспонента 1
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, MINUS_AND_EXPONENT_1};
  int actual = s21_get_exponent_long(a);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_28)  // get_exponent_long знак плюс, экспонента 1
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, EXPONENT_1};
  int actual = s21_get_exponent_long(a);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_29)  // get_exponent_long знак плюс, экспонента 28
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, MAX_EXPONENT};
  int actual = s21_get_exponent_long(a);
  int expected = 28;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_30)  // get_exponent_long знак плюс, экспонента 29
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, TOO_MUCH_EXPONENT};
  int actual = s21_get_exponent_long(a);
  int expected = 29;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_31)  // get_exponent_long знак минус, экспонента 28
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, MINUS_AND_MAX_EXPONENT};
  int actual = s21_get_exponent_long(a);
  int expected = 28;
  ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(common_32)  // set_exponent_long знак плюс, экспонента 1
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, 0};
  int result = s21_set_exponent_long(&a, 1);
  int actual = s21_get_exponent_long(a);
  int expected = 1;
  ck_assert_int_eq(actual, expected);
  ck_assert_int_eq(result, 0);  // проверка на успех функции
}
END_TEST

START_TEST(common_33)  // set_exponent_long знак плюс, экспонента 28
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, 0};
  int result = s21_set_exponent_long(&a, 28);
  int actual = s21_get_exponent_long(a);
  int expected = 28;
  ck_assert_int_eq(actual, expected);
  ck_assert_int_eq(result, 0);  // проверка на успех функции
}
END_TEST

START_TEST(common_34)  // set_exponent_long знак плюс, экспонента 29
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, 0};
  int result = s21_set_exponent_long(&a, 29);
  int actual = s21_get_exponent_long(a);
  int expected = 29;
  ck_assert_int_eq(actual, expected);
  ck_assert_int_eq(result, 0);  // проверка на успех функции
}
END_TEST

START_TEST(common_35)  // set_exponent_long знак минус, экспонента 28
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  int result = s21_set_exponent_long(&a, 28);
  int actual = s21_get_exponent_long(a);
  int expected = 28;
  int sign = s21_get_sign_long(a);
  ck_assert_int_eq(actual, expected);
  ck_assert_int_eq(result, 0);  // проверка на успех функции
  ck_assert_int_eq(sign, 1);  // проверка, что знак остался
}
END_TEST

START_TEST(common_36)  // set_exponent_long знак минус, экспонента 1
{
  s21_decimal_long a = {MAX_UINT, MAX_UINT, MAX_UINT, MAX_UINT,
                        MAX_UINT, MAX_UINT, MAX_UINT, MINUS};
  int result = s21_set_exponent_long(&a, 1);
  int actual = s21_get_exponent_long(a);
  int expected = 1;
  int sign = s21_get_sign_long(a);
  ck_assert_int_eq(actual, expected);
  ck_assert_int_eq(result, 0);  // проверка на успех функции
  ck_assert_int_eq(sign, 1);  // проверка, что знак остался
}
END_TEST

START_TEST(common_37)  // init_zero
{
  s21_decimal actual = {1, 1, 1, 1};
  s21_decimal expected = {0};
  s21_init_zero(&actual);
  ck_assert_int_eq(1, s21_is_equal(actual, expected));
}
END_TEST

START_TEST(common_38)  // init_zero_long
{
  s21_decimal_long actual = {1, 1, 1, 1, 1, 1, 1, 1};
  s21_decimal_long expected = {0};
  s21_init_zero_long(&actual);
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
  ck_assert_int_eq(actual.bits[4], expected.bits[4]);
  ck_assert_int_eq(actual.bits[5], expected.bits[5]);
  ck_assert_int_eq(actual.bits[6], expected.bits[6]);
  ck_assert_int_eq(actual.bits[7], expected.bits[7]);
}
END_TEST

START_TEST(common_39)  // s21_is_zero
{
  s21_decimal actual = {1, 1, 1, 1};
  s21_decimal expected = {0};
  s21_init_zero(&actual);
  ck_assert_int_eq(1, s21_is_equal(actual, expected));
  ck_assert_int_eq(1, s21_is_zero(actual));
}
END_TEST

START_TEST(common_40)  // s21_is_zero_long
{
  s21_decimal_long actual = {1, 1, 1, 1, 1, 1, 1, 1};
  s21_decimal_long expected = {0};
  s21_init_zero_long(&actual);
  // сравнение децималов
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
  ck_assert_int_eq(actual.bits[4], expected.bits[4]);
  ck_assert_int_eq(actual.bits[5], expected.bits[5]);
  ck_assert_int_eq(actual.bits[6], expected.bits[6]);
  ck_assert_int_eq(actual.bits[7], expected.bits[7]);
  ck_assert_int_eq(1, s21_is_zero_long(actual));
}
END_TEST

START_TEST(common_41)  // s21_init_inf / s21_is_inf
{
  s21_decimal actual;
  s21_init_inf(&actual);
  ck_assert_int_eq(1, s21_is_inf(actual));
}
END_TEST

START_TEST(common_42)  // s21_init_inf / s21_is_inf
{
  s21_decimal actual = {1, 1, 1, 0};
  s21_init_inf(&actual);
  ck_assert_int_eq(1, s21_is_inf(actual));
}
END_TEST

START_TEST(common_43)  // s21_init_inf / s21_is_inf
{
  s21_decimal actual = {1, 1, 1, 1};
  s21_init_inf(&actual);
  ck_assert_int_eq(1, s21_is_inf(actual));
}
END_TEST

START_TEST(common_44)  // s21_init_nan / s21_is_nan
{
  s21_decimal actual;
  s21_init_nan(&actual);
  ck_assert_int_eq(1, s21_is_nan(actual));
}
END_TEST

START_TEST(common_45)  // s21_init_nan / s21_is_nan
{
  s21_decimal actual = {1, 1, 1, 0};
  s21_init_nan(&actual);
  ck_assert_int_eq(1, s21_is_nan(actual));
}
END_TEST

START_TEST(common_46)  // s21_init_nan / s21_is_nan
{
  s21_decimal actual = {1, 1, 1, 1};
  s21_init_nan(&actual);
  ck_assert_int_eq(1, s21_is_nan(actual));
}
END_TEST

START_TEST(common_47)  // s21_init_inf_long / s21_is_inf_long
{
  s21_decimal_long actual;
  s21_init_inf_long(&actual);
  ck_assert_int_eq(1, s21_is_inf_long(actual));
}
END_TEST

START_TEST(common_48)  // s21_init_inf_long / s21_is_inf_long
{
  s21_decimal_long actual = {1, 1, 1, 1, 1, 1, 1, 0};
  s21_init_inf_long(&actual);
  ck_assert_int_eq(1, s21_is_inf_long(actual));
}
END_TEST

START_TEST(common_49)  // s21_init_inf_long / s21_is_inf_long
{
  s21_decimal_long actual = {1, 1, 1, 1, 1, 1, 1, 1};
  s21_init_inf_long(&actual);
  ck_assert_int_eq(1, s21_is_inf_long(actual));
}
END_TEST

START_TEST(common_50)  // s21_init_nan_long / s21_is_nan_long
{
  s21_decimal_long actual;
  s21_init_nan_long(&actual);
  ck_assert_int_eq(1, s21_is_nan_long(actual));
}
END_TEST

START_TEST(common_51)  // s21_init_nan_long / s21_is_nan_long
{
  s21_decimal_long actual = {1, 1, 1, 1, 1, 1, 1, 0};
  s21_init_nan_long(&actual);
  ck_assert_int_eq(1, s21_is_nan_long(actual));
}
END_TEST

START_TEST(common_52)  // s21_init_nan_long / s21_is_nan_long
{
  s21_decimal_long actual = {1, 1, 1, 1, 1, 1, 1, MINUS};
  s21_init_nan_long(&actual);
  ck_assert_int_eq(1, s21_is_nan_long(actual));
}
END_TEST

START_TEST(common_53)  // s21_is_decimal_long
{
  s21_decimal_long actual = {1, 1, 1, 1, 1, 1, 1, MINUS};
  int result = s21_is_decimal_long(actual);
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(common_54)  // s21_is_decimal_long
{
  s21_decimal_long actual = {0};
  int result = s21_is_decimal_long(actual);
  ck_assert_int_eq(1, result);
}
END_TEST

START_TEST(common_55)  // s21_abs
{
  s21_decimal dec1 = {1, 1, 1, MINUS};
  s21_decimal actual = s21_abs(dec1);
  s21_decimal expected = {1, 1, 1, 0};
  ck_assert_int_eq(1, s21_is_equal(actual, expected));
}
END_TEST

START_TEST(common_56)  // s21_abs
{
  s21_decimal dec1 = {0, 0, 1, MINUS};
  s21_decimal actual = s21_abs(dec1);
  s21_decimal expected = {0, 0, 1, 0};
  ck_assert_int_eq(1, s21_is_equal(actual, expected));
}
END_TEST

START_TEST(common_57)  // s21_abs
{
  s21_decimal dec1 = {0, 0, 1, MINUS_AND_MAX_EXPONENT};
  s21_decimal actual = s21_abs(dec1);
  s21_decimal expected = {0, 0, 1, MAX_EXPONENT};
  ck_assert_int_eq(1, s21_is_equal(actual, expected));
}
END_TEST

START_TEST(common_58)  // s21_abs
{
  s21_decimal dec1 = {0, 0, 1, MAX_EXPONENT};
  s21_decimal actual = s21_abs(dec1);
  s21_decimal expected = {0, 0, 1, MAX_EXPONENT};
  ck_assert_int_eq(1, s21_is_equal(actual, expected));
}
END_TEST

START_TEST(common_59)  // s21_abs_long
{
  s21_decimal_long dec1 = {1, 1, 1, 1, 1, 1, 1, MINUS};
  s21_decimal_long actual = s21_abs_long(dec1);
  s21_decimal_long expected = {1, 1, 1, 1, 1, 1, 1, 0};
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
  ck_assert_int_eq(actual.bits[4], expected.bits[4]);
  ck_assert_int_eq(actual.bits[5], expected.bits[5]);
  ck_assert_int_eq(actual.bits[6], expected.bits[6]);
  ck_assert_int_eq(actual.bits[7], expected.bits[7]);
}
END_TEST

START_TEST(common_60)  // s21_abs
{
  s21_decimal_long dec1 = {0, 0, 0, 1, 1, 1, 1, MINUS};
  s21_decimal_long actual = s21_abs_long(dec1);
  s21_decimal_long expected = {0, 0, 0, 1, 1, 1, 1, 0};
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
  ck_assert_int_eq(actual.bits[4], expected.bits[4]);
  ck_assert_int_eq(actual.bits[5], expected.bits[5]);
  ck_assert_int_eq(actual.bits[6], expected.bits[6]);
  ck_assert_int_eq(actual.bits[7], expected.bits[7]);
}
END_TEST

START_TEST(common_61)  // s21_abs
{
  s21_decimal_long dec1 = {1, 1, 1, 1, 1, 1, 1, MINUS_AND_MAX_EXPONENT};
  s21_decimal_long actual = s21_abs_long(dec1);
  s21_decimal_long expected = {1, 1, 1, 1, 1, 1, 1, MAX_EXPONENT};
  ck_assert_int_eq(actual.bits[0], expected.bits[0]);
  ck_assert_int_eq(actual.bits[1], expected.bits[1]);
  ck_assert_int_eq(actual.bits[2], expected.bits[2]);
  ck_assert_int_eq(actual.bits[3], expected.bits[3]);
  ck_assert_int_eq(actual.bits[4], expected.bits[4]);
  ck_assert_int_eq(actual.bits[5], expected.bits[5]);
  ck_assert_int_eq(actual.bits[6], expected.bits[6]);
  ck_assert_int_eq(actual.bits[7], expected.bits[7]);
}
END_TEST

Suite *suite_s21_bit_operations(void) {
  Suite *s1 = suite_create("s21_bit_operations");
  TCase *tc1_1 = tcase_create("get_sign");
  TCase *tc1_2 = tcase_create("set_sign");
  TCase *tc1_3 = tcase_create("get_sign_long");
  TCase *tc1_4 = tcase_create("set_sign_long");
  TCase *tc2_1 = tcase_create("get_exponent");
  TCase *tc2_2 = tcase_create("set_exponent");
  TCase *tc2_3 = tcase_create("get_exponent_long");
  TCase *tc2_4 = tcase_create("set_exponent_long");
  TCase *tc3_1 = tcase_create("init_zero");
  TCase *tc3_2 = tcase_create("is_zero");
  TCase *tc4_1 = tcase_create("is_inf / init_inf");
  TCase *tc4_2 = tcase_create("is_nan / init_nan");
  TCase *tc4_3 = tcase_create("is_inf_long / init_inf_long");
  TCase *tc4_4 = tcase_create("is_nan_long / init_nan_long");
  TCase *tc4_5 = tcase_create("is_decimal_long");
  TCase *tc4_6 = tcase_create("s21_abs");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);  // get_sign
  tcase_add_test(tc1_1, common_1);
  tcase_add_test(tc1_1, common_2);
  tcase_add_test(tc1_1, common_3);
  tcase_add_test(tc1_1, common_4);
  suite_add_tcase(s1, tc1_2);  // set_sign
  tcase_add_test(tc1_2, common_5);
  tcase_add_test(tc1_2, common_6);
  suite_add_tcase(s1, tc1_3);  // get_sign_long
  tcase_add_test(tc1_3, common_7);
  tcase_add_test(tc1_3, common_8);
  tcase_add_test(tc1_3, common_9);
  tcase_add_test(tc1_3, common_10);
  suite_add_tcase(s1, tc1_4);  // set_sign_long
  tcase_add_test(tc1_4, common_11);
  tcase_add_test(tc1_4, common_12);
  suite_add_tcase(s1, tc2_1);  // get_exponent
  tcase_add_test(tc2_1, common_13);
  tcase_add_test(tc2_1, common_14);
  tcase_add_test(tc2_1, common_15);
  tcase_add_test(tc2_1, common_16);
  tcase_add_test(tc2_1, common_17);
  tcase_add_test(tc2_1, common_18);
  tcase_add_test(tc2_1, common_19);
  suite_add_tcase(s1, tc2_2);  // set_exponent
  tcase_add_test(tc2_2, common_20);
  tcase_add_test(tc2_2, common_21);
  tcase_add_test(tc2_2, common_22);
  tcase_add_test(tc2_2, common_23);
  suite_add_tcase(s1, tc2_3);  // get_exponent_long
  tcase_add_test(tc2_3, common_24);
  tcase_add_test(tc2_3, common_25);
  tcase_add_test(tc2_3, common_26);
  tcase_add_test(tc2_3, common_27);
  tcase_add_test(tc2_3, common_28);
  tcase_add_test(tc2_3, common_29);
  tcase_add_test(tc2_3, common_30);
  suite_add_tcase(s1, tc2_4);  // set_exponent_long
  tcase_add_test(tc2_4, common_31);
  tcase_add_test(tc2_4, common_32);
  tcase_add_test(tc2_4, common_33);
  tcase_add_test(tc2_4, common_34);
  tcase_add_test(tc2_4, common_35);
  tcase_add_test(tc2_4, common_36);
  suite_add_tcase(s1, tc3_1);  // init zero
  tcase_add_test(tc3_1, common_37);
  tcase_add_test(tc3_1, common_38);
  suite_add_tcase(s1, tc3_2);  // is zero
  tcase_add_test(tc3_2, common_39);
  tcase_add_test(tc3_2, common_40);
  suite_add_tcase(s1, tc4_1);  // is inf
  tcase_add_test(tc4_1, common_41);
  tcase_add_test(tc4_1, common_42);
  tcase_add_test(tc4_1, common_43);
  suite_add_tcase(s1, tc4_2);  // is nan
  tcase_add_test(tc4_2, common_44);
  tcase_add_test(tc4_2, common_45);
  tcase_add_test(tc4_2, common_46);
  suite_add_tcase(s1, tc4_3);  // is inf_long
  tcase_add_test(tc4_3, common_47);
  tcase_add_test(tc4_3, common_48);
  tcase_add_test(tc4_3, common_49);
  suite_add_tcase(s1, tc4_4);  // is nan_long
  tcase_add_test(tc4_4, common_50);
  tcase_add_test(tc4_4, common_51);
  tcase_add_test(tc4_4, common_52);
  suite_add_tcase(s1, tc4_5);  // is_decimal_long
  tcase_add_test(tc4_5, common_53);
  tcase_add_test(tc4_5, common_54);
  suite_add_tcase(s1, tc4_6);  // s21_abs
  tcase_add_test(tc4_6, common_55);
  tcase_add_test(tc4_6, common_56);
  tcase_add_test(tc4_6, common_57);
  tcase_add_test(tc4_6, common_58);
  tcase_add_test(tc4_6, common_59);
  tcase_add_test(tc4_6, common_60);
  tcase_add_test(tc4_6, common_61);

  return s1;
}
