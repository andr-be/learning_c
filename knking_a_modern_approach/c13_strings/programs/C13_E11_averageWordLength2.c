// AVERAGE WORD LENGTH CALCULATOR
// andr-be 07/2023
/*
    Calculates the average word length for a given sentence.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

double compute_average_word_length(const char *sentence);

int main(void)
{
    double average = 0;
    char sentence[1024] = {0};

    printf("Enter a sentence: ");
    fgets(sentence, 1024, stdin);
    compute_average_word_length(sentence);
    
    return 0;
}

double compute_average_word_length(const char *sentence)
{
    int letters = 0,
        words = 1;

    for (; *sentence; sentence++) {
        if (isalpha(*sentence)) 
            letters++;
        else if (isspace(*sentence))
            words++;
    }

    double average = (double) letters / (double) words;

    printf("LETTERS:\t%d\nWORDS:\t\t%d\n", letters, words);
    printf("AVG LENGTH:\t%3.2f LETTERS", average);

    return average;
}