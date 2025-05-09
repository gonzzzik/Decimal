#include "./s21_spec_foo.h"

int s21_can_I_do_it(s21_decimal value) {
  return (value.bit.oversize || value.bit._void || (value.bit.exp > 28));
}

void s21_dcml_init(s21_decimal *value) {
  for (int i = 0; i < 4; i++)
    value->bits[i] = 0;
}

s21_big_decimal s21_conversion_from_dec_to_ldec(s21_decimal value) {
  s21_big_decimal my_ldec = {{0}};
  for (int i = 0; i < 3; i++)
    my_ldec.bits[i] = value.bits[i];
  my_ldec.bits[7] = value.bits[3];
  return my_ldec;
}

void bank_round(s21_big_decimal *dcml, int *last_rem) {
  if (dcml->bit.exp == 0)
    return;
  s21_big_decimal tmp = *dcml;
  __uint64_t remainder = s21_muldiv_int(&tmp, div, 10, 1);

  s21_muldiv_int(dcml, div, 10, 1);
  dcml->bit.exp--;
  if (remainder > 5) {
    s21_big_plus_1(dcml);
  } else if (remainder == 5 && (*last_rem > 0 && *last_rem < 5)) {
    s21_big_plus_1(dcml);
  } else if (*last_rem == 0) {
    if (remainder == 5) {
      if (dcml->bit.mantissa[0] & 1)
        s21_big_plus_1(dcml);
    }
  }

  *last_rem = remainder;
}

void normalize(s21_decimal dcml1, s21_decimal dcml2, s21_big_decimal *big_dcml1,
               s21_big_decimal *big_dcml2) {
  big_dcml1->bits[7] = dcml1.bits[3];
  big_dcml2->bits[7] = dcml2.bits[3];
  for (int i = 2; i >= 0; i--) {
    big_dcml1->bits[i] = dcml1.bits[i];
    big_dcml2->bits[i] = dcml2.bits[i];
  }

  if (dcml1.bit.exp > dcml2.bit.exp)
    BIG_normalize(big_dcml1, big_dcml2);
  else if (dcml1.bit.exp < dcml2.bit.exp)
    BIG_normalize(big_dcml2, big_dcml1);

  if (!dcml1.bits[0] && !dcml1.bits[1] && !dcml1.bits[2])
    big_dcml1->bit.exp = 0, big_dcml1->bit.sign = 0;
  if (!dcml2.bits[0] && !dcml2.bits[1] && !dcml2.bits[2])
    big_dcml2->bit.exp = 0, big_dcml2->bit.sign = 0;
}

void BIG_normalize(s21_big_decimal *big_dcml1, s21_big_decimal *big_dcml2) {
  int delta_exp = big_dcml1->bit.exp - big_dcml2->bit.exp;
  s21_muldiv_int(big_dcml2, mul, 10, delta_exp);
  big_dcml2->bit.exp += delta_exp;
}

int big_to_dcml(s21_big_decimal dcml, s21_decimal *res) {
  int err = 0, last_rem = 0;
  s21_dcml_init(res);

  while ((dcml.bits[3] || dcml.bits[4] || dcml.bits[5] || dcml.bits[6]) &&
         dcml.bit.exp) {
    bank_round(&dcml, &last_rem);
  }
  remove_dcml_zeros(&dcml);

  if (dcml.bits[3])
    err = (dcml.bit.sign) ? 2 : 1;
  else if (dcml.bit.exp > 28) {
    while ((dcml.bits[0] || dcml.bits[1] || dcml.bits[2]) && dcml.bit.exp > 28)
      bank_round(&dcml, &last_rem);
    if (dcml.bit.exp > 28)
      err = 2;
  }
  if (!err) {
    for (int i = 0; i < 3; i++)
      res->bits[i] = dcml.bits[i];
    res->bit.exp = dcml.bit.exp;
    if (dcml.bit.sign)
      res->bit.sign = 1;
  }

  return err;
}

void remove_dcml_zeros(s21_big_decimal *dcml) {
  s21_big_decimal tmp = *dcml;

  while (s21_muldiv_int(&tmp, div, 10, 1) == 0 && tmp.bit.exp) {
    tmp.bit.exp--;
    *dcml = tmp;
  }
}