#ifndef DIY_FP_H
#define DIY_FP_H

#include <stdint.h>
#include <assert.h>
#include "utils.h"

typedef uint64_t binary64; // Double precision 
typedef uint32_t binary32; // Single precision

typedef struct diy_fp {
    binary64    f; // unsigned q-bit integer fx (mantissa)
    int         e; // signed integer ex (exponent)
} diy_fp;

/* Operations */

diy_fp diy_fp_normalize(diy_fp x);

diy_fp minus(diy_fp x, diy_fp y);

diy_fp multiply(diy_fp x, diy_fp y);

#endif // DIY_FP_H