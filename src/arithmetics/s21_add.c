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
  unsigned int sum = 0;

  for (int i = 0; i < 3; i++) {
    int is_negative = value_1.bits.sign || value_2.bits.sign;
    sum = is_negative
              ? (value_1.bits.mantissa[i] < value_2.bits.mantissa[i]
                     ? (int)value_2.bits.mantissa[i] -
                           (int)value_1.bits.mantissa[i] - carry
                     : value_1.bits.mantissa[i] - value_2.bits.mantissa[i] -
                           carry)
              : value_1.bits.mantissa[i] + value_2.bits.mantissa[i] + carry;
    carry = sum >> 32;
    result->bits.mantissa[i] = (sum & 0xFFFFFFFF);
  }

  result->bits.sign = 1 ? 1 : 0;
}

void normalize(s21_decimal value_1, s21_decimal value_2) {}

int main() {
  s21_decimal dec1 = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  s21_decimal dec2 = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  s21_decimal result = {0};
  char string[BUFSIZ] = {0};

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

  print_comma(string, result.bits.exp);
  printf("%s\n", string);
  return 0;
}