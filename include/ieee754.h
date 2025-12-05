#ifndef IEEE754_H
#define IEEE754_H

#include <stdint.h>
#include "diy_fp.h"

typedef union  {
    binary64 u;
    double   f;
} ieee754_double; // IEEE 754 double-precision floating-point number

#define DOUBLE_TO_BITS(result, value)           \
    do {                                        \
        ieee754_double temp = {.f = value};     \
        result  = temp.u;                       \
    } while(0)

#define BITS_TO_DOUBLE(result, value)           \
    do {                                        \
        ieee754_double temp = {.u = value};     \
        result  = temp.f;                       \
    } while(0)


/* Helper Funtions */
bool is_zero(binary64 f);

int extract_exp(binary64 f);

binary64 extract_significand(binary64 f);

int extract_sign(binary64 f);

diy_fp binary642diy_fp(const double d);

#endif // IEEE754_H