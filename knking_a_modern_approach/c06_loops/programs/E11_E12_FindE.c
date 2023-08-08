// FINDING E
// andr-be 06/2023

#include <stdio.h>

float factorial(int);

int main(void)
{
    int n = 0, i = 1; 
    float e = 1, sigma = 0.005f;
    printf("This program approximates the value of Eulers constant.\n");
    printf("Please enter the number of iterations to perform: ");
    scanf("%d", &n);
    printf("Please enter a minimum sigma value to divide by: ");
    scanf("%f", &sigma);

    for (; i < n; i++) {
        if (1.0f / factorial(i) < sigma) break;
        e += 1.0f / factorial(i);
    }

    printf("Approximate value after %d iterations: %f\n", i, e);
    
    return 0;
}

float factorial(int i) {
    float result = (float)i--;
    for (;i > 0; i--)
        result *= (float)i;
    return result;
}