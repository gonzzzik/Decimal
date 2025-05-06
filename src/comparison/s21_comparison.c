#include <math.h>

#include "../s21_decimal.h"
#include "../s21_spec_foo.c"

int s21_is_greater(
    s21_decimal value1,
    s21_decimal value2) {  // сравнение децималов с одинаковой экспонентой
  if (s21_is_equal(value1, value2)) return 0;

  int res = 0;
  s21_big_decimal big_val1 = {{0}}, big_val2 = {{0}};

  normalize(value1, value2, &big_val1, &big_val2);
  res = (big_val1.bit.sign == 0 && big_val2.bit.sign == 1) ? 1 : 0;

  if (big_val1.bit.sign == big_val2.bit.sign) {
    int flag = 0;

    for (int i = 6; i >= 0 && !flag; i--) {
      if (big_val1.bit.mantissa[i] != big_val2.bit.mantissa[i]) {
        res = big_val1.bit.sign
                  ? (big_val1.bit.mantissa[i] < big_val2.bit.mantissa[i])
                  : (big_val1.bit.mantissa[i] > big_val2.bit.mantissa[i]);
        flag = 1;
      }
    }
  }

  return res;
}

int s21_is_equal(s21_decimal value1,
                 s21_decimal value2) { /* Сделать нормализацию экспоненты. */
  int res = 1;

  if (value1.bit.sign != value2.bit.sign) { /* изучить зачем сранение
                                                 экспоненты. Возможно убрать. */
    res = 0;
  } else {
    s21_big_decimal big_val1 = {{0}}, big_val2 = {{0}};
    normalize(value1, value2, &big_val1, &big_val2);
    for (int i = 0; i < 3 && res != 0; i++) {
      if (big_val1.bit.mantissa[i] != big_val2.bit.mantissa[i]) res = 0;
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

int digit_counter(__uint64_t num) {
  int count = 0;
  while (num > 0) num /= 10, count++;
  return count;
}

s21_big_decimal mul(s21_decimal value, int num) {
  s21_big_decimal res = {{0}};
  __uint32_t rem = 0, tmp = 0;
  for (int i = 0; i >= 0; i--) {
    __uint64_t tmp = (rem << 32) | value.bits[i];
    rem = tmp % num;
    res.bits[i] = tmp / del;
  }
}

int main() {
  s21_decimal val1 = {.bit = {.sign = 0, .exp = 0, .mantissa = {14, 14, 15}}},
              val2 = {.bit = {.sign = 0, .exp = 2, .mantissa = {1400, 14, 15}}};
  debug_print_decimal(val1);
  debug_print_decimal(val2);

  s21_big_decimal res[28] = {{{0}}};
  s21_decimal tmp_val1 = val1;
  s21_decimal tmp_val2 = val2;
  int rem = dev_int(&tmp_val2, 10);

  return 0;
}
