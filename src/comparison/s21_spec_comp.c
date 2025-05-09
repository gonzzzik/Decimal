#include "../s21_spec_foo.h"

int s21_big_is_equal(s21_big_decimal val1, s21_big_decimal val2) {
  int res = 1;
  for (int i = 0; i < 7 && res != 0; i++) {
    if (val1.bit.mantissa[i] != val2.bit.mantissa[i])
      res = 0;
  }
  return res;
}

int s21_big_is_greater(s21_big_decimal val1, s21_big_decimal val2) {
  int flag = 0, res = 0;

  for (int i = 6; i >= 0 && !flag; i--) {
    if (val1.bit.mantissa[i] != val2.bit.mantissa[i]) {
      res = (val1.bit.sign) ? (val1.bit.mantissa[i] < val2.bit.mantissa[i])
                            : (val1.bit.mantissa[i] > val2.bit.mantissa[i]);
      flag = 1;
    }
  }

  return res;
}