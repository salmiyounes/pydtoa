#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "utils.h"


inline bool test_bit(uint64_t s, int i) {
    return (bool) (s & bit(i));
}

inline uint64_t bit(int i) {
    return (U64(1) << i);
}

inline int clzll(uint64_t s) {
    assert(s != 0);
#if (defined(__GNUC__))
    return __builtin_clzll(s);
#else
    // naive version
    uint32_t r = 0;
    while (!test_bit(s, 63)) {
        s <<= 1;
        ++r;
    }

    return r;
#endif
}
