#include "../s21_decimal.h"
#include "../s21_spec_foo.h"

#define INT_MIN 2147483648U
#define INT_MAX 2147483647

#define MAX_FLOAT 79228162514264337593543950335.0
#define MIN_FLOAT 1e-28

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == s21_NULL)
    return 1;
  s21_dcml_init(dst);

  if (src < 0) {
    dst->bit.sign = 1;
    src = ~src + 1;
  }
  dst->bits[0] = src;

  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (s21_truncate(src, &src) || src.bits[1] || src.bits[2] ||
      src.bits[0] > ((src.bit.sign) ? INT_MIN : INT_MAX) || dst == s21_NULL) {
    if (dst != s21_NULL)
      *dst = 0;
    return 1;
  }

  *dst = src.bits[0];
  if (src.bit.sign)
    *dst = -(*dst);

  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = 0;
  if (!dst) {
    res = 1;
  } else if (isinf(src) || isnan(src)) {
    res = 1;
  } else if (fabsf(src) > MAX_FLOAT ||
             (fabsf(src) < MIN_FLOAT && fabsf(src) > 0)) {
    res = 1;
  } else {
    s21_dcml_init(dst);
    if (src < 0) {
      s21_negate(*dst, dst);
      src = -src;
    }
    int exp = 0;
    dst->bits[0] = get_meaningful_numbers_and_exp(src, &exp);
    if (exp > 0)
      remove_trailing_zeroes(&dst->bits[0], &exp);
    else if (exp < 0)
      multiply_to_exp(dst, &exp);
    dst->bit.exp = exp;
  }

  if (res && dst) {
    s21_dcml_init(dst);
  }
  return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (s21_can_I_do_it(src) || dst == s21_NULL) {
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