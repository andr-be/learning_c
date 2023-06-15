// ADDFRAC REDUX
// andr-be 06/2023
/*
    Just a really quick demonstration of how you can parse
    in C using scanf; it's actually quite versatile!
*/

#include <stdio.h>

int main(void)
{
    int num1, denom1, num2, denom2, result_num, result_denom;

    printf("Enter Fractions to Add (x/y + a/b):  ");
    scanf("%d/%d + %d/%d", &num1, &denom1, &num2, &denom2);

    result_num = num1 * denom2 + num2 * denom1;
    result_denom = denom1 * denom2;

    printf("The sum is %d/%d\n", result_num, result_denom);

    return 0;
}