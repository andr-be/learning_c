//  C7 EXERCISES: LEGAL CONSTANTS
//  andr-be 07/2023

#include <stdio.h>

int main(void)
{
    float a = 010E2;
    printf("%f\n", a);

    float b = 32.1E+5;
    printf("%f\n", b);

    //int c = 0790;       // invalid octal digit!

    //int d = 100_000;    // invalid suffix on integer!

    double e = 3.978e-2;
    printf("%f\n", e);

    return 0;
}
