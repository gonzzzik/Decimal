#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_spec_foo.h"

void debug_print_binary(s21_decimal decimal) {
  const char BLUE[] = "\033[0;34m";
  const char GREEN[] = "\033[0;32m";
  const char RED[] = "\033[0;31m";
  const char RESET[] = "\033[0m";
  int one = 0;

  printf("%s%d%s", GREEN, (decimal.bits[3] & (1 << 31)) ? 1 : 0, RESET);

  for (int j = 30; j >= 0; j--) {
    if (j >= 24) {
      (decimal.bits[3] & (1 << j)) ? printf("1") : printf("%s0", RED);
      printf(RESET);
    } else if (j >= 16) {
      (decimal.bits[3] & (1 << j)) ? printf("%s1", GREEN)
                                   : printf("%s0", GREEN);
      printf(RESET);
    } else {
      (decimal.bits[3] & (1 << j)) ? printf("1") : printf("%s0", RED);
      printf(RESET);
    }
  }

  printf("%s|%s", BLUE, RESET);

  for (int i = 2; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      if (decimal.bits[i] & (1 << j)) {
        printf("%s1", GREEN);
        one = 1;
      } else
        printf("%s0", one ? GREEN : RED);
      printf(RESET);
    }

    if (i > 0) printf("%s|%s", BLUE, RESET);
  }
  printf("\n");
}

void print_comma(char* str, int exp) {
  if (-exp > 38) {
    memcpy(str, "(s21_NULL)", 7);
    return;
  }
  int len = strlen(str), i = 0, j = 0;
  char result[40] = {0};

  if (len <= -exp) {
    result[i++] = '0', result[i++] = ',';
    while (exp++ < 0) {
      if (exp + len <= 0)
        result[i++] = '0';
      else
        result[i++] = str[j++];
    }
  } else {
    for (; i < len + exp; i++) result[i] = str[i];
    result[i++] = ',';
    for (; i - 1 < len; i++) result[i] = str[i - 1];
  }

  memcpy(str, result, i);
}

void debug_print_decimal(s21_decimal decimal) {
  int sign = (decimal.bits[3] & 0x80000000) ? 1 : 0;
  char buffer[40] = {0};
  int i = 0;

  __int128_t decimal_bits = 0;
  decimal_bits = (__int128_t)decimal.bits[0] |
                 (__int128_t)decimal.bits[1] << 32 |
                 (__int128_t)decimal.bits[2] << 64;

  while (decimal_bits > 0) {
    buffer[i++] = (decimal_bits % 10) + '0';
    decimal_bits /= 10;
  }

  char temp[40] = {0};
  int len = i;
  int j = 0;

  while (len > 0) temp[j++] = buffer[--len];

  if (decimal.bit.exp) print_comma(temp, -decimal.bit.exp);

  if (sign)
    printf("\ndecimal в десятичной системе счисления : -%s\n", temp);
  else
    printf("\ndecimal в десятичной системе счисления : %s\n", temp);
}

/* int main() {
  s21_decimal v1 = {{0x00000467, 0x0000007A, 0x00003215, 0x80010000}};
  s21_decimal v2 = {.bit.sign = 1, .bit.exp = 2, .bit.mantissa = {3855, 15, 2}};
  s21_decimal dec;

  s21_round(v1, &dec);
  debug_print_decimal(v1);
  debug_print_binary(v1);
  debug_print_decimal(v2);
  debug_print_binary(v2);

  debug_print_decimal(dec);
  debug_print_binary(dec);
  return 0;
} */
