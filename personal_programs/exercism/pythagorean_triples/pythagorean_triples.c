#include "pythagorean_triples.h"

// 12:        3,   4,   5
// 108:      27,  36,  45
// 1000:    200, 375, 425


int main(void)
{
    //test_all();
    test_case(12);
    test_case(36);
    test_case(108);
    test_case(840);
    test_case(1000);
    return 0;
}

triplets_t *triplets_with_sum(uint16_t sum)
{
    size_t max_size = sum / 2;
    triplets_t *result = malloc(sizeof(triplets_t) + sizeof(triplet_t) * max_size);
    if (!result || !sum) return NULL;

    result->count = 0;

    for (uint16_t m = 1; m <= sum; m++) {
        for (uint16_t n = 1; n < m; n++) 
        {
            // generate primitive triplet
            uint16_t a = (m * m) - (n * n),
                     b = (m * n) + (m * n),
                     c = (m * m) + (n * n),
                     working_sum = a + b + c;

            if (working_sum > sum) return result;

            // check primitive and composite triplets
            for (uint16_t k = 1; k * working_sum <= sum; k++) 
            {
                // generate composite triplet by multiplying each side by k (which increments)
                uint16_t n_a = a * k,
                         n_b = b * k,
                         n_c = c * k;

                // check this is a valid solution
                if (is_valid(n_a, n_b, n_c, sum)) 
                {   
                    // if it is, turn it into a triplet struct
                    triplet_t new_triplet = {n_a, n_b, n_c};
                    // check the triplet structure is not a duplicate
                    if (is_duplicate(new_triplet, result)) continue;
                    // then add it to the end of the list if it's unique
                    result->triplets[result->count++] = new_triplet;   
                }
            }
        }
    }
    return result;
}

void free_triplets(triplets_t *triplets)
{
    free(triplets);
}

bool is_valid(uint16_t a, uint16_t b, uint16_t c, uint16_t sum)
{
    return a < b && a < c && b < c && a + b + c == sum;
}

void test_all(void)
{
    uint16_t test_cases[] = {
        12, 108, 1000, 1001, 90, 840, 30000, 36
    };

    size_t total_tests = sizeof(test_cases) / sizeof(uint16_t);

    for (size_t i = 0; i < total_tests; i++) {
        test_case(test_cases[i]);
    }
}

void test_case(uint16_t test_sum)
{
    triplets_t *new = triplets_with_sum(test_sum);
    if (new->count) {
        for (uint16_t j = 0; j < new->count; j++)
            printf("%5d: %5d, %5d, %5d\n", test_sum, new->triplets[j].a, new->triplets[j].b, new->triplets[j].c);
    }
    else printf("%5d: NO VALID TRIPLETS\n", test_sum);
}

bool is_same(triplet_t a, triplet_t b)
{
    return a.a == b.a 
        && a.b == b.b 
        && a.c == b.c;
}

bool is_duplicate(triplet_t entry, triplets_t *list)
{
    if (!list->count) return false;

    for (size_t i = 0; i < list->count; i++)
        if (is_same(list->triplets[i], entry)) return true;
    
    return false;
}