#include "allergies.h"

// the maximum valid allergy score (allergic to everything!)
#define MAX_SCORE 256


/// @brief the different allergy score values
const int ALLERGY_SCORES[ALLERGEN_COUNT] = {1, 2, 4, 8, 16, 32, 64, 128};


/// @brief based on a score, will calculate if a score indicates an allergy to a chosen allergen
/// @param allergen the allergen to check for 
/// @param score the score to check
/// @return whether or not the score value indicates an allergy to the chosen allergen
bool is_allergic_to(allergen_t allergen, int score)
{
    allergen_list_t list = get_allergens(score);
    return list.allergens[allergen];
}


/// @brief calculates the allergy matrix for a numerical allergen score
/// @param score the total allergy score
/// @return completed and processed allergy list
allergen_list_t get_allergens(int score)
{
    allergen_list_t list = get_blank_list();
    calculate_allergens(&list, score);
    return list;
}


/// @brief generates a blank allergen_list t struct
/// @return an alergen_list struct
allergen_list_t get_blank_list(void)
{
    allergen_list_t list;
    list.count = 0;

    for (int i = 0; i < ALLERGEN_COUNT; i++)
        list.allergens[i] = false;

    return list;
}


/// @brief Given a blank allergen_list and a score, will calculate allergens
/// @param list the blank allergen_list_t struct
/// @param score the numerical allergy score
void calculate_allergens(allergen_list_t *list, int score)
{
    score %= MAX_SCORE;

    for (int i = ALLERGEN_COUNT - 1; i >= 0; i--)
        if (score - ALLERGY_SCORES[i] >= 0) {
            list->allergens[i] = true;
            list->count++;
            score -= ALLERGY_SCORES[i];
        }
}