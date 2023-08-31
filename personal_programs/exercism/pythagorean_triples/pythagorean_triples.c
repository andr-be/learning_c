#include "pythagorean_triples.h"

// 12:        3,     4,     5
// 108:      27,    36,    45
// 1000:    200,   375,   425
// 30000:  1200, 14375, 14425
//         1875, 14000, 14125 
//         5000, 12000, 13000 
//         6000, 11250, 12750 
//         7500, 10000, 12500

#define BIG_SUM 500

int main(void)
{
    test_all();
    return 0;
}

triplets_t *triplets_with_sum(uint16_t sum)
{
    size_t max_size = (sum < BIG_SUM) ? sum / 2 : BIG_SUM / 2;
    triplets_t *result = malloc(sizeof(triplets_t) + sizeof(triplet_t) * max_size);
    if (!result || !sum) return NULL;

    result->count = 0;

    for (int m = 2; m <= (int) max_size; m++) {
        for (int n = 1; n < m; n++) 
        {
            // generate primitive triplet
            int a = (m * m) - (n * n),
                b = (m * n) + (m * n),
                c = (m * m) + (n * n),
                test_sum = a + b + c;

            if (test_sum > sum) break;

            // check primitive and composite triplets
            for (int k = 1; k * test_sum <= sum; k++) 
            {
                // generate composite triplet by multiplying each side by k (which increments)
                uint16_t n_a = (uint16_t) a * k,
                         n_b = (uint16_t) b * k,
                         n_c = (uint16_t) c * k;

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

bool is_valid(int a, int b, int c, uint16_t sum)
{
    int _sum = (int) sum;
    
    return b < c && a < c
        && a + b + c == _sum
        && (a * a) + (b * b) - (c * c) == 0;
}

bool is_same(triplet_t a, triplet_t b)
{
    return ((a.c == b.c) 
        && ((a.a == b.a && a.b == b.b) 
        ||  (a.a == b.b && a.b == b.a)));
}

bool is_duplicate(triplet_t entry, triplets_t *list)
{
    if (!list->count) return false;

    for (size_t i = 0; i < list->count; i++)
        if (is_same(list->triplets[i], entry)) return true;
    
    return false;
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