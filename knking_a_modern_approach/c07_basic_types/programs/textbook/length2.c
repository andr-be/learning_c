// DETERMINE THE LENGTH OF A MESSAGE V2
// andr-be 06/2023

#include <stdio.h>

int main(void)
{
    char ch;
    int len = 1;

    printf("Enter a message: ");
    ch = getchar();
    while (getchar() != '\n')
        len++;
    printf("Your message was %d character(s) long!", len);

    return 0;
}
