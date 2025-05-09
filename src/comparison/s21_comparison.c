#include <math.h>

#include "../s21_decimal.h"
#include "../s21_spec_foo.h"

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  if (s21_can_I_do_it(value1) || s21_can_I_do_it(value2))
    return -1;
  if (s21_is_equal(value1, value2))
    return 0;

  int res = 0;
  s21_big_decimal big_val1 = {{0}}, big_val2 = {{0}};
  normalize(value1, value2, &big_val1, &big_val2);

  if (big_val1.bit.sign == big_val2.bit.sign)
    res = s21_big_is_greater(big_val1, big_val2);
  else if (big_val1.bit.sign < big_val2.bit.sign)
    res = 1;

  return res;
}

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  if (s21_can_I_do_it(value1) || s21_can_I_do_it(value2))
    return -1;
  int res = 1;

  s21_big_decimal big_val1 = {{0}}, big_val2 = {{0}};
  normalize(value1, value2, &big_val1, &big_val2);
  res = s21_big_is_equal(big_val1, big_val2);
  if (big_val1.bit.sign != big_val2.bit.sign)
    res = 0;

  return res;
}

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  if (s21_can_I_do_it(value1) || s21_can_I_do_it(value2))
    return -1;
  return !s21_is_greater(value1, value2) && !s21_is_equal(value1, value2);
}

int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2) {
  if (s21_can_I_do_it(value1) || s21_can_I_do_it(value2))
    return -1;
  return !s21_is_greater(value1, value2) || s21_is_equal(value1, value2);
}

int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2) {
  if (s21_can_I_do_it(value1) || s21_can_I_do_it(value2))
    return -1;
  return s21_is_greater(value1, value2) || s21_is_equal(value1, value2);
}

int s21_is_not_equal(s21_decimal value1, s21_decimal value2) {
  if (s21_can_I_do_it(value1) || s21_can_I_do_it(value2))
    return -1;
  return !s21_is_equal(value1, value2);
}

/* int main() {
    s21_decimal v1 = {{0x14490831, 0x00048E23, 0x00000000, 0x00070000}};

    s21_decimal v2 = {{0x164214B7, 0x00000028, 0x00000000, 0x00040000}};
    s21_is_equal(v1, v2);
    s21_decimal nv1 = {.bit = {.exp = 7, .mantissa = {340330545, 298531, 0}}};
    s21_decimal nv2 = {.bit = {.exp = 7, .mantissa = {4062243544, 40000, 0}}};

    debug_print_decimal(v1);
    debug_print_decimal(nv1);
    debug_print_decimal(v2);
    debug_print_decimal(nv2);
    return 0;
} */