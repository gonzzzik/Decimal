#include "../s21_decimal.h"
#include "../s21_spec_foo.c"

void decimal_summ(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  align_exponents(&value_1, &value_2);
  decimal_summ(value_1, value_2, result);
  return 0;
}

void decimal_summ(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result) {
  int sign1 = value_1.bit.sign;
  int sign2 = value_2.bit.sign;

  for (int i = 0; i < 3; i++) {
    result->bit.mantissa[i] = 0;
  }

  if (sign1 == sign2) {
    add_mantissas(value_1, value_2, result);
    result->bit.sign = sign1;
  } else if (sign1 > sign2) {
    subtract_mantissas(value_1, value_2, result);
    result->bit.sign = sign1;
  } else {
    subtract_mantissas(value_2, value_1, result);
    result->bit.sign = sign2;
  }

  result->bit.exp = value_1.bit.exp;
}

void add_mantissas(s21_decimal val1, s21_decimal val2,
                   s21_decimal *res) {  // функция сложения мантисс
  unsigned long long carry = 0;

  for (int i = 0; i < 3; i++) {
    unsigned long long temp_sum = (unsigned long long)val1.bit.mantissa[i] +
                                  (unsigned long long)val2.bit.mantissa[i] +
                                  carry;

    res->bit.mantissa[i] = (unsigned int)(temp_sum & 0xFFFFFFFF);
    carry = temp_sum >> 32;
  }
}

void subtract_mantissas(s21_decimal val1, s21_decimal val2,
                        s21_decimal *res) {  // функция вычитания мантисс
  long long borrow = 0;

  for (int i = 0; i < 3; i++) {
    long long diff = (long long)val1.bit.mantissa[i] -
                     (long long)val2.bit.mantissa[i] - borrow;

    if (diff < 0) {
      diff += ((long long)1 << 32);
      borrow = 1;
    } else {
      borrow = 0;
    }

    res->bit.mantissa[i] = (unsigned int)(diff & 0xFFFFFFFF);
  }
}