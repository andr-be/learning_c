// VOWEL COUNTER
// andr-be 07/2023
/*
    Uses the getchar while-loop idiom to count all of
    the vowels present in a user determined sentence
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFF_SIZE 80

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
    char input;
    int vowel_sum = 0;
    printf("Enter a sentence: ");

    do {
        input = getchar();
        if (is_vowel(input)) vowel_sum += 1;
    } while (input != '\n');

    printf("total vowels: %d\n", vowel_sum);
    return 0;
}
