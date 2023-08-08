// SCRABBLE SCORER
// andr-be 07/2023
/*
    Calculates the baseline score for a word in scrabble based on face values.
    pitfall == 12
*/

#include <stdio.h>
#define BUFF_SIZE 80 

int score_from_char(char);

int main(void)
{
    char input[BUFF_SIZE];    
    int sum;

    printf("Enter a word: ");
    scanf("%s", input);
    
    for (int i = 0; i < BUFF_SIZE; i++){
        if (input[i] == '\0') break;
        sum += score_from_char(input[i]);
    }
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