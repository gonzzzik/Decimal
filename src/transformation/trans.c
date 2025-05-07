#include "../s21_decimal.h"
#include "../s21_spec_foo.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_dcml_init(dst);

  if (src < 0) {
    dst->bit.sign = 1;
    src = ~src;
  }
  dst->bits[0] = src;

  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (s21_truncate(src, &src) || src.bits[1] || src.bits[2] ||
      src.bits[0] > __INT32_MAX__) {
    *dst = 0;
    return 1;
  }

  *dst = src.bits[0];
  if (src.bit.sign) *dst = -(*dst);

  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) { return 0; }

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (s21_can_I_do_it(src)) {
    return 1;
  }
  *dst = 0;

  int scale = src.bit.exp;

  __uint32_t low = src.bit.mantissa[0];
  __uint32_t mid = src.bit.mantissa[1];
  __uint32_t high = src.bit.mantissa[2];

  float value =
      (float)high * pow(2.0, 64) + (float)mid * pow(2.0, 32) + (float)low;
  value = value / pow(10, scale);

  if (src.bit.sign) {
    value = -value;
  }

  *dst = (float)value;

  return 0;
}
