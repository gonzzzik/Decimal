#include <stdio.h>

#include "../s21_decimal.h"

int main(void) { return 0; }

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    if (src < 0) {
        dst->bits.sign = 1;
        src *= -1;
    }

    while (src % 10) {
        dst->bits.exp++;
        src /= 10;
    }

    dst->bits.mantissa[0] = src;
}