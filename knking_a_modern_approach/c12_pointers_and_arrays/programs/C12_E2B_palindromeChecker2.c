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
bool is_palindrome_ptr(char *msg);

int main(void)
{
    char* message = get_message();
    printf("%s", is_palindrome_ptr(message) ? "Palindrome" : "Not a palindrome");
    free(message);
}

char* get_message(void)
{
    char* message = malloc(sizeof(char) * MAX_LEN);
    printf("Enter a message: ");
    fgets(message, MAX_LEN, stdin);
    return message;
}

bool is_palindrome_ptr(char *msg)
{
    bool palindrome = true;
    char *p = msg,
         *stripped = calloc(MAX_LEN, sizeof(char)),
         *q = stripped;

    for (; *p != '\n'; p++) 
        if (isalpha(*p)) *q++ = (char) tolower(*p);

    for (p = stripped, q--; q >= p;)
        if (*p++ != *q--) palindrome = false;

    free(stripped);

    return palindrome;
}