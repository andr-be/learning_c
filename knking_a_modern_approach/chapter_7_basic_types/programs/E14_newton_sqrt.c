// NEWTON METHOD FOR SQUARE ROOTS
// andr-be 07/2023
/*
    uses Newton's method to compute the square root of a positive floating-point number.
*/

#include <math.h>
#include <stdio.h>

#define THRESHOLD 0.00001 

int main(void)
{
    double x = 0, y_n = 1, y_nm1 = 0;
    printf("Enter a positive number: ");
    scanf("%lf", &x);
    while (fabs(y_n - y_nm1) > THRESHOLD * y_n) {
        y_nm1 = y_n;
        y_n = ( (x / y_n) + (y_n) ) / 2;
    }
    printf("SQUARE ROOT: %20lf\n", y_n);
    return 0;
}
