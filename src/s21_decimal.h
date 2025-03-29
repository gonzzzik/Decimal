#ifndef S21_DECIMAL_H
#define S21_DECIMEL_H

typedef union {
    int num[4];
    struct {
        int mantissa : 96;
        int little_word : 16;
        int exp : 8;
        int _void : 7;
        int sign : 1;
    } bits;
} s21_decimal;

// Arithmetic foo
/*! @brief Cложение Decimal
    @param value_1,value_2 - слагаемое
    @param result - сумма
    @return код ошибки.
    0 - ОК
    1 - число слишком велико или равно бесконечности
    2 — число слишком мало или равно отрицательной бесконечности; */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// comparison foo
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// transformation foo
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// other foo
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif