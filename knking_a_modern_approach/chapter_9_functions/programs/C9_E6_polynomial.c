// POLYNOMIAL CALCULATOR
// andr-be 07/2023
/*
    Compute the value of the following polynomial:
    y = 3x^5 + 2x^4 - 5x^3 - x^2 + 7x - 6

    TODO: - variable length arrays
          - a means by which you input the order and the coefficients
          - looping
*/

#include <stdio.h>
#include <math.h>

int polynomial(int x, int order, int coefficients[order]);
int power(int x, int y);

int main(void)
{
    int x = 0, y = 0, order = 6;
    static int coefficients[6] = {3, 2, -5, -1, 7, -6};

    printf("Enter a value for x: ");
    scanf("%lf", &x);

    y = polynomial(x, order, coefficients);
    printf("y = %d\n", y);

    return 0;
}

int power(int x, int y)
{
    int sum = 1;

    for (; y > 1; y--) sum *= x;

    return sum;
}

int polynomial(int x, int order, int coefficients[order])
{
    int y = 0;

    for (int i = 0; order > 0; order--, i++)
        y += coefficients[i] * power(x, order);
    
    return y;
}