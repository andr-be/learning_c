// DOUBLE SUM
// andr-be 07/2023

#include <stdio.h>

int main(void)
{
    double n, sum = 0;
    printf("This program sums a series of floats.\n");
    printf("Enter floats (0 to terminate): \n");

    scanf("%lf", &n);
    while (n != 0) {
        sum += n;
        scanf("%lf", &n);
    }
    printf("The sum is: %lf\n", sum);

    return 0;
}
