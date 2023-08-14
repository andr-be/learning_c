// MESSAGE REVERSER
// andr-be 08/2023
/*
    A program that reads a message, then prints the reversal of the message.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 1024

char *get_message(void);
void print_reverse(char* message);

int main(void)
{
    char* message = get_message();
    print_reverse(message);
    free(message);
}

char* get_message(void)
{
    char* message = malloc(sizeof(char) * MAX_LEN);
    printf("Enter a message: ");
    fgets(message, MAX_LEN, stdin);
    return message;
}

void print_reverse(char* message)
{
    char *p = message;
    while (*p != '\n') p++;

    printf("Reversal is: ");
    for (p -= 1; p - message >= 0; p--)
        printf("%c", *p);
}