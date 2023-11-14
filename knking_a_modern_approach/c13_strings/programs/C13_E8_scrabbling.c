// Chapter 13 - Exercise 8 - Scrabble Redux
// andr-be 11/2023 

#include <stdio.h>
#include <ctype.h>
#define BUFF_SIZE 80 

int score_from_char(char);
int compute_scrabble_value(const char *word);

int main(void)
{
    char input[BUFF_SIZE];    

    printf("Enter a word: ");
    scanf("%s", input);
    
    int sum = compute_scrabble_value(input);

    printf("Scrabble value: %3d", sum);
    return 0;
}

int score_from_char(char letter) {
    switch (toupper(letter))
    {
    case 'A': case 'E': case 'I': case 'L': case 'N': 
    case 'O': case 'R': case 'S': case 'T': case 'U': return 1;
    case 'D': case 'G':                               return 2;
    case 'B': case 'C': case 'M': case 'P':           return 3;
    case 'F': case 'H': case 'V': case 'W': case 'Y': return 4;
    case 'K':                                         return 5;
    case 'J': case 'X':                               return 8;
    case 'Q': case 'Z':                               return 10;
    default:                                          return 0;
    }
}

int compute_scrabble_value(const char *word)
{
    int sum;
    for (sum = 0; *word; word++) {
        sum += score_from_char(*word);
    }
    return sum;
}