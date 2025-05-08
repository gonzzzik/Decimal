#include "../s21_decimal.h"
#include "../s21_spec_foo.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (result == s21_NULL || s21_can_I_do_it(value_1) || s21_can_I_do_it(value_2)) return 4;
    s21_big_decimal val1 = {{0}}, val2 = {{0}}, res = {{0}};
    normalize(value_1, value_2, &val1, &val2);

    int sign1 = val1.bit.sign;
    int sign2 = val2.bit.sign;
    value_1.bit.sign = value_2.bit.sign = 0;

    if (sign1 == sign2) {
        add_mantissas(val1, val2, &res);
        res.bit.sign = sign1;
    } else if (s21_is_greater(value_1, value_2)) {
        subtract_mantissas(val1, val2, &res);
        res.bit.sign = sign1;
    } else {
        subtract_mantissas(val2, val1, &res);
        res.bit.sign = sign2;
    }

    if (value_2.bit.exp > value_1.bit.exp)
        res.bit.exp = value_2.bit.exp;
    else
        res.bit.exp = value_1.bit.exp;

    if (res.bit.mantissa && (sign1 || sign2)) res.bit.sign = 1;

    return big_to_dcml(res, result);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (result == s21_NULL || s21_can_I_do_it(value_1) || s21_can_I_do_it(value_2)) return 4;
    s21_big_decimal val1 = {{0}}, val2 = {{0}}, res = {{0}};
    normalize(value_1, value_2, &val1, &val2);

    int sign1 = val1.bit.sign;
    int sign2 = val2.bit.sign;
    value_1.bit.sign = value_2.bit.sign = 0;

    if (sign1 != sign2) {
        add_mantissas(val1, val2, &res);
        res.bit.sign = sign1;
    } else if (s21_is_greater(value_1, value_2)) {
        subtract_mantissas(val1, val2, &res);
        res.bit.sign = sign1;
    } else {
        subtract_mantissas(val2, val1, &res);
        res.bit.sign = sign2;
    }

    if (value_2.bit.exp > value_1.bit.exp)
        res.bit.exp = value_2.bit.exp;
    else
        res.bit.exp = value_1.bit.exp;

    return big_to_dcml(res, result);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (result == s21_NULL || s21_can_I_do_it(value_1) || s21_can_I_do_it(value_2)) return 4;

    s21_big_decimal val1 = {{0}}, val2 = {{0}}, res = {{0}};
    normalize(value_1, value_2, &val1, &val2);
    res.bit.exp = val1.bit.exp + val2.bit.exp;
    res.bit.sign = (val1.bit.sign) ? val1.bit.sign : val2.bit.sign;

    while (val1.bits[0]) {
        if (s21_muldiv_int(&val1, div, 2, 1)) add_mantissas(res, val2, &res);
        s21_muldiv_int(&val2, mul, 2, 1);
        if (res.bits[6]) {
            s21_muldiv_int(&val2, div, 10, 1);
            s21_muldiv_int(&res, div, 10, 1);
            res.bit.exp--;
        }
    }

    int err = big_to_dcml(res, result);

    if (err) s21_dcml_init(result);
    return err;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (result == s21_NULL || s21_can_I_do_it(value_1) || s21_can_I_do_it(value_2)) return 4;
    if (!value_2.bits[0] && !value_2.bits[1] && !value_2.bits[2]) return 3;

    s21_big_decimal val1 = {{0}}, val2 = {{0}}, empty = {{0}}, res = {{0}};
    normalize(value_1, value_2, &val1, &val2);
    res.bit.exp = (val1.bit.exp > val2.bit.exp) ? val1.bit.exp - val2.bit.exp : 0;
    float count = 1;
    s21_big_decimal tmp = val2;
    /* разобраться с приведением */
    while (!(val1.bits[6])) s21_muldiv_int(&val1, mul, 2, 1), count++;
    while (!(val2.bits[6])) s21_muldiv_int(&val2, mul, 2, 1), count--;

    int flag = 0;
    while (!flag) {
        if (s21_big_is_greater(val1, val2)) {
            subtract_mantissas(val1, val2, &val1);
            res.bits[0]++;
        }
        if (s21_big_is_equal(val2, tmp) || s21_big_is_equal(val1, empty)) flag = 1;
        s21_muldiv_int(&res, mul, 2, 1);
        s21_muldiv_int(&val2, div, 2, 1);
        count++;
    }
    res.bit.exp += (int)(count * log10(2));
    int err = big_to_dcml(res, result);

    if (err) s21_dcml_init(result);
    return err;
}

int main() {
    s21_decimal v1 = {{10, 0x00000000, 0x00000000, 0x00000000}};
    s21_decimal v2 = {{20010, 0x00000000, 0x00000000, 0x00000000}};
    s21_decimal need = {{0x9BD58676, 0x15E87A6F, 0x00042243, 0x001C0000}};
    s21_decimal res = {{0}};

    int err = s21_div(v1, v2, &res);

    debug_print_decimal(v1);
    debug_print_decimal(v2);
    debug_print_decimal(res);
    debug_print_binary(res);
    debug_print_decimal(need);
    debug_print_binary(need);
    printf("%d", err);

    return 0;
}