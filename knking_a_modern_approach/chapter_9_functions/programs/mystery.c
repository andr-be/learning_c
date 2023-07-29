// MYSTERY FUNCTION
// andr-be 07/2023

#include <stdio.h>

void pb(int n);

int main(void)
{
    int n = 0;
    printf("Please enter a number: ");
    scanf("%d", &n);
    pb(n);

    return 0;
}

void pb(int n)
{
    if (n != 0) {
        pb(n / 2);
        putchar('0' + n % 2);
    }
}