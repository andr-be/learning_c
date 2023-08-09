// SIMPLEST FRACTION
// andr-be 08/2023
/*
    This program uses Euclid's method to find the highest common
    divisor of two numbers to calculate a simplified fraction.
*/

#include <stdio.h>

#define MAX_ITER 4000

typedef struct frac {
    int n;
    int d;
} frac;

int gc_div(int, int);
frac from_ints(int, int);
frac from_user(void);
frac gc_simp(frac);
frac frac_simp(frac);
char* time_as_str(void);
void reduce(int, int, int *, int *);

int main(void)
{
    int result_nom, result_den;
    
    frac input = from_user();

    reduce(input.n, input.d, &result_nom, &result_den);

    printf("SIMPLEST FORM: %d/%d\n", result_nom, result_den);
    
    return 0;
}

void reduce(int numerator, int denominator, int *reduced_numerator, int* reduced_denominator)
{
    frac input = from_ints(numerator, denominator),
         result = gc_simp(input);

    *reduced_numerator = result.n;
    *reduced_denominator = result.d;
}


int gc_div(int n, int m) 
{
    if (n == 0 || m == 0)
        return (m > n) ? m : n;
    
    while (n != 0) {
        int temp = m % n;
        m = n, n = temp;
    }
    return m;
}

frac from_ints(int n, int d)
{
    frac result = { .n = n, .d = (d == 0) ? 1 : d };
    return result;
}

frac from_user(void)
{
    int n, d;
    printf("ENTER FRACTION (x/y): ");
    scanf("%d/%d", &n, &d);
    return from_ints(n, d);
}

frac gc_simp(frac input)
{
    int gcd = gc_div(input.n, input.d);
    frac result = { input.n / gcd, input.d / gcd };
    return result;
}

frac frac_simp(frac input)
{
    frac result = {input.n, input.d};
    for (int div = input.d; div > 1; div--)
        if (input.n % div == 0 && input.d % div == 0) {
            result.n = input.n / div;
            result.d = input.d / div;
            break;
        }
    return result;
} 
