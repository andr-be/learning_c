// WORD REVERSER
// andr-be 07/2023
/*
    reverses the words in a sentence
    > Enter a sentence: you can cage a swallow can't you?
    > Reversal of sentence: you can't swallow a cage can you?
    
    read characters one by one and store them in a one-dimensional array
    have the loop stop at terminating character, save in separate ch variable
    use second loop to search backwards to beginning of last word
    print the last word, then search backward for the next to last word
    repeat until the beginning of the array is reached
    print the terminating character
*/
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define STR_LEN 20
#define MAX_WORDS 30 
#define BUFF_SIZE STR_LEN * MAX_WORDS

bool isnewline(char c);
void reverse_words(char* buffer);

int main(void)
{
    char *buffer = calloc(BUFF_SIZE, sizeof(char));

    printf("Enter a sentence: ");
    fgets(buffer, BUFF_SIZE, stdin);
    reverse_words(buffer);

    free(buffer);
    return 0;
}

bool isnewline(char c)
{
    return c == '\n';
}

void reverse_words(char* buffer)
{
    char word_grid[MAX_WORDS][STR_LEN] = {0};
    char terminator = '\0';
    int word = 0, 
        character = 0;

    while(*buffer) 
    {
        if(isalpha(*buffer)) 
            word_grid[word][character++] = *buffer;

        else if(isspace(*buffer)) { 
            word_grid[word++][character] = '\0'; 
            character = 0; 
        }

        else if(isnewline(*buffer))
            if(ispunct(*(buffer - 1)))
                terminator = *(buffer - 1);
    
        buffer++;    
    }

    for (int i = word - 1; i >= 0; i--)
        printf("%s ", word_grid[i]);

    putchar('\b');
    putchar(terminator);
}