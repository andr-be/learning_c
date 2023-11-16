// MESSAGE REVERSER
// andr-be 08/2023
/*
    A program that reads a message, then prints the reversal of the message.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 1024

char *get_message(void);
void reverse(char *message);

int main(void)
{
    char* message = get_message();
    reverse(message);
    printf("Reversal: %s\n", message);
    free(message);
    return 0;
}

char* get_message(void)
{
    char* message = malloc(sizeof(char) * MAX_LEN);
    printf("Enter a message: ");
    fgets(message, MAX_LEN, stdin);
    return message;
}

void reverse(char *message)
{
    char *start = message;
    char *end = message;

    while (*end != '\n')
        end++;

    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
}