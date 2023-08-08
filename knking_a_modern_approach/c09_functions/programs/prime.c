// PRIME FINDER
// andr-be 07/2023
/*
    Generates a number
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>

bool is_prime(int64_t n)
{
    int64_t divisor;

    if (n <= 1)
        return false;
    for (divisor = 2; divisor * divisor <= n; divisor++)
        if (n % divisor == 0)
            return false;
    return true;
}

int main(void)
{
    puts("PRIME FINDER\nPrimes to find: ");
    char input[10]; 
    fgets(input, 9, stdin);

    int increment = atoi(input);
    for(int64_t prime_candidate = 0, prime_idx = 1; prime_candidate < INT64_MAX; prime_candidate++)
    {
        if(is_prime(prime_candidate)) { 
            printf("Prime %I64d:\t%I64d\n", prime_idx, prime_candidate); 

            if(prime_idx % increment == 0) {
                printf("\nGenerate primes? (y/n):  ");
                char more = (char) getchar();
                fflush(stdin);
                if (more == 'n') break; 
            }

            prime_idx++;
        }
    }
    printf("Thanks for finding primes!");

    return 0;
}
