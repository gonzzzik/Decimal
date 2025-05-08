#include "../s21_decimal.h"
#include "../s21_spec_foo.h"

#define INT_MIN 2147483648U
#define INT_MAX 2147483647

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    if (dst == s21_NULL) return 1;
    s21_dcml_init(dst);

    if (src < 0) {
        dst->bit.sign = 1;
        src = ~src + 1;
    }
    dst->bits[0] = src;

    return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    if (s21_truncate(src, &src) || src.bits[1] || src.bits[2] ||
        src.bits[0] > ((src.bit.sign) ? INT_MIN : INT_MAX) || dst == s21_NULL) {
        if (dst != s21_NULL) *dst = 0;
        return 1;
    }

    *dst = src.bits[0];
    if (src.bit.sign) *dst = -(*dst);

    return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    if (dst == s21_NULL || /*  !(src > 0 && src < 1e-28) || */ (isnan(src) || isinf(src))) return 1;

    if (src == 0.0f) {
        return 0;
    }

    int sign = 0;
    if (src < 0) {
        sign = 1;
        src = -src;
    }

    if (src < 1e-28f) {
        s21_dcml_init(dst);
    }

    s21_dcml_init(dst);
    double val = (double)src;
    int approx_exp = (int)floor(log10(val));
    if (approx_exp < 0) approx_exp = 0;
    int scale = 0;
    val = val * pow(10, approx_exp);
    scale = approx_exp;
    while (scale < 28 && floor(val) != val) {
        val *= 10.0;
        scale++;
    }
    double intpart;
    double fracpart = modf(val, &intpart);
    if (fracpart > 0.5) {
        intpart += 1.0;
    } else if (fracpart == 0.5) {
        if (fmod(intpart, 2.0) != 0.0) {
            intpart += 1.0;
        }
    }
    s21_big_decimal big_dec = {{0}};

    unsigned long long mantissa64 = (unsigned long long)intpart;
    big_dec.bit.mantissa[0] = (unsigned int)(mantissa64 & 0xFFFFFFFF);
    big_dec.bit.mantissa[1] = (unsigned int)((mantissa64 >> 32) & 0xFFFFFFFF);

    big_dec.bit.exp = scale;
    big_dec.bit.sign = sign;

    bank_round(&big_dec);

    int res = big_to_dcml(big_dec, dst);

    return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    if (s21_can_I_do_it(src) || dst == s21_NULL) {
        return 1;
    }
    *dst = 0;

    int scale = src.bit.exp;

    __uint32_t low = src.bit.mantissa[0];
    __uint32_t mid = src.bit.mantissa[1];
    __uint32_t high = src.bit.mantissa[2];

    float value = (float)high * pow(2.0, 64) + (float)mid * pow(2.0, 32) + (float)low;
    value = value / pow(10, scale);

    if (src.bit.sign) {
        value = -value;
    }

    *dst = (float)value;

    return 0;
}
/*
int main() {
    s21_decimal v1 = {{0}};
    int a = -1;
    s21_from_int_to_decimal(a, &v1);
    return 0;
}
 */