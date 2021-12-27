#include "primes.h"

PRIMES_EXPORT void gen_prime_array(int *arr, size_t sz)
{
    int cur_prime = 1;

    for (int i = 0; i < sz; i++)
    {
        int is_prime;

        do
        {
            cur_prime++;
            is_prime = 1;
            for (int j = 0; j < i && is_prime && arr[j] * arr[j] <= cur_prime; j++)
                is_prime = cur_prime % arr[j];
        }
        while (!is_prime);
        arr[i] = cur_prime;
    }
}

PRIMES_EXPORT void inject_number(const int *src, size_t src_sz, int number, int *dst)
{
    for (int i = 0; i < src_sz; i++)
    {
        dst[(i << 1)] = src[i];
        dst[(i << 1) + 1] = number;
    }
}
