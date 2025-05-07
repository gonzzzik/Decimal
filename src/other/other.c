#include "../arithmetics/s21_spec_math.c"
#include "../debug.c"
#include "../s21_decimal.h"
#include "../s21_spec_foo.c"

int s21_negate(s21_decimal value, s21_decimal* result) {
  if (result == NULL) return 1;
  if (s21_can_I_do_it(value)) {
    s21_dcml_init(result);
    return 1;
  }

  *result = value;
  result->bit.sign = ~result->bit.sign;

  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
  if (result == NULL) return 1;
  if (s21_can_I_do_it(value)) {
    s21_dcml_init(result);
    return 1;
  }

  *result = value;
  while (result->bit.exp) {
    dev_int(result, 10);
    result->bit.exp--;
  }

  return 0;
}

int s21_round(s21_decimal value, s21_decimal* result) {
  if (result == NULL) return 1;
  if (s21_can_I_do_it(value)) {
    s21_dcml_init(result);
    return 1;
  }

  value.bit.exp--;
  s21_truncate(value, &value);
  __uint32_t rem = dev_int(&value, 10);
  value.bit.exp = 0;
  if (rem >= 5) s21_plus_1(&value);

  *result = value;

  return 0;
}

int s21_floor(s21_decimal value, s21_decimal* result) {
  if (result == NULL) return 1;
  if (s21_can_I_do_it(value)) {
    s21_dcml_init(result);
    return 1;
  }

  s21_truncate(value, &value);
  if (value.bit.sign) s21_plus_1(&value);
  *result = value;

  return 0;
}
/*
int main() {
  s21_decimal v1 = {{0x00000467, 0x0000007A, 0x00003215, 0x80010000}};
  s21_decimal dec;
  s21_round(v1, &dec);

  debug_print_decimal(v1);
  debug_print_binary(v1);
  debug_print_decimal(dec);
  debug_print_binary(dec);
  return 0;
} */