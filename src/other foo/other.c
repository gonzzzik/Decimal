#include "../debug.c"
#include "../s21_decimal.h"
#include "../s21_spec_foo.c"
#include "../s21_spec_foo.h"

int s21_negate(s21_decimal value, s21_decimal* result) {
  if (s21_can_I_do_it(value)) {
    s21_dcml_init(result);
    return 1;
  }

  *result = value;
  result->bit.sign = ~result->bit.sign;

  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
  if (s21_can_I_do_it(value)) {
    s21_dcml_init(result);
    return 1;
  }

  *result = value;
  while (result->bit.exp) {
    dev_10(result);
    result->bit.exp--;
  }

  return 0;
}

uint32_t dev_10(s21_decimal* value) {
  uint64_t rem = 0, tmp = 0;
  for (int i = 2; i >= 0; i--) {
    tmp = (rem << 32) | value->bits[i];
    rem = tmp % 10;
    value->bits[i] = tmp / 10;
  }
  return rem;
}

int s21_round(s21_decimal value, s21_decimal* result) {
  if (s21_can_I_do_it(value)) {
    s21_dcml_init(result);
    return 1;
  }

  value.bit.exp--;
  s21_truncate(value, &value);
  uint32_t rem = dev_10(&value);
  value.bit.exp = 0;
  if (rem >= 5) s21_plus_1(&value);

  *result = value;

  return 0;
}

int s21_floor(s21_decimal value, s21_decimal* result) {
  if (s21_can_I_do_it(value)) {
    s21_dcml_init(result);
    return 1;
  }

  s21_truncate(value, &value);
  if (value.bit.sign) s21_plus_1(&value);
  *result = value;

  return 0;
}
