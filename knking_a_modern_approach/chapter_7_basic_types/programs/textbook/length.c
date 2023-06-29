// DETERMINE THE LENGTH OF A MESSAGE
// andr-be 06/2023

#include <stdio.h>

int main(void)
{
    char ch;
    int len = 0;

    printf("Enter a message: ");
    ch = getchar();
    while (ch != '\n') {
        len++;
        ch = getchar();
    }
    printf("Your message was %d character(s) long!", len);

    return 0;
}
