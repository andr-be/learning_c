// Chapter 13 - Exercise 13 - CAESER CIPHER 2
// andr-be 07/2023
/*
    Replaces each letter in a message with another letter that is a
    fixed number of positions later in the alphabet.

    - message does not exceed 80 characters
    - non-letters remain unchanged
    - lower case remains lower case, upper remains upper
        ((ch - 'A') + n) % 26 + 'A' calculates upper case letter.
        ((ch - 'a') + n) % 26 + 'a' calculates lower case
*/

#include <stdio.h>
#include <ctype.h>

#define BUFFSIZE 80

char encrypt(char input, int shift);
void encrypt_string(char *message, int shift);

int main(void)
{
    char message[BUFFSIZE];
    int shift = 0;
    printf("Enter message to be encrypted: ");
    fgets(message, BUFFSIZE - 1, stdin);

    printf("Enter shift amount (1-25): ");
    scanf("%d", &shift);

    encrypt_string(message, shift);
    return 0;
}

char encrypt(char input, int shift) {
    if (!isalpha(input)) 
        return input;

    if (islower(input)) 
        return ((input - 'a') + shift) % 26 + 'a';
        
    else                         
        return ((input - 'A') + shift) % 26 + 'A';
}

void encrypt_string(char *message, int shift)
{
    printf("Encrypted message: ");
    while (*message)
        putchar(encrypt(*message++, shift));
}