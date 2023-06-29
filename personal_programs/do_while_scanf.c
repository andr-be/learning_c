#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char ch;
    while ((ch = getchar()) == ' ');
    printf("%c", ch);
    return 0;
}
