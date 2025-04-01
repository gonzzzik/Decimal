#include "s21_decimal.h"
#include <stdio.h>

void debug_print_binary(s21_decimal decimal) {
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

void debug_print_decimal(s21_decimal decimal) {
    int sign = (decimal.num[3] & 0x80000000) ? 1 : 0;
    char buffer[40] = {0};
    int i = 0;

    __int128_t decimal_num = 0;
    decimal_num = (__int128_t)decimal.num[0] | (__int128_t)decimal.num[1] << 32 | (__int128_t)decimal.num[2] << 64;

    while (decimal_num > 0) {
        buffer[i++] = (decimal_num % 10) + '0';
        decimal_num /= 10;
    }

    char temp[40] = {0};
    int len = i;
    int j = 0;

    while (len > 0) {
        temp[j++] = buffer[--len];
    }
    if(sign) printf("\ndecimal в десятичной системе счисления : -%s\n", temp);
    else printf("\ndecimal в десятичной системе счисления : %s\n", temp);
}

int main() {
    s21_decimal dec = { 0xFFFFFFFF, 0x00000001, 0x0000000, 0x80000000};
    debug_print_decimal(dec);
    debug_print_binary(dec);
    return 0;
}