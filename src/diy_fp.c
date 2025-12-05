#include <stdint.h>
#include <assert.h>
#include "diy_fp.h"
#include "utils.h"

/* Operations */

diy_fp diy_fp_normalize(diy_fp x) {
    int s = clzll(x.f);
    return (diy_fp) {.f= x.f << s, .e = x.e - s};
}

diy_fp minus(diy_fp x, diy_fp y) {
    assert(x.e == y.e && x.f >= y.f);
    diy_fp r = {
        .f = x.f - y.f,
        .e = x.e
    };
    return r;
}

diy_fp multiply(diy_fp x, diy_fp y) {
    binary64 a,b,c,d,ac,bc,ad,bd,tmp;
    diy_fp r; binary64 M32 = U64(0xFFFFFFFF);
    a = x.f >> 32; b = x.f & M32;
    c = y.f >> 32; d = y.f & M32;
    ac = a*c; bc = b*c; ad = a*d; bd = b*d;
    tmp = (bd>>32) + (ad&M32) + (bc&M32);
    tmp += 1U << 31; /// mult_round
    r.f = ac+(ad>>32)+(bc>>32)+(tmp >>32);
    r.e = x.e + y.e + 64;
    return r;
}
