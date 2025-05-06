#include "./s21_spec_foo.h"

static int s21_can_I_do_it(s21_decimal value) {
  return (value.bit.oversize || value.bit._void || value.bit.exp > 28) ? 1 : 0;
}

static void s21_dcml_init(s21_decimal *value) {
  for (int i = 0; i < 4; i++) value->bits[i] = 0;
}

static void s21_plus_1(s21_decimal *val) {
  int flag = 1;
  for (int i = 0; i < 3 && flag; i++) {
    if (val->bits[i] == __UINT32_MAX__)
      val->bits[i] = 0;
    else
      val->bits[i] += 1, flag = 0;
  }
}

static void s21_muldev_int(s21_big_decimal *big_dcml, int operation,
                           int operand, int count) {
  unsigned long tmp = 0, rem = 0;
  while (count) {
    if (operation) {
      for (int i = 6; i >= 0; i--) {
        tmp = big_dcml->bits[i];
        big_dcml->bits[i] = tmp * operand;
      }
    } else {
      for (int i = 6; i >= 0; i--) {
        tmp = (rem << 32) | big_dcml->bits[i];
        rem = tmp % operand;
        big_dcml->bits[i] = tmp / operand;
      }
    }
    count--;
  }
}

__uint64_t dev_int(s21_decimal *value, int del) {
  __uint64_t rem = 0, tmp = 0;
  for (int i = 2; i >= 0; i--) {
    tmp = (rem << 32) | value->bits[i];
    rem = tmp % del;
    value->bits[i] = tmp / del;
  }
  return rem;
}

static int s21_can_I_do_float(long double num) {
  return (isnan(num) || isinf(num)) ? 1 : 0;
}

static void normalize(s21_decimal dcml1, s21_decimal dcml2,
                      s21_big_decimal *big_dcml1, s21_big_decimal *big_dcml2) {
  big_dcml1->bits[7] = dcml1.bits[3];
  big_dcml2->bits[7] = dcml2.bits[3];
  for (int i = 2; i >= 0; i--) {
    big_dcml1->bits[i] = dcml1.bits[i];
    big_dcml2->bits[i] = dcml2.bits[i];
  }

  if (dcml1.bit.exp > dcml2.bit.exp)
    BIG_normalize(big_dcml1, big_dcml2);
  else if (dcml1.bit.exp < dcml2.bit.exp)
    BIG_normalize(big_dcml2, big_dcml1);
}

static void BIG_normalize(s21_big_decimal *big_dcml1,
                          s21_big_decimal *big_dcml2) {
  int delta_exp = big_dcml1->bit.exp - big_dcml2->bit.exp;
  s21_muldev_int(big_dcml2, 1, 10, delta_exp);
  big_dcml2->bit.exp -= delta_exp;
}
