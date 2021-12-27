#ifndef PRIMES_H
#define PRIMES_H

#include "primes_global.h"

PRIMES_EXPORT void gen_prime_array(int *arr, size_t sz);
PRIMES_EXPORT void inject_number(const int *src, size_t src_sz, int number, int *dst);

#endif // PRIMES_H
