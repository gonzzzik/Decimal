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
