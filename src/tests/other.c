#include "tests.h"

START_TEST(dcml_neg_0) {
  s21_decimal a = {.bit.sign = 0, .bit.exp = 15, .bit.mantissa = {0, 15, 35}};
  s21_decimal res;

  int err = s21_negate(a, &res);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(res.bit.sign, 1);
}
END_TEST

START_TEST(dcml_neg_1) {
  s21_decimal a = {.bit.sign = 1, .bit.exp = 15, .bit.mantissa = {0, 15, 35}};
  s21_decimal res;

  int err = s21_negate(a, &res);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(res.bit.sign, 0);
}
END_TEST

START_TEST(dcml_neg_err_0) {
  s21_decimal a = {.bit.sign = 0,
                   .bit.oversize = 1,
                   .bit.exp = 15,
                   .bit.mantissa = {0, 15, 35}};
  s21_decimal res;

  int err = s21_negate(a, &res);

  ck_assert_int_eq(err, 1);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(res.bits[i], 0);
}
END_TEST

START_TEST(dcml_neg_err_1) {
  s21_decimal a = {.bit.sign = 0,
                   .bit.oversize = 1,
                   .bit.exp = 15,
                   .bit._void = 1,
                   .bit.mantissa = {0, 15, 35}};
  s21_decimal res;

  int err = s21_negate(a, &res);

  ck_assert_int_eq(err, 1);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(res.bits[i], 0);
}
END_TEST

START_TEST(dcml_neg_err_2) {
  s21_decimal a = {.bit.sign = 0,
                   .bit.exp = 15,
                   .bit._void = 1,
                   .bit.mantissa = {0, 15, 35}};
  s21_decimal res;

  int err = s21_negate(a, &res);

  ck_assert_int_eq(err, 1);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(res.bits[i], 0);
}
END_TEST