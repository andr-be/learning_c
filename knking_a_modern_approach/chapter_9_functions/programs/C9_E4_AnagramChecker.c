// ANAGRAM TESTER
// andre-be 07/2023
/*
    modify this program so that it includes the following functions:
     - void read_word(int counts[26]);
     - bool equal_array(int counts1[26], int counts2[26]);
*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFF_S 64
#define ALPHA_S 26

void read_word(int counts[26]);
bool equal_array(int counts_1[26], int counts_2[26]);

int main(void)
{
    int w1_count[ALPHA_S] = {0},
        w2_count[ALPHA_S] = {0};

    read_word(w1_count);
    read_word(w2_count);

    if (equal_array(w1_count, w2_count)) 
        printf("These two words are anagrams.\n");
    else 
        printf("These two words are not anagrams.\n");
    
    return 0;
}

void read_word(int counts[26]){
    char word[BUFF_S];
    
    printf("Enter a word: ");
    fgets(word, BUFF_S, stdin);

    for (int i = 0; i < BUFF_S && word[i] != '\n'; i++)
        counts[tolower(word[i]) - 'a'] += 1;
}

bool equal_array(int counts_1[26], int counts_2[26]){
    for (int i = 0; i < ALPHA_S; i++)
        if (counts_1[i] != counts_2[i]) 
            return false;

    return true;
}
