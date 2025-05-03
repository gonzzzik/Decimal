#include "tests.h"

START_TEST(dcml_mul_0) {  // базовый тест на 1 блок (усмножение интов)
  s21_decimal expected = {
      .bit.sign = 1, .bit.exp = 10, .bit.mantissa = {0, 0, 3855}};
  s21_decimal val1 = {.bit.sign = 0, .bit.exp = 8, .bit.mantissa = {0, 0, 15}};
  s21_decimal val2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {0, 0, 257}};
  s21_decimal result;
  int err = s21_mul(val1, val2, &result);

  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(expected.bits[i], result.bits[i]);
}
END_TEST

/* START_TEST(dcml_mul_1){  //тест на 3 блока
    s21_decimal expected = {.bit.sign = 1, .bit.exp = 10, .bit.mantissa = {0, 0,
3855}}; s21_decimal val1 = {.bit.sign = 0, .bit.exp = 8, .bit.mantissa = {0, 0,
15}}; s21_decimal val2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {0, 0,
257}}; s21_decimal result; int err = s21_mul(val1, val2, &result);

    for (int i = 0; i < 4; i++) ck_assert_int_eq(expected.num[i],
result.num[i]);
}
END_TEST */

/* START_TEST(dcml_mul_2){  //с отрицательной эксп
    s21_decimal expected = {.bit.sign = 1, .bit.exp = 10, .bit.mantissa = {0, 0,
3855}}; s21_decimal val1 = {.bit.sign = 0, .bit.exp = 8, .bit.mantissa = {0, 0,
15}}; s21_decimal val2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {0, 0,
257}}; s21_decimal result; int err = s21_mul(val1, val2, &result);

    for (int i = 0; i < 4; i++) ck_assert_int_eq(expected.num[i],
result.num[i]);
}
END_TEST */

/* START_TEST(dcml_mul_3){  //с большой эксп
    s21_decimal expected = {.bit.sign = 1, .bit.exp = 10, .bit.mantissa = {0, 0,
3855}}; s21_decimal val1 = {.bit.sign = 0, .bit.exp = 8, .bit.mantissa = {0, 0,
15}}; s21_decimal val2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {0, 0,
257}}; s21_decimal result; int err = s21_mul(val1, val2, &result);

    for (int i = 0; i < 4; i++) ck_assert_int_eq(expected.num[i],
result.num[i]);
}
END_TEST */

/* START_TEST(dcml_mul_4){  //с малой эксп
    s21_decimal expected = {.bit.sign = 1, .bit.exp = 10, .bit.mantissa = {0, 0,
3855}}; s21_decimal val1 = {.bit.sign = 0, .bit.exp = 8, .bit.mantissa = {0, 0,
15}}; s21_decimal val2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {0, 0,
257}}; s21_decimal result; int err = s21_mul(val1, val2, &result);

    for (int i = 0; i < 4; i++) ck_assert_int_eq(expected.num[i],
result.num[i]);
}
END_TEST */

/* START_TEST(dcml_mul_max_mant){
    s21_decimal expected = {.bit.sign = 1, .bit.exp = 10, .bit.mantissa = {0, 0,
3855}}; s21_decimal val1 = {.bit.sign = 0, .bit.exp = 8, .bit.mantissa = {0, 0,
15}}; s21_decimal val2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {0, 0,
257}}; s21_decimal result; int err = s21_mul(val1, val2, &result);

    for (int i = 0; i < 4; i++) ck_assert_int_eq(expected.num[i],
result.num[i]);
}
END_TEST */

/* START_TEST(dcml_mul_max_exp){
    s21_decimal expected = {.bit.sign = 1, .bit.exp = 10, .bit.mantissa = {0, 0,
3855}}; s21_decimal val1 = {.bit.sign = 0, .bit.exp = 8, .bit.mantissa = {0, 0,
15}}; s21_decimal val2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {0, 0,
257}}; s21_decimal result; int err = s21_mul(val1, val2, &result);

    for (int i = 0; i < 4; i++) ck_assert_int_eq(expected.num[i],
result.num[i]);
}
END_TEST */

/* START_TEST(dcml_mul_double_max){
    s21_decimal expected = {.bit.sign = 1, .bit.exp = 10, .bit.mantissa = {0, 0,
3855}}; s21_decimal val1 = {.bit.sign = 0, .bit.exp = 8, .bit.mantissa = {0, 0,
15}}; s21_decimal val2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {0, 0,
257}}; s21_decimal result; int err = s21_mul(val1, val2, &result);

    for (int i = 0; i < 4; i++) ck_assert_int_eq(expected.num[i],
result.num[i]);
}
END_TEST */

/* START_TEST(dcml_mul_max_res){
    s21_decimal expected = {.bit.sign = 1, .bit.exp = 10, .bit.mantissa = {0, 0,
3855}}; s21_decimal val1 = {.bit.sign = 0, .bit.exp = 8, .bit.mantissa = {0, 0,
15}}; s21_decimal val2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {0, 0,
257}}; s21_decimal result; int err = s21_mul(val1, val2, &result);

    for (int i = 0; i < 4; i++) ck_assert_int_eq(expected.num[i],
result.num[i]);
}
END_TEST */

/* START_TEST(dcml_mul_min_mant){
    s21_decimal expected = {.bit.sign = 1, .bit.exp = 10, .bit.mantissa = {0, 0,
3855}}; s21_decimal val1 = {.bit.sign = 0, .bit.exp = 8, .bit.mantissa = {0, 0,
15}}; s21_decimal val2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {0, 0,
257}}; s21_decimal result; int err = s21_mul(val1, val2, &result);

    for (int i = 0; i < 4; i++) ck_assert_int_eq(expected.num[i],
result.num[i]);
}
END_TEST */

/* START_TEST(dcml_mul_min_exp){
    s21_decimal expected = {.bit.sign = 1, .bit.exp = 10, .bit.mantissa = {0, 0,
3855}}; s21_decimal val1 = {.bit.sign = 0, .bit.exp = 8, .bit.mantissa = {0, 0,
15}}; s21_decimal val2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {0, 0,
257}}; s21_decimal result; int err = s21_mul(val1, val2, &result);

    for (int i = 0; i < 4; i++) ck_assert_int_eq(expected.num[i],
result.num[i]);
}
END_TEST */

/* START_TEST(dcml_mul_double_min){
    s21_decimal expected = {.bit.sign = 1, .bit.exp = 10, .bit.mantissa = {0, 0,
3855}}; s21_decimal val1 = {.bit.sign = 0, .bit.exp = 8, .bit.mantissa = {0, 0,
15}}; s21_decimal val2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {0, 0,
257}}; s21_decimal result; int err = s21_mul(val1, val2, &result);

    for (int i = 0; i < 4; i++) ck_assert_int_eq(expected.num[i],
result.num[i]);
}
END_TEST */

/* START_TEST(dcml_mul_min_res){
    s21_decimal expected = {.bit.sign = 1, .bit.exp = 10, .bit.mantissa = {0, 0,
3855}}; s21_decimal val1 = {.bit.sign = 0, .bit.exp = 8, .bit.mantissa = {0, 0,
15}}; s21_decimal val2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {0, 0,
257}}; s21_decimal result; int err = s21_mul(val1, val2, &result);

    for (int i = 0; i < 4; i++) ck_assert_int_eq(expected.num[i],
result.num[i]);
}
END_TEST */
