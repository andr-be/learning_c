#ifndef PYTHAGOREAN_TRIPLET_H
#define PYTHAGOREAN_TRIPLET_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct triplet_t {
    uint16_t a;
    uint16_t b;
    uint16_t c;
} triplet_t;

typedef struct triplets_t {
    size_t count;
    triplet_t triplets[];
} triplets_t;

triplets_t *triplets_with_sum(uint16_t sum);
void free_triplets(triplets_t *triplets);
bool is_valid(uint16_t a, uint16_t b, uint16_t c, uint16_t sum);
bool is_same(triplet_t a, triplet_t b);
bool is_duplicate(triplet_t entry, triplets_t *list);
void test_case(uint16_t test_sum);
void test_all(void);

#endif