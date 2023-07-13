// SQUARE GENERATOR 2 V2
// andr-be 07/2023
/*
    part a: 46,341          (sqrt of 2^31 - 1)
    part b: 182             (sqrt of 2^15 - 1)
    part c: 3,037,000,500   (sqrt of 2^63 - 1)
*/

#include <stdio.h>

int main(void)
{
    short i, n;

    printf("This program prints a table of squares.\n");
    printf("Enter number of entries in table: ");
    scanf("%hd", &n);

    for (i = 1; i <= n; i++) 
        printf("%10hd%10hd\n", i, i * i);

    return 0;
}