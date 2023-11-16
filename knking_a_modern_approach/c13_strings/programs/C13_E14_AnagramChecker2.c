// ANAGRAM TESTER
// andre-be 07/2023
/*
    tests whether two words are anagrams;
    i.e. they have the same number of the same letters
*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define BUFF_S 32
#define ALPHA_S 26

bool are_anagrams(const char *word1, const char *word2);
int count_letters(const char *word, int letters[ALPHA_S]);
bool compare_counts(int x[ALPHA_S], int y[ALPHA_S]);

int main(void)
{
    char word_1[BUFF_S],
         word_2[BUFF_S];

    printf("Enter first word: ");
    fgets(word_1, BUFF_S, stdin);

    printf("Enter second word: ");
    fgets(word_2, BUFF_S, stdin);

    if (are_anagrams(word_1, word_2))
        printf("These two words are anagrams!\n");
    else
        printf("These two words are not anagrams.\n");

    return 0;
}

/// @brief compares two words to see if they are anagrams of each other
/// @param word1 the first word
/// @param word2 the second word
/// @return true if the two words are anagrams
bool are_anagrams(const char *word1, const char *word2)
{
    if (strlen(word1) != strlen(word2)) 
        return false;

    int letter_count_1[ALPHA_S] = {0},
        letter_count_2[ALPHA_S] = {0};
    
    count_letters(word1, letter_count_1);
    count_letters(word2, letter_count_2);

    return compare_counts(letter_count_1, letter_count_2);
}

/// @brief checks word and adds up the letters found in letters
/// @param word the word to count letters in
/// @param letters the array of letter totals
/// @return the total number of letters in the word
int count_letters(const char *word, int letters[ALPHA_S])
{
    int sum = 0;
    while(*word) {
        if (isalpha(*word)) {
            letters[tolower(*word) - 'a']++;
            sum++;
        }
        word++;
    }
    return sum;
}

/// @brief compares two arrays of letter counts
/// @param x the first array
/// @param y the second array
/// @return true if the arrays are identical
bool compare_counts(int x[ALPHA_S], int y[ALPHA_S])
{
    for (int i = 0; i < ALPHA_S; i++)
        if (x[i] != y[i])
            return false;

    return true;
}