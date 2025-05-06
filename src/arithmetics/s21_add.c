#include "../s21_decimal.h"
#include "../s21_spec_foo.c"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_big_decimal val1 = {{0}}, val2 = {{0}}, res = {{0}};
  normalize(value_1, value_2, &val1, &val2);

  int sign1 = val1.bit.sign;
  int sign2 = val2.bit.sign;
  value_1.bit.sign = value_2.bit.sign = 0;

  if (sign1 == sign2) {
    res = add_mantissas(val1, val2);
    res.bit.sign = sign1;
  } else if (s21_is_greater(value_1, value_2)) {
    res = subtract_mantissas(val1, val2);
    res.bit.sign = sign1;
  } else {
    res = subtract_mantissas(val2, val1);
    res.bit.sign = sign2;
  }

  res.bit.exp = value_1.bit.exp;

  return big_to_dcml(res, result);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_big_decimal val1 = {{0}}, val2 = {{0}}, res = {{0}};
  normalize(value_1, value_2, &val1, &val2);

  int sign1 = val1.bit.sign;
  int sign2 = val2.bit.sign;
  value_1.bit.sign = value_2.bit.sign = 0;

  if (sign1 != sign2) {
    res = add_mantissas(val1, val2);
    res.bit.sign = sign1;
  } else if (s21_is_greater(value_1, value_2)) {
    res = subtract_mantissas(val1, val2);
    res.bit.sign = sign1;
  } else {
    res = subtract_mantissas(val2, val1);
    res.bit.sign = sign2;
  }

  res.bit.exp = value_1.bit.exp;

  return big_to_dcml(res, result);
}