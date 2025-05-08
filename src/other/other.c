#include "../s21_decimal.h"
#include "../s21_spec_foo.h"

int s21_negate(s21_decimal value, s21_decimal* result) {
    if (result == s21_NULL) return 1;
    if (s21_can_I_do_it(value)) {
        s21_dcml_init(result);
        return 1;
    }

    *result = value;
    result->bit.sign = ~result->bit.sign;

    return 0;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
    if (result == s21_NULL) return 1;
    if (s21_can_I_do_it(value)) {
        s21_dcml_init(result);
        return 1;
    }

    *result = value;
    while (result->bit.exp) {
        dev_int(result, 10);
        result->bit.exp--;
    }

    return 0;
}

int s21_round(s21_decimal value, s21_decimal* result) {
    if (result == s21_NULL) return 1;
    if (s21_can_I_do_it(value)) {
        s21_dcml_init(result);
        return 1;
    }

    if (value.bit.exp) {
        value.bit.exp--;
        s21_truncate(value, &value);
        __uint32_t rem = dev_int(&value, 10);
        value.bit.exp = 0;
        if (rem >= 5) s21_plus_1(&value);
    }

    *result = value;

    return 0;
}

int s21_floor(s21_decimal value, s21_decimal* result) {
    if (result == s21_NULL) return 1;
    if (s21_can_I_do_it(value)) {
        s21_dcml_init(result);
        return 1;
    }

    int flag = 0;
    while (value.bit.exp) {
        __uint32_t rem = dev_int(&value, 10);
        value.bit.exp--;
        if (rem) flag = 1;
    }
    if (value.bit.sign && flag) s21_plus_1(&value);

    *result = value;

    return 0;
}
