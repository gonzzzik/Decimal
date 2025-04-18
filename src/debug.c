#include <stdio.h>
#include <string.h>

#include "s21_decimal.h"
typedef struct {
  int num[4];
} dcml;

void debug_print_binary(s21_decimal decimal) {
  const char BLUE[] = "\033[0;34m";
  const char GREEN[] = "\033[0;32m";
  const char RED[] = "\033[0;31m";
  const char RESET[] = "\033[0m";
  int one = 0;

  printf("%s%d%s", GREEN, (decimal.num[3] & (1 << 31)) ? 1 : 0, RESET);

  for (int j = 30; j >= 0; j--) {
    if (j >= 24) {
      (decimal.num[3] & (1 << j)) ? printf("1") : printf("%s0", RED);
      printf(RESET);
    } else if (j >= 16) {
      (decimal.num[3] & (1 << j)) ? printf("%s1", GREEN) : printf("%s0", GREEN);
      printf(RESET);
    } else {
      (decimal.num[3] & (1 << j)) ? printf("1") : printf("%s0", RED);
      printf(RESET);
    }
  }

  printf("%s|%s", BLUE, RESET);

  for (int i = 2; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      if (decimal.num[i] & (1 << j)) {
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
    memcpy(str, "(null)", 7);
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
  if (decimal.num[0] == 0 && decimal.num[1] == 0 && decimal.num[2] == 0) {
    puts("0");
    return;
  }

  int sign = (decimal.num[3] & 0x80000000) ? 1 : 0;
  char buffer[40] = {0};
  int i = 0;

  __int128_t decimal_num = 0;
  decimal_num = (__int128_t)decimal.num[0] | (__int128_t)decimal.num[1] << 32 |
                (__int128_t)decimal.num[2] << 64;

  while (decimal_num > 0) {
    buffer[i++] = (decimal_num % 10) + '0';
    decimal_num /= 10;
  }

  char temp[40] = {0};
  int len = i;
  int j = 0;

  while (len > 0) temp[j++] = buffer[--len];

  int exp = decimal.bits.exp;
  if (exp >= 0) {
    for (int i = 0; i < exp; i++, j++) temp[j] = '0';
  } else {
    int point_pos = j + exp;

    for (int i = j - 1; i >= 0; i--) {
      if (i >= point_pos) {
        temp[i + exp] = temp[i];
      } else {
        temp[i + exp] = '0';
      }
    }

    temp[point_pos] = '.';
    j -= exp;
  }

  if (sign)
    printf("-%s\n", temp);
  else
    printf("%s\n", temp);
}

void debug_print_decimal_with_no_exponent(s21_decimal decimal) {
  if (decimal.num[0] == 0 && decimal.num[1] == 0 && decimal.num[2] == 0) {
    puts("0");
    return;
  }

  int sign = (decimal.num[3] & 0x80000000) ? 1 : 0;
  char buffer[40] = {0};
  int i = 0;

  __int128_t decimal_num = 0;
  decimal_num = (__int128_t)decimal.num[0] | (__int128_t)decimal.num[1] << 32 |
                (__int128_t)decimal.num[2] << 64;

  while (decimal_num > 0) {
    buffer[i++] = (decimal_num % 10) + '0';
    decimal_num /= 10;
  }

  char temp[40] = {0};
  int len = i;
  int j = 0;

  while (len > 0) temp[j++] = buffer[--len];

  int exp = 0;
  if (exp >= 0) {
    for (int i = 0; i < exp; i++, j++) temp[j] = '0';
  } else {
    int point_pos = j + exp;

    for (int i = j - 1; i >= 0; i--) {
      if (i >= point_pos) {
        temp[i + exp] = temp[i];
      } else {
        temp[i + exp] = '0';
      }
    }

    temp[point_pos] = '.';
    j -= exp;
  }

  if (sign)
    printf("-%s\n", temp);
  else
    printf("%s\n", temp);
}

// int main() {
//     s21_decimal dec = {.bits.sign = 1, .bits.exp = -38, .bits.mantissa =
//     {3855, 0, 0}}; debug_print_decimal(dec); debug_print_binary(dec); return
//     0;
// }