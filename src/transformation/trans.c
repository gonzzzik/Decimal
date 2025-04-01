#include <stdio.h>
#include <stdint.h>
#include "../s21_decimal.h"

void print_bits_uint32(uint32_t value) {
    for (int i = 31; i >= 0; i--) {
        printf("%u", (value >> i) & 1);
        if (i % 8 == 0)
            printf(" ");
    }
}

void debug_printBinary(s21_decimal decimal) {
    const char BLUE[] = "\033[0;34m";
    const char GREEN[] = "\033[0;32m";
    const char RED[] = "\033[0;31m";
    const char RESET[] = "\033[0m";
    int one = 0;

    printf("%s%d%s",GREEN , (decimal.num[3] & (1 << 31)) ? 1 : 0, RESET);

    for (int j = 30; j >= 0; j--) {
        if (j >= 24){
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

    printf("%s|%s",BLUE , RESET);

    for (int i = 2; i >= 0; i--) {
        for (int j = 31; j >= 0; j--) {
            if (decimal.num[i] & (1 << j)) {
                printf("%s1", GREEN);
                one = 1;
            }
            else
                printf("%s0", one ? GREEN : RED);
            printf(RESET);
        }
        
        if (i > 0) printf("%s|%s",BLUE, RESET);
    }
    printf("\n");
    
}

void print_decimal_bits(const s21_decimal *dec) {
    printf("\nРазбивка по полям структуры bits:\n");
    printf("mantissa[0]: ");
    print_bits_uint32((uint32_t)dec->bits.mantissa[0]);
    printf("\n");

    printf("mantissa[1]: ");
    print_bits_uint32((uint32_t)dec->bits.mantissa[1]);
    printf("\n");

    printf("mantissa[2]: ");
    print_bits_uint32((uint32_t)dec->bits.mantissa[2]);
    printf("\n");

    printf("exp (8 бит): ");
    print_bits_uint32((uint32_t)((uint8_t)dec->bits.exp));
    printf("\n");
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {

    for (int i = 0; i < 4; i++) {
        dst->num[i] = 0;
    }

    if (src < 0) {
        dst->bits.sign = 1;
        src = -src;
    }

    dst->bits.mantissa[0] = src;

    print_decimal_bits(dst);

    return 0;
}

int main(void) {
    s21_decimal dec = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000};
    debug_printBinary(dec);
    s21_from_int_to_decimal(111, &dec);
    return 0;
}
