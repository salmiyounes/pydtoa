#include <math.h>
#include "k_comp.h"

#define D_1_LOG2_10 0.30102999566398114 // 1/lg(10)

int k_comp(int e, int alpha, int gamma) {
    return ceil((alpha-e+63) * D_1_LOG2_10);
}