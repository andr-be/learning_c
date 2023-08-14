// WORD REVERSER 2
// andr-be 08/2023
/*
    reverses the words in a sentence
    > Enter a sentence: you can cage a swallow can't you?
    > Reversal of sentence: you can't swallow a cage can you?
    
    uses pointer arithmetic to do things instead of  array subscripting
*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 1024

char *get_user_string(void);
void reverse_sentence(char* string);

int main(void)
{
    char *sentence = get_user_string();
    reverse_sentence(sentence);
    return 0;
}

char *get_user_string(void)
{
    char* buffer = calloc(BUFF_SIZE, sizeof(char));
    printf("Enter a sentence: ");
    fgets(buffer, BUFF_SIZE-1, stdin);
    return buffer;
}

void reverse_sentence(char* string)
{
    size_t len = strlen(string);
    char *tail = string + len - 1,
         *head = tail - 1,
         terminator;

    if (*head == '.' || *head == '?' || *head == '!')
        terminator = *head;

    while (tail >= string)
    {
        if (tail != string + len - 1) 
            putchar(' ');

        for (head = tail - 1; *head != ' ' && head >= string; head--) 
            ;

        for (; head < tail; head++) 
            if (isalpha(*head)) printf("%c", *head);

        for (tail = head - 1; *tail != ' ' && tail >= string; tail--)
            ;
    }

    if (terminator) printf("%c\n", terminator);
}