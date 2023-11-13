// Chapter 13 - Exercise 1 - Wordsorter
// andr-be 11/2023
/*
    sorts a selection of input words into 'smallest' and 'largest'
    as determined by an alphabetical ordering
    i.e. cat < dogs < xylophone < zoo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void word_sort(char *smallest, char *largest, int word_count)
{
    for (int i = 0; i < word_count; i++) {
        char new_word[20];
        printf("Enter word: ");
        scanf("%s", new_word);
        
        if (!*smallest) {
            strcpy(smallest, new_word);
            continue;
        } 
        else if (strcmp(smallest, new_word) > 0) {
            strcpy(smallest, new_word);
        } 
        else if (strcmp(largest, new_word) < 0) {
            strcpy(largest, new_word);
        }
    }
}

int main(int argc, char const *argv[])
{
    char smallest[20] = {0},
         largest[20] = {0};

    int word_count = 5;

    if (argc == 2) 
        word_count = atoi(argv[1]);

    word_sort(smallest, largest, word_count);

    printf("Smallest word: %s\n", smallest);
    printf("Largest word: %s\n", largest);

    return 0;
}
