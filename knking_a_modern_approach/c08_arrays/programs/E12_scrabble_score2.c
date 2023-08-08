// SCRABBLE SCORER 2: ARRAY OF HOPE
// andr-be 07/2023
/*
    modified so that the values of the letters are stored in an array
    the array will have 26 elements for each letter of the alphabet
    e.g. a[0] will store 1 because 'A' is worth 1 point
         a[1] will store 3 because 'B' is worth 3 points
*/

#include <stdio.h>
#include <ctype.h>

#define BUFF_SIZE 80 

int score_from_array(char);

const int SCORES[26] = {
    1, 3, 3, 2, 1, 4, 2,        // a b c d e f g
    4, 1, 8, 5, 1, 3, 1, 1, 3,  // h i j k l m n o p
    10, 1, 1, 1, 1, 4,          // q r s t u v
    4, 8, 4, 10                 // w x y z
};

int main(void)
{
    char input[BUFF_SIZE];    
    int sum;

    printf("Enter a word: ");
    scanf("%s", input);
    
    for (int i = 0; i < BUFF_SIZE; i++){
        if (input[i] == '\0') break;
        sum += score_from_array(input[i]);
    }
    printf("Scrabble value: %3d", sum);
    return 0;
}

int score_from_array(char letter) {
    return SCORES[toupper(letter) - 'A'];
}
