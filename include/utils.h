#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>

#define CONCAT(x, y) x##y
#define U64(x) CONCAT(x, ULL)
#define ABS(x) ((x) < 0 ? -(x) : (x))

bool test_bit(uint64_t s, int i);
uint64_t bit(int i);
int clzll(uint64_t s);

#endif //UTILS_H