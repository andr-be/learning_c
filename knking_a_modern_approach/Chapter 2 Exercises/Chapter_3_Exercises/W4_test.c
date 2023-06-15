// Written Exercise 4 Testbed
// andr-be 06/2023
/*
    I don't really understand how scanf works tbh.
    The whole exercise felt like a massive waste of brainpower.
    Basically, scanf is a fuck.
*/

#include <stdio.h>

int main(void)
{
    int i, j;
    float x;
    scanf("%d%f%d", &i, &x, &j);

    printf("\ni = %d", i);
    printf("\nx = %f", x);
    printf("\nj = %d", j);
}