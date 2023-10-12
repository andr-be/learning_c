#include "allergies.h"

#define MAX_SCORE 256

const int ALLERGY_SCORES[ALLERGEN_COUNT] = {1, 2, 4, 8, 16, 32, 64, 128};

bool is_allergic_to(allergen_t allergen, int score)
{
    allergen_list_t list = get_allergens(score);
    return list.allergens[allergen];
}

allergen_list_t get_allergens(int score)
{
    score %= MAX_SCORE;
    allergen_list_t list;
    
    list.count = 0;
    for (int i = 0; i < ALLERGEN_COUNT; i++) 
        list.allergens[i] = false;

    for (int j = ALLERGEN_COUNT - 1; j >= 0; j--)
        if (score - ALLERGY_SCORES[j] >= 0) {
            list.allergens[j] = true;
            list.count++;
            score -= ALLERGY_SCORES[j];
        }

    return list;
}