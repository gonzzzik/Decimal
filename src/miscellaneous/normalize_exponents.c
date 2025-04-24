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
  unsigned long long carry = 0;
  for (int i = 0; i < 3; i++) {
      unsigned long long temp = (unsigned long long)dec->bits.mantissa[i] * 10 + carry;
      dec->bits.mantissa[i] = (unsigned int)(temp & 0xFFFFFFFF);
      carry = temp >> 32;
  }
  if (carry != 0) {
      printf("ПЕРЕПОЛНЕНИЕ \n");
  }
}


void align_exponents(
    s21_decimal *dec1,
    s21_decimal *dec2) {  // сравнять экспоненты и нормализовать число в
                          // соответствии с экспонентой (при положительной экспоненте)
    while (dec1->bits.exp > dec2->bits.exp) {
      multiply_by_10(dec2);
      dec2->bits.exp++;
    }
    while (dec2->bits.exp > dec1->bits.exp) {
      multiply_by_10(dec1);
      dec1->bits.exp++;
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