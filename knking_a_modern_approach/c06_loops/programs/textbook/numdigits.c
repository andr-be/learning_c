// NUMBER OF DIGITS COUNTER
// andr-be 06/2023
/*
    calculates the number of digits in an integer
*/

#include <stdio.h>

int main(void)
{
    int digits = 0, n;

    printf("Enter a nonnegative integer: ");
    scanf("%d", &n);

    do {
        n /= 10;
        digits++;
    } while (n > 0);

    printf("The number has %d digits(s).\n", digits);

    return 0;
}