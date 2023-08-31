#include "sieve.h"

#define MAX_LIM 10000

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    uint32_t *number_list = malloc((limit + 1) * sizeof(uint32_t));

    for (uint32_t i = 0; i <= limit; i++)
        number_list[i] = i;

    uint32_t prime_count = 0;
    for (uint32_t j = 0; j <= limit; j++)
    {
        if (prime_count > max_primes) 
            break;

        if (number_list[j] == 1 || number_list[j] == 0) 
            continue;

        primes[prime_count++] = number_list[j];

        for (uint32_t k = 2; j*k <= limit; k++)
            number_list[j * k] = 0;
    }
    free(number_list);
    return prime_count;
}

int main(void)
{
    uint32_t primes[MAX_LIM] = {0},
             limit = MAX_LIM,
             max_primes = MAX_LIM,
             count = sieve(limit, &primes[0], max_primes);

    for (uint32_t i = 0; primes[i] != 0; i++)
        printf("PRIME %d: %d\n", i + 1, primes[i]);

    printf("\n\nTOTAL PRIMES GENERATED: %d\n", count);

    return 0;
}