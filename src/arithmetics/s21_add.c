#include "../s21_decimal.h"
#include "../s21_spec_foo.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == s21_NULL || s21_can_I_do_it(value_1) ||
      s21_can_I_do_it(value_2))
    return 4;
  s21_big_decimal val1 = {{0}}, val2 = {{0}}, res = {{0}};
  normalize(value_1, value_2, &val1, &val2);

  int sign1 = val1.bit.sign;
  int sign2 = val2.bit.sign;
  value_1.bit.sign = value_2.bit.sign = 0;

  if (sign1 == sign2) {
    add_mantissas(val1, val2, &res);
    res.bit.sign = sign1;
  } else if (s21_is_greater(value_1, value_2)) {
    subtract_mantissas(val1, val2, &res);
    res.bit.sign = sign1;
  } else {
    subtract_mantissas(val2, val1, &res);
    res.bit.sign = sign2;
  }

  if (value_2.bit.exp > value_1.bit.exp)
    res.bit.exp = value_2.bit.exp;
  else
    res.bit.exp = value_1.bit.exp;

  return big_to_dcml(res, result);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == s21_NULL || s21_can_I_do_it(value_1) ||
      s21_can_I_do_it(value_2))
    return 4;
  s21_big_decimal val1 = {{0}}, val2 = {{0}}, res = {{0}};

  int sign1 = value_1.bit.sign;
  int sign2 = value_2.bit.sign;

  value_1.bit.sign = 0;
  value_2.bit.sign = 0;

  normalize(value_1, value_2, &val1, &val2);

  if (sign1 != sign2) {
    add_mantissas(val1, val2, &res);
    res.bit.sign = sign1;
  } else if (s21_is_greater(value_1, value_2)) {
    subtract_mantissas(val1, val2, &res);
    res.bit.sign = sign1;
  } else {
    subtract_mantissas(val2, val1, &res);
    res.bit.sign = !sign1;
  }

  res.bit.exp =
      (value_2.bit.exp > value_1.bit.exp) ? value_2.bit.exp : value_1.bit.exp;
  int err = big_to_dcml(res, result);
  return err;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == s21_NULL || s21_can_I_do_it(value_1) ||
      s21_can_I_do_it(value_2))
    return 4;

  s21_big_decimal val1 = {{0}}, val2 = {{0}}, res = {{0}};
  normalize(value_1, value_2, &val1, &val2);
  res.bit.exp = val1.bit.exp + val2.bit.exp;
  res.bit.sign = (val1.bit.sign) ? val1.bit.sign : val2.bit.sign;

  while (val1.bits[0]) {
    if (s21_muldiv_int(&val1, div, 2, 1))
      add_mantissas(res, val2, &res);
    s21_muldiv_int(&val2, mul, 2, 1);
    if (res.bits[6]) {
      s21_muldiv_int(&val2, div, 10, 1);
      s21_muldiv_int(&res, div, 10, 1);
      res.bit.exp--;
    }
  }

  int err = big_to_dcml(res, result);

  if (err)
    s21_dcml_init(result);
  return err;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == s21_NULL || s21_can_I_do_it(value_1) ||
      s21_can_I_do_it(value_2))
    return 4;
  if (s21_is_equal(value_2, (s21_decimal){{0, 0, 0, 0}}))
    return 3;

  s21_big_decimal val1 = {{0}}, val2 = {{0}}, empty = {{0}}, res = {{0}};
  normalize(value_1, value_2, &val1, &val2);
  val1.bit.sign = val2.bit.sign = 0;

  int flag = 0, delta_exp = 0;
  s21_big_decimal tmp = val2;
  if (!s21_big_is_equal(val1, empty))
    while (!(val1.bits[6]))
      s21_muldiv_int(&val1, mul, 10, 1), delta_exp++;
  while (!(val2.bits[6]))
    s21_muldiv_int(&val2, mul, 10, 1), delta_exp--;

  while (!flag) {
    while (s21_big_is_greater(val1, val2)) {
      subtract_mantissas(val1, val2, &val1);
      res.bits[0]++;
    }
    if (s21_big_is_equal(val2, tmp) || s21_big_is_equal(val1, empty))
      flag = 1;
    else
      s21_muldiv_int(&res, mul, 10, 1), delta_exp++;

    s21_muldiv_int(&val2, div, 10, 1);
  }

  res.bit.exp +=
      ((val1.bit.exp > val2.bit.exp) ? val1.bit.exp - val2.bit.exp : 0) +
      delta_exp;
  res.bit.sign = value_1.bit.sign ^ value_2.bit.sign;

  int err = big_to_dcml(res, result);
  if (err)
    s21_dcml_init(result);

  return err;
}

/* int main() {
    s21_decimal v1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal v2 = {{0x00000033, 0x00000000, 0x00000000, 0x00020000}};
    s21_decimal need = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
    s21_decimal res = {{0}};

    int err = s21_add(v1, v2, &res);

    debug_print_decimal(v1);
    debug_print_decimal(v2);
    debug_print_decimal(res);
    debug_print_binary(res);
    debug_print_decimal(need);
    debug_print_binary(need);
    printf("%d %d", err, s21_is_equal(res, need));

    return 0;
} */