#include "../s21_spec_foo.h"

s21_big_decimal add_mantissas(s21_big_decimal val1, s21_big_decimal val2) {
  unsigned long long carry = 0;
  s21_big_decimal res = {{0}};

  for (int i = 0; i < 7; i++) {
    unsigned long long temp_sum = (unsigned long long)val1.bit.mantissa[i] +
                                  (unsigned long long)val2.bit.mantissa[i] +
                                  carry;

    res.bit.mantissa[i] = (unsigned int)(temp_sum & 0xFFFFFFFF);
    carry = temp_sum >> 32;
  }
  return res;
}

s21_big_decimal subtract_mantissas(s21_big_decimal val1, s21_big_decimal val2) {
  long long borrow = 0;
  s21_big_decimal res = {{0}};
  for (int i = 0; i < 7; i++) {
    long long diff = (long long)val1.bit.mantissa[i] -
                     (long long)val2.bit.mantissa[i] - borrow;

    if (diff < 0) {
      diff += ((long long)1 << 32);
      borrow = 1;
    } else {
      borrow = 0;
    }

    res.bit.mantissa[i] = (unsigned int)(diff & 0xFFFFFFFF);
  }
  return res;
}

__uint64_t s21_muldev_int(s21_big_decimal *big_dcml, int operation, int operand,
                          int iterations) {
  __uint64_t tmp = 0, rem = 0;
  while (iterations) {
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
    iterations--;
  }
  return rem;
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

void s21_big_plus_1(s21_big_decimal *val) {
  int flag = 1;
  for (int i = 0; i < 7 && flag; i++) {
    if (val->bits[i] == __UINT32_MAX__)
      val->bits[i] = 0;
    else
      val->bits[i] += 1, flag = 0;
  }
}

void s21_plus_1(s21_decimal *val) {
  int flag = 1;
  for (int i = 0; i < 3 && flag; i++) {
    if (val->bits[i] == __UINT32_MAX__)
      val->bits[i] = 0;
    else
      val->bits[i] += 1, flag = 0;
  }
}
