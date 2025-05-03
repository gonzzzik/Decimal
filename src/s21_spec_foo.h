#ifndef SPEC_FOO_H
#define SPEC_FOO_H

#include <math.h>
#include <stdio.h>

typedef union {
  unsigned int bits[8];
  struct {
    unsigned int mantissa[7];
    int little_word : 16;
    unsigned int exp : 8;
    int _void : 7;
    unsigned int sign : 1;
  } bit;
} s21_big_decimal;

static int s21_can_I_do_it(s21_decimal value);
// static int s21_can_I_do_float(long double num);
static void s21_dcml_init(s21_decimal* value);
static void s21_plus_1(s21_decimal* val);
// static void s21_muldev_int(s21_big_decimal* big_dcml, int operation,
//                            int operand, int count);
// static void normalize(s21_decimal dcml1, s21_decimal dcml2,
//                       s21_big_decimal* big_dcml1, s21_big_decimal*
//                       big_dcml2);
// static void BIG_normalize(s21_big_decimal* big_dcml1,
//                           s21_big_decimal* big_dcml2);

#endif