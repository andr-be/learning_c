#ifndef SIEVE_H
#define SIEVE_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/// @brief Finds all the prime numbers between 0 and a given limit
/// @param limit the number to filter up to, inclusive
/// @param primes an empty array with enough space for max_prime integers
/// @param max_primes the maximum number of primes the program will return
/// @return the total number of found primes
uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes);

#endif
