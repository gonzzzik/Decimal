#ifndef TESTS_H
#define TESTS_H

#include <check.h>

#include "../s21_decimal.h"
#define UINT_MAX 4294967295

int test_other();
Suite *suite_negative(void);
Suite *suite_truncate(void);
Suite *suite_round(void);
Suite *suite_floor(void);

#endif