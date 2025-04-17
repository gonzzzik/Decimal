#include <string.h>

#include "../debug.c"
#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  decimal_summ(value_1, value_2, result);
  result->bits.little_word =
      value_1.bits.little_word + value_2.bits.little_word;

  /*      result->bits.exp = value_1.bits.exp;
          result->bits.sign = value_1.bits.sign; */// понадобится в будущем

  return 0;
}

void decimal_summ(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result) {
  unsigned long long carry = 0;
  if (value_1.bits.sign || value_2.bits.sign) {
    for (int i = 0; i < 3; i++) {
      if (value_1.bits.mantissa[i] < value_2.bits.mantissa[i]) {
        unsigned int ostatok =
            value_2.bits.mantissa[i] - value_1.bits.mantissa[i];
        unsigned int sum = (int)value_1.bits.mantissa[i] -
                           (int)value_2.bits.mantissa[i] - carry +
                           (ostatok * 2);
        result->bits.sign = 1;
        carry = sum >> 32;
        result->bits.mantissa[i] = (sum & 0xFFFFFFFF);
      } else {
        unsigned int sum =
            value_1.bits.mantissa[i] - value_2.bits.mantissa[i] - carry;
        carry = sum >> 32;
        result->bits.mantissa[i] = (sum & 0xFFFFFFFF);
      }
    }
  } else {
    for (int i = 0; i < 3; i++) {
      unsigned int sum =
          value_1.bits.mantissa[i] + value_2.bits.mantissa[i] + carry;
      carry = sum >> 32;
      result->bits.mantissa[i] = (sum & 0xFFFFFFFF);
    }
  }
}

int main() {
  s21_decimal dec1 = {3000, 3000, 3000, 0};
  s21_decimal dec2 = {75634, 63423, 5664, 0x80000000};
  s21_decimal result = {0};
  printf("Число 1 в двоичной системе : ");
  debug_print_binary(dec1);
  printf("Число 2 в двоичной системе : ");
  debug_print_binary(dec2);

  printf("Число 1 в десятичной системе : ");
  debug_print_decimal(dec1);
  printf("Число 2 в десятичной системе : ");
  debug_print_decimal(dec2);

  s21_add(dec1, dec2, &result);
  printf("Результат в двоичной системе : ");
  debug_print_binary(result);
  printf("Результат в десятичной системе : ");
  debug_print_decimal(result);

  return 0;
}