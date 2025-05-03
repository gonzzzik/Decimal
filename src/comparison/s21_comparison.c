#include "../s21_decimal.h"

int s21_is_greater(
    s21_decimal value1,
    s21_decimal value2) {  // сравнение децималов с одинаковой экспонентой
  if (s21_is_equal(value1, value2)) return 0;

  int res = 0;
  int normalization = 1;

  if (normalization) {  // тут функция нормализацтии
    res = (value1.bit.sign == 0 && value2.bit.sign == 1) ? 1 : 0;

    if (value1.bit.sign == value2.bit.sign) {
      int flag = 0;

      for (int i = 2; i >= 0 && !flag; i--) {
        if (value1.bit.mantissa[i] != value2.bit.mantissa[i]) {
          res = value1.bit.sign
                    ? (value1.bit.mantissa[i] < value2.bit.mantissa[i])
                    : (value1.bit.mantissa[i] > value2.bit.mantissa[i]);
          flag = 1;
        }
      }
    }
  }

  return res;
}

int s21_is_equal(s21_decimal value1,
                 s21_decimal value2) { /* Сделать нормализацию экспоненты. */
  int res = 1;

  if ((value1.bit.sign != value2.bit.sign) ||
      (value1.bit.exp != value2.bit.exp)) { /* изучить зачем сранение
                                                 экспоненты. Возможно убрать. */
    res = 0;
  } else {
    for (int i = 0; i < 3 && res != 0; i++) {
      if (value1.bit.mantissa[i] != value2.bit.mantissa[i]) res = 0;
    }
  }

  return res;
}

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  return !s21_is_greater(value1, value2);
}

int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2) {
  return !s21_is_greater(value1, value2) || s21_is_equal(value1, value2);
}

int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2) {
  return s21_is_greater(value1, value2) || s21_is_equal(value1, value2);
}

int s21_is_not_equal(s21_decimal value1, s21_decimal value2) {
  return !s21_is_equal(value1, value2);
}