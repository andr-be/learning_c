// RECURSIVE POWER CALCULATOR
// andr-be 07/2023 
/*
    if n is a power of 2, then x^n can be computed by squaring
    e.g. x^4 is the square of x^2, so can be computed in only 2 multiplications
    if n is even -> x^n = (x^{n/2})^2
    if n is odd ->  x^n = x * x^{n-1}
*/

#include <stdio.h>

int power(int x, int n);
int power2(int x, int n);

int main(void)
{
    int x = 1, n = 0;
    printf("Enter a value of x and a value of n for x^n: ");
    scanf("%d %d", &x, &n);

    printf("p1: x^n == %d\n", power(x, n));
    printf("p2: x^n == %d\n", power2(x, n));
    return 0;
}

int power(int x, int n)
{
    return n == 0 ? 1 : x * power(x, n - 1);
}

int power2(int x, int n)
{
    if (n % 2 == 0) 
        return n == 0 ? 1 : power2(x, n/2) * power2(x, n/2);
    else 
        return n == 0 ? 1 : x * power2(x, n - 1);
}