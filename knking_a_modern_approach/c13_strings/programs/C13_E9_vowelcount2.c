// Chapter 13 - Exercise 9 - vowelcount2.c
// andr-be 11/2023
/*
    uses a string approach instead of the getchar method.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFF_SIZE 96

bool is_vowel(char input) {
    switch (toupper(input))
    {
        case 'A': case 'E': case 'I': case 'O': case 'U':
            return true;
        default:
            return false;
    }
}

int main(void)
{
    char input[BUFF_SIZE];
    int vowel_sum = 0;
    printf("Enter a sentence: ");

    fgets(input, BUFF_SIZE, stdin);

    for (char *i = input; *i; i++)
        if (is_vowel(*i))
            vowel_sum++;

    printf("total vowels: %d\n", vowel_sum);
    return 0;
}
