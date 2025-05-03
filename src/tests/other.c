#include "tests.h"

static s21_decimal a[] = {
    {.bit = {.sign = 0, .exp = 15, .mantissa = {0, 15, 35}}},
    {.bit = {.sign = 1, .exp = 15, .mantissa = {0, 15, 35}}},
    {.bit = {.sign = 0, .oversize = 1, .exp = 15, .mantissa = {0, 15, 35}}},
    {.bit = {.sign = 0, .oversize = 1, ._void = 1, .mantissa = {0, 15, 35}}},
    {.bit = {.sign = 0, .exp = 15, ._void = 1, .mantissa = {0, 15, 35}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 0, .exp = 7, .mantissa = {3478914188, 5057519, 0}}},
    {.bit = {.sign = 1, .exp = 6, .mantissa = {4272799138, 507, 0}}},
    {.bit = {.sign = 0,
             .exp = 0,
             .mantissa = {4294967295, 4294967295, 4294967295}}},
    {.bit = {.sign = 1,
             .exp = 0,
             .mantissa = {4294967295, 4294967295, 4294967295}}},
    {.bit = {.sign = 0, .exp = 2, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 1, .exp = 2, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 2, .mantissa = {1000000, 0, 0}}},
    {.bit = {.sign = 1, .exp = 2, .mantissa = {1000000, 0, 0}}},
    {.bit = {.sign = 0, .exp = 4, .mantissa = {1127, 122, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1127, 122, 0}}},
    {.bit = {.sign = 0, .exp = 1, .mantissa = {1127, 122, 12821}}},
    {.bit = {.sign = 1, .exp = 2, .mantissa = {1127, 122, 2121712}}},
    {.bit = {.sign = 1, .exp = 5, .mantissa = {1000000, 10000, 10000}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {14, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {15, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {100000, 0, 0}}},
    {.bit = {.sign = 0, .exp = 1, .mantissa = {11, 0, 0}}},
    {.bit = {.sign = 1, .exp = 1, .mantissa = {11, 0, 0}}},
    {.bit = {.sign = 1, .exp = 2, .mantissa = {149, 0, 0}}},
    {.bit = {.sign = 1, .exp = 1, .mantissa = {15, 0, 0}}},
    {.bit = {.sign = 1, .exp = 2, .mantissa = {151, 0, 0}}},
    {.bit = {.sign = 0, .exp = 2, .mantissa = {149, 0, 0}}},
    {.bit = {.sign = 0, .exp = 1, .mantissa = {15, 0, 0}}},
    {.bit = {.sign = 0, .exp = 2, .mantissa = {17, 0, 0}}},
    {.bit = {.sign = 0, .exp = 2, .mantissa = {134, 0, 0}}},
    {.bit = {.sign = 0, .exp = 3, .mantissa = {1765, 0, 0}}},
    {.bit = {.sign = 1, .exp = 3, .mantissa = {1765, 0, 0}}},
    {.bit = {.sign = 0, .exp = 2, .mantissa = {249, 0, 0}}},
    {.bit = {.sign = 0, .exp = 1, .mantissa = {25, 0, 0}}},
    {.bit = {.sign = 0, .exp = 2, .mantissa = {251, 0, 0}}},
    {.bit = {.sign = 1, .exp = 2, .mantissa = {249, 0, 0}}},
    {.bit = {.sign = 1, .exp = 1, .mantissa = {25, 0, 0}}},
    {.bit = {.sign = 1, .exp = 2, .mantissa = {251, 0, 0}}},
    {.bit = {.sign = 0, .exp = 11, .mantissa = {1380269056, 314, 0}}},
    {.bit = {.sign = 0, .exp = 10, .mantissa = {3266079232, 33, 0}}},
    {.bit = {.sign = 0, .exp = 2, .mantissa = {532941407, 2844775614, 0}}},
    {.bit = {.sign = 0, .exp = 2, .mantissa = {532941405, 2844775614, 0}}},
    {.bit = {.sign = 1, .exp = 2, .mantissa = {532941407, 2844775614, 0}}},
    {.bit = {.sign = 1, .exp = 2, .mantissa = {532941405, 2844775614, 0}}},
    {.bit = {.sign = 0, .exp = 3, .mantissa = {123456789, 0, 0}}},
    {.bit = {.sign = 0, .exp = 9, .mantissa = {123456789, 0, 0}}},
    {.bit = {.sign = 0, .exp = 18, .mantissa = {123456789, 0, 0}}},
    {.bit = {.sign = 0, .exp = 27, .mantissa = {123456789, 0, 0}}},
    {.bit = {.sign = 0, .exp = 6, .mantissa = {4294967295, 0, 0}}},
    {.bit = {.sign = 0, .exp = 5, .mantissa = {4294967295, 4294967295, 0}}},
    {.bit = {.sign = 1, .exp = 27, .mantissa = {123456789, 0, 0}}},
    {.bit = {.sign = 1, .exp = 6, .mantissa = {4294967295, 0, 0}}},
    {.bit = {.sign = 0,
             .exp = 28,
             .mantissa = {4294967295, 4294967295, 4294967295}}},
    {.bit = {.sign = 1, .exp = 5, .mantissa = {4294967295, 4294967295, 0}}},
    {.bit = {.sign = 1,
             .exp = 28,
             .mantissa = {4294967295, 4294967295, 4294967295}}},
    {.bit = {.sign = 1, .exp = 182, .mantissa = {0, 0, 3485864704}}}};

static s21_decimal neg[] = {
    {.bit = {.sign = 0, .exp = 15, .mantissa = {0, 15, 35}}},
    {.bit = {.sign = 1, .exp = 15, .mantissa = {0, 15, 35}}},
    {.bit = {.sign = 0, .oversize = 1, .exp = 15, .mantissa = {0, 15, 35}}},
    {.bit = {.sign = 0, .oversize = 1, ._void = 1, .mantissa = {0, 15, 35}}},
    {.bit = {.sign = 0, .exp = 15, ._void = 1, .mantissa = {0, 15, 35}}}};

START_TEST(dcml_neg) {
  s21_decimal res;
  int err = s21_negate(neg[_i], &res);

  if (err)
    for (int i = 0; i < 4; i++) ck_assert_int_eq(res.bits[i], 0);
  else
    ck_assert_int_eq(res.bit.sign, ~(neg[_i].bit.sign));
}
END_TEST

static s21_decimal truncate_res[] = {
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2172188218, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2181821, 0, 0}}},
    {.bit = {.sign = 0,
             .exp = 0,
             .mantissa = {4294967295, 4294967295, 4294967295}}},
    {.bit = {.sign = 1,
             .exp = 0,
             .mantissa = {4294967295, 4294967295, 4294967295}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {10000, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {10000, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {52398601, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1127, 122, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {3435973949, 429496741, 1282}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {3178275810, 515396076, 21217}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {3006477117, 429496729, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {14, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {15, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {100000, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {13, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {14, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {606624835, 28447756, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {606624835, 28447756, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {606624835, 28447756, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {606624835, 28447756, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {123456, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {4294, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2890341191, 42949, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {4294, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {7, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2890341191, 42949, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {7, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}}};

START_TEST(dcml_truncate) {
  s21_decimal res;
  int err = s21_truncate(neg[_i], &res);

  for (int j = 0; j < 4; j++)
    if (err)
      ck_assert_int_eq(res.bits[j], 0);
    else
      ck_assert_int_eq(res.bits[j], truncate_res[_i].bits[j]);
}
END_TEST

static s21_decimal round_res[] = {
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2172188218, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2181821, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {10000, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {10000, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {52398601, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {3435973950, 429496741, 1282}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {3178275810, 515396076, 21217}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {3006477117, 429496729, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {3, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {3, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {3, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {3, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {14, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {15, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {606624836, 28447756, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {606624835, 28447756, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {606624836, 28447756, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {606624835, 28447756, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {123457, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {4295, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2890341192, 42949, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {4295, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {8, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2890341192, 42949, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {8, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
};

START_TEST(dcml_round) {
  s21_decimal res;

  int err = s21_round(neg[_i], &res);

  for (int j = 0; j < 4; j++)
    if (err)
      ck_assert_int_eq(res.bits[j], 0);
    else
      ck_assert_int_eq(res.bits[j], round_res[_i].bits[j]);
}
END_TEST

static s21_decimal floor_res[] = {
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2172188218, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2181822, 0, 0}}},
    {.bit = {.sign = 0,
             .exp = 0,
             .mantissa = {4294967295, 4294967295, 4294967295}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {10000, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {10001, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {52398601, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1128, 122, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {3435973949, 429496741, 1282}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {3178275811, 515396076, 21217}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {3006477118, 429496729, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {14, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {16, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {100000, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {3, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {3, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {3, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {13, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {14, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {606624835, 28447756, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {606624835, 28447756, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {606624836, 28447756, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {606624836, 28447756, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {123456, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {4294, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {2890341191, 42949, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {1, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {4295, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {7, 0, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {2890341192, 42949, 0}}},
    {.bit = {.sign = 1, .exp = 0, .mantissa = {8, 0, 0}}},
    {.bit = {.sign = 0, .exp = 0, .mantissa = {0, 0, 0}}},
};

START_TEST(dcml_floor) {
  s21_decimal res;

  int err = s21_floor(neg[_i], &res);

  for (int j = 0; j < 4; j++)
    if (err)
      ck_assert_int_eq(res.bits[j], 0);
    else
      ck_assert_int_eq(res.bits[j], floor_res[_i].bits[j]);
}

END_TEST

Suite *suite_negative(void) {
  Suite *s;
  TCase *tc_s21_negative;
  s = suite_create("s21_negative");
  tc_s21_negative = tcase_create("s21_negative");

  tcase_add_loop_test(tc_s21_negative, dcml_neg, 0, 4);

  suite_add_tcase(s, tc_s21_negative);

  return s;
}

Suite *suite_truncate(void) {
  Suite *s;
  TCase *tc_s21_decimal_truncate;
  s = suite_create("s21_truncate");
  tc_s21_decimal_truncate = tcase_create("s21_truncate");

  tcase_add_loop_test(tc_s21_decimal_truncate, dcml_truncate, 0,
                      sizeof(a) / sizeof(s21_decimal));

  suite_add_tcase(s, tc_s21_decimal_truncate);

  return s;
}

Suite *suite_round(void) {
  Suite *s;
  TCase *tc_s21_decimal_round;
  s = suite_create("s21_round");
  tc_s21_decimal_round = tcase_create("s21_round");

  tcase_add_loop_test(tc_s21_decimal_round, dcml_round, 0,
                      sizeof(a) / sizeof(s21_decimal));

  suite_add_tcase(s, tc_s21_decimal_round);

  return s;
}

Suite *suite_floor(void) {
  Suite *s;
  TCase *tc_s21_decimal_floor;
  s = suite_create("s21_floor");
  tc_s21_decimal_floor = tcase_create("s21_floor");

  tcase_add_loop_test(tc_s21_decimal_floor, dcml_floor, 0,
                      sizeof(a) / sizeof(s21_decimal));

  suite_add_tcase(s, tc_s21_decimal_floor);

  return s;
}

int test_other() {
  int failed_count = 0;
  SRunner *suiteRunner;

  suiteRunner = srunner_create(suite_negative());
  srunner_run_all(suiteRunner, CK_NORMAL);
  failed_count += srunner_ntests_failed(suiteRunner);
  srunner_free(suiteRunner);

  suiteRunner = srunner_create(suite_truncate());
  srunner_run_all(suiteRunner, CK_NORMAL);
  failed_count += srunner_ntests_failed(suiteRunner);
  srunner_free(suiteRunner);

  suiteRunner = srunner_create(suite_round());
  srunner_run_all(suiteRunner, CK_NORMAL);
  failed_count += srunner_ntests_failed(suiteRunner);
  srunner_free(suiteRunner);

  suiteRunner = srunner_create(suite_floor());
  srunner_run_all(suiteRunner, CK_NORMAL);
  failed_count += srunner_ntests_failed(suiteRunner);
  srunner_free(suiteRunner);

  return (failed_count == 0) ? 0 : 1;
}