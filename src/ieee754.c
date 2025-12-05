#include <stdint.h>
#include <stdbool.h>
#include "diy_fp.h"
#include "ieee754.h"
#include "utils.h"

/* Macros */
#define DP_SIZE 64
#define DP_SIGNIFICAND_SIZE 52
#define DP_EXPONENT_BIAS (0x3FF + DP_SIGNIFICAND_SIZE)
#define DP_MIN_EXPONENT (-DP_EXPONENT_BIAS)
#define DP_EXPONENT_MASK 0x7FF0000000000000
#define DP_SIGNIFICAND_MASK 0x000FFFFFFFFFFFFF
#define DP_HIDDEN_BIT    0x0010000000000000 // 2 ** 52


/* Helper Funtions */
inline bool is_zero(binary64 f) {
    return (f & ~(bit(DP_SIZE - 1))) == 0;
}

inline  int extract_exp(binary64 f) {
    return (f & DP_EXPONENT_MASK) >> DP_SIGNIFICAND_SIZE;
}

inline binary64 extract_significand(binary64 f) {
    return (f & DP_SIGNIFICAND_MASK);
}

inline int extract_sign(binary64 f) {
    return (int)(f >> (DP_SIZE - 1));
}

diy_fp binary642diy_fp(const double d) {
    binary64 d64, f_v, f_b64;
    int e_b64, e_v;
    DOUBLE_TO_BITS(d64, d);

    e_b64 = extract_exp(d64); // Extract biased exponent 
    f_b64 = extract_significand(d64);
    
    //FIXME: handle the case where the number is INF OR -INF, NAN 
    assert(e_b64 != U64(0x7FF));

    if (e_b64 != 0) {
        f_v = DP_HIDDEN_BIT + f_b64;
        e_v = e_b64 - DP_EXPONENT_BIAS;
    } else { // Handle subnormal numbers
        f_v = f_b64;
        e_v = 1 - DP_EXPONENT_BIAS;
    }

    return (diy_fp) {.e= e_v, .f= f_v};
}
