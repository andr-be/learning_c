// FACTORIAL OF A POSITIVE INTEGER
// andr-be 07/2023
/*
    Computes the factorial of a positive integer.
    e.g.    Enter a positive integer: 6
            Factorial of 6: 720

    ANSWERS:
        (a) 7
        (b) 15
        (c) 15
        (d) 20
        (e) 34
        (f) 170
        (g) it doesn't work; I can't display long doubles!
*/

#include <stdio.h>

int main(void)
{
    int integer = 0;
    double factorial = 1.0f;

    printf("Enter a positive integer: ");
    scanf("%d", &integer);

    while (integer > 0) factorial *= (double) integer--;
    
    printf("Factorial: %.0le\n", factorial);
    return 0;
}
