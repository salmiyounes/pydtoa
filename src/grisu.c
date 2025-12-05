#include <stdio.h>
#include <stdbool.h>
#include "grisu.h"

#define TEN7 10000000 // 10 ** 7

void cut(diy_fp D, binary32 parts[3]) {
    parts[2] = (D.f % (TEN7 >> D.e)) << D.e;
    binary64 tmp = D.f / (TEN7 >> D.e);
    parts[1] = tmp % TEN7;
    parts[0] = tmp / TEN7;
}

void grisu(double v, char* buffer) {
    diy_fp w; binary32 parts[3];
    int q = 64, alpha = 0, gamma = 3;
    w = diy_fp_normalize(binary642diy_fp(v));
    int mk = k_comp(w.e + q, alpha, gamma);
    diy_fp c_mk = get_cached_power(mk);
    diy_fp D = multiply(w, c_mk);
    cut(D, parts);
    sprintf(buffer, "%u%07u%07ue%d", parts[0], parts[1], parts[2], -mk);
}

char *dtoa(double value, char *buffer) {
    binary64 d;
    DOUBLE_TO_BITS(d, value);
    bool sign = !!extract_sign(d);
    if (is_zero(d)) {
        if (sign) 
            *buffer++ = '-';
        buffer[0] = '0';
        buffer[1] = '.';
        buffer[2] = '0';
        return buffer;
    }
    else {
        if (sign) {
            *buffer++ = '-';
            value *= -1; // Get rid of the sign
        }
        grisu(value, buffer);
        return buffer;
    }
}