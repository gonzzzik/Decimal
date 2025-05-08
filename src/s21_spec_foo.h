#ifndef SPEC_FOO_H
#define SPEC_FOO_H

#include <math.h>

#include "s21_decimal.h"

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

#define div 0
#define mul 1

/* s21_spec_foo.c */
int s21_can_I_do_it(s21_decimal value);
int s21_can_I_do_float(long double num);
void s21_dcml_init(s21_decimal *value);
void bank_round(s21_big_decimal *dcml);
void normalize(s21_decimal dcml1, s21_decimal dcml2, s21_big_decimal *big_dcml1, s21_big_decimal *big_dcml2);
void BIG_normalize(s21_big_decimal *big_dcml1, s21_big_decimal *big_dcml2);
int big_to_dcml(s21_big_decimal dcml, s21_decimal *res);

/* s21_spec_math.c */
void add_mantissas(s21_big_decimal val1, s21_big_decimal val2, s21_big_decimal *res);
void subtract_mantissas(s21_big_decimal val1, s21_big_decimal val2, s21_big_decimal *res);
__uint64_t s21_muldiv_int(s21_big_decimal *big_dcml, int operation, int operand, int iterations);
__uint64_t div_int(s21_decimal *value, int del);
void s21_big_plus_1(s21_big_decimal *val);
void s21_plus_1(s21_decimal *val);

/* s21_spec_comp.c */
int s21_big_is_equal(s21_big_decimal val1, s21_big_decimal val2);
int s21_big_is_greater(s21_big_decimal val1, s21_big_decimal val2);

/* debug.c */
void debug_print_binary(s21_decimal decimal);
void debug_print_decimal(s21_decimal decimal);

#endif
