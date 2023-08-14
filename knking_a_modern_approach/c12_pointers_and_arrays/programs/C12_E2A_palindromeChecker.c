// PALINDROME FINDER 1
// andr-be 08/2023
/*
    A program that reads a message and checks whether it's a palindrome.
    a) Use integer variables to keep track of positions in the array.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LEN 1024

char *get_message(void);
bool is_palindrome(char* message);

int main(void)
{
    char* message = get_message();
    printf("%s", is_palindrome(message) ? "Palindrome" : "Not a palindrome");
    free(message);
}

char* get_message(void)
{
    char* message = malloc(sizeof(char) * MAX_LEN);
    printf("Enter a message: ");
    fgets(message, MAX_LEN, stdin);
    return message;
}

bool is_palindrome(char* msg)
{
    char *reverse = calloc(MAX_LEN, sizeof(char)),
         *stripped = calloc(MAX_LEN, sizeof(char));

    int length = 0;

    for (int i = 0; msg[i] != '\n'; i++)
        if (isalpha(msg[i])) 
            stripped[length++] = (char) tolower(msg[i]);

    for (int i = 0, j = length; j > 0;)
        reverse[i++] = stripped[--j];

    for (int i = 0; i < length; i++)
        if (stripped[i] != reverse[i]) return false;

    return true;
}