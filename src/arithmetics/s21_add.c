#include "../debug.c"
#include "../miscellaneous/normalize_exponents.c"
#include "../s21_decimal.h"

void decimal_summ(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  align_exponents(&value_1, &value_2);
  decimal_summ(value_1, value_2, result);
  return 0;
}

void add_mantissas(s21_decimal val1, s21_decimal val2,
                   s21_decimal *res) {  // функция сложения мантисс
  unsigned long long carry = 0;

  for (int i = 0; i < 3; i++) {
    unsigned long long temp_sum = (unsigned long long)val1.bits.mantissa[i] +
                                  (unsigned long long)val2.bits.mantissa[i] +
                                  carry;

    res->bits.mantissa[i] = (unsigned int)(temp_sum & 0xFFFFFFFF);
    carry = temp_sum >> 32;
  }
}

void subtract_mantissas(s21_decimal val1, s21_decimal val2,
                        s21_decimal *res) {  // функция вычитания мантисс
  long long borrow = 0;

  for (int i = 0; i < 3; i++) {
    long long diff = (long long)val1.bits.mantissa[i] -
                     (long long)val2.bits.mantissa[i] - borrow;

    if (diff < 0) {
      diff += ((long long)1 << 32);
      borrow = 1;
    } else {
      borrow = 0;
    }

    res->bits.mantissa[i] = (unsigned int)(diff & 0xFFFFFFFF);
  }
}

void decimal_summ(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result) {
  int sign1 = value_1.bits.sign;
  int sign2 = value_2.bits.sign;

  for (int i = 0; i < 3; i++) {
    result->bits.mantissa[i] = 0;
  }

  if (sign1 == sign2) {
    add_mantissas(value_1, value_2, result);
    result->bits.sign = sign1;
  } else {
    if (value_1.bits.mantissa > value_2.bits.mantissa) {
      subtract_mantissas(value_1, value_2, result);
      result->bits.sign = sign1;
    } else {
      subtract_mantissas(value_2, value_1, result);
      result->bits.sign = sign2;
    }
  }
  result->bits.exp = value_1.bits.exp;
}

int main() {
  s21_decimal dec_1 = {.bits.sign = 0, .bits.exp = 0, .bits.mantissa = {0, 1, 0}};
  s21_decimal dec_2 = {.bits.sign = 0, .bits.exp = 5, .bits.mantissa = {0, 1, 0}};
  s21_decimal dec_check = {.bits.sign = 0, .bits.exp = 5, .bits.mantissa = {0, 100001, 0}};
  s21_decimal result = {0};

  printf("Число 1: ");
  debug_print_decimal(dec_1);
  printf("экспонента числа 1: %d\n",dec_1.bits.exp);

  printf("Число 2: ");
  debug_print_decimal(dec_2);
  printf("экспонента числа 2: %d\n",dec_2.bits.exp);


  s21_add(dec_1, dec_2, &result);

  printf("\nРезультат сложения в десятичной системе: ");
  debug_print_decimal(result);
  printf("Экспонента фактического результата: %d\n\n", result.bits.exp);
  printf("Ожидаемый результат: ");
  debug_print_decimal(dec_check);
  printf("Экспонента ожидаемого результата: %d\n", dec_check.bits.exp);

  printf("Двоичное представление фактического результата:\n");
  debug_print_binary(result);
  printf("\nДвоичное представление ожидаемого результата:\n");
  debug_print_binary(dec_check);

  return 0;
}