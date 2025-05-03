#include "../s21_decimal.h"
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

  while (value.bit.exp) {
    unsigned long tmp = 0, rem = 0;
    for (int i = 2; i >= 0; i--) {
      tmp = (rem << 32) | value.bits[i];
      rem = tmp % 10;
      result->bits[i] = tmp / 10;
    }
    value.bit.exp--;
  }

  result->bit.sign = value.bit.sign;
  return 0;
}

int s21_round(s21_decimal value, s21_decimal* result) {
  if (s21_can_I_do_it(value)) {
    s21_dcml_init(result);
    return 1;
  }

  value.bit.exp--;
  s21_truncate(value, &value);
  int last = value.bits[0] % 10;

  value.bit.exp++;
  s21_truncate(value, &value);
  if (last > 4) plus_1(value);

  *result = value;

  return 0;
}

int s21_floor(s21_decimal value, s21_decimal* result) {
  if (s21_can_I_do_it(value)) {
    s21_dcml_init(result);
    return 1;
  }

  s21_truncate(value, &value);
  if (value.bit.sign) s21_plus_1;

  return 0;
}
/*
int main(void) {
  s21_decimal a = {.bit.sign = 0, .bit.exp = 15, .bit.mantissa = {0, 15, 35}};
  s21_decimal res;

  int err = s21_negate(a, &res);
  printf("%d: %d --- %d", err, a.bit.sign, res.bit.sign);

  return 0;
} */