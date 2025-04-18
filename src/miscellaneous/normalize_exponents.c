#include <math.h>

#include "../s21_decimal.h"

void set_common_exp(s21_decimal *value_1, s21_decimal *value_2);
int less_common_multiple(int a, int b);
int greatest_common_divider(int a, int b);
void get_decimal_exponent(s21_decimal *dec);
void multiply_by_10(s21_decimal *dec);
bool divide_by_10(s21_decimal *dec);

bool divide_by_10(s21_decimal *dec) {
  unsigned long long remainder = 0;  // остаток

  for (int i = 2; i >= 0; i--) {
    unsigned long long current = (remainder << 32) | dec->bits.mantissa[i];
    dec->bits.mantissa[i] = (unsigned int)(current / 10);
    remainder = current % 10;
  }

  return remainder == 0;
}

void multiply_by_10(s21_decimal *dec) {
  for (int i = 0; i < 3; i++) {
    dec->bits.mantissa[i] *= 10;
  }

  if (dec->bits.mantissa[0] > 0xFFFFFFFF) {
    dec->bits.mantissa[0] /= 10;
    dec->bits.mantissa[1] += 1;
  }
}

void get_decimal_exponent(s21_decimal *dec) {
  while (dec->bits.exp < 28) {
    unsigned int backup[3] = {dec->bits.mantissa[0], dec->bits.mantissa[1],
                              dec->bits.mantissa[2]};

    if (!divide_by_10(dec->bits.mantissa)) {
      dec->bits.mantissa[0] = backup[0];
      dec->bits.mantissa[1] = backup[1];
      dec->bits.mantissa[2] = backup[2];
      break;
    }

    dec->bits.exp++;
  }
}

void align_exponents(
    s21_decimal *dec1,
    s21_decimal *dec2) {  // сравнять экспоненты и нормализовать число в
                          // соответствии с экспонентой
  if (dec1->bits.exp && dec2->bits.exp) {
    int exp1 = dec1->bits.exp;
    int exp2 = dec2->bits.exp;

    while (exp1 < exp2) {
      multiply_by_10(dec2);
      dec2->bits.exp--;
      exp2--;
    }
    while (exp2 < exp1) {
      multiply_by_10(dec1);
      dec1->bits.exp--;
      exp1--;
    }
  }
}

void multiply_by_exponent(s21_decimal *dec) {
  for (int i = 0; i < dec->bits.exp; i++) {
    multiply_by_10(dec);
  }
}

void divide_by_exponent(s21_decimal *dec) {
  for (int i = 0; i < dec->bits.exp; i++) {
    divide_by_10(dec);
  }
}