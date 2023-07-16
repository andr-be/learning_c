// ANAGRAM TESTER
// andre-be 07/2023
/*
    tests whether two words are anagrams;
    i.e. they have the same number of the same letters
*/

#include <stdio.h>
#include <ctype.h>

#define BUFF_S 32
#define ALPHA_S 26

int main(void)
{
    char word_1[BUFF_S],
         word_2[BUFF_S];

    int w1_count[ALPHA_S] = {0},
        w2_count[ALPHA_S] = {0};

    printf("Enter first word: ");
    fgets(word_1, BUFF_S, stdin);
    for (int i = 0; i < BUFF_S && word_1[i] != '\n'; i++)
        w1_count[tolower(word_1[i]) - 'a'] += 1;

    printf("Enter second word: ");
    fgets(word_2, BUFF_S, stdin);
    for (int j = 0; j < BUFF_S && word_2[j] != '\n'; j++)
        w2_count[tolower(word_2[j]) - 'a'] += 1;

    for (int k = 0; k < ALPHA_S; k++) {
        if (w1_count[k] != w2_count[k]) { printf("The words are not anagrams."); break; }
        if (k == ALPHA_S - 1) printf("The words are anagrams.");
    }

    return 0;
}
