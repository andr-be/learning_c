// ALPHANUMERIC PHONE INTERPRETER
// andr-be 07/2023
/*
    Translates American letter phone numbers into regular, normal phone numbers
    1-800-CAL-LATT == 1-800-225-5288
    1-800-COL-LECT == 1-800-265-5328
*/

#include <stdio.h>
#define BUFF_SIZE 80 

char switch_to_num(char);

int main(void)
{
    char input[BUFF_SIZE], 
         letter;
    
    printf("Enter phone number: ");
    scanf("%s", input);
    
    for (int i = 0; i < BUFF_SIZE; i++){
        if (input[i] == '\0') break;
        letter = switch_to_num(input[i]);
        printf("%c", letter);
    }
    return 0;
}

char switch_to_num(char letter) {
    switch (toupper(letter))
    {
    case 'A': case 'B': case 'C':           return '2';
    case 'D': case 'E': case 'F':           return '3';
    case 'G': case 'H': case 'I':           return '4';
    case 'J': case 'K': case 'L':           return '5';
    case 'M': case 'N': case 'O':           return '6';
    case 'P': case 'Q': case 'R': case 'S': return '7';
    case 'T': case 'U': case 'V':           return '8';
    case 'W': case 'X': case 'Y': case 'Z': return '9';
    default: return letter;
    }
}