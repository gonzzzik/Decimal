#include "../debug.c"
#include "../miscellaneous/normalize_exponents.c"
#include "../s21_decimal.h"

void decimal_summ(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
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

  if (value_1.bits.exp > 0)
    multiply_by_exponent(
        value_1.bits.mantissa);  // ПОКА НЕ УБИРАТЬ (умножение складываемого
                                 // числа на экспоненту, в будущем перенести
                                 // экспоненту в результат)
  if (value_2.bits.exp > 0)
    multiply_by_exponent(
        value_2.bits.mantissa);  // ПОКА НЕ УБИРАТЬ (умножение складываемого
                                 // числа на экспоненту, в будущем перенести
                                 // экспоненту в результат и умножить )

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
}

int main() {
  s21_decimal dec1 = {0, 0, 1000000, 0x00000000};
  s21_decimal dec2 = {0, 0, 9, 0x80000000};
  s21_decimal result = {0};

  get_decimal_exponent(&dec1);
  get_decimal_exponent(&dec2);

  printf("Начальная экспонента числа 1: %d\n", dec1.bits.exp);
  printf("Начальная экспонента числа 2: %d\n\n", dec2.bits.exp);

  printf("Число 1 с учётом экспоненты (exp = %d): ", dec1.bits.exp);
  debug_print_decimal_with_no_exponent(dec1);

  printf(
      "Число 1 без учёта экспоненты (число, умноженное на экспоненту (exp = "
      "%d)): ",
      dec1.bits.exp);
  debug_print_decimal(dec1);

  printf("Число 2 с учётом экспоненты (exp = %d): ", dec2.bits.exp);
  debug_print_decimal_with_no_exponent(dec2);

  printf(
      "Число 2 без учёта экспоненты (число, умноженное на экспоненту (exp = "
      "%d)): ",
      dec2.bits.exp);
  debug_print_decimal(dec2);

  align_exponents(&dec1,
                  &dec2);  // Выравнивание экспонент обоих чисел перед сложением
  s21_add(dec1, dec2, &result);  // Сложение

  printf("\nРезультат сложения в десятичной системе: ");
  debug_print_decimal(result);

  return 0;
}
