// SIMPLEST FRACTION
// andr-be 06/2023
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

int gc_div(int, int) ;
frac from_ints(int, int);
frac from_user(void);
frac gc_simp(frac);
frac frac_simp(frac);
char* time_as_str(void);

int main(void)
{
    frac input = from_user();
    frac result_1 = gc_simp(input);
    frac result_2 = frac_simp(input);

    printf("GC METHOD: %d/%d\nMY METHOD: %d/%d", 
        result_1.n, result_1.d, result_2.n, result_2.d);
    
    return 0;
}


int gc_div(int n, int m) 
{
    if (n == 0 || m == 0)
        return (n == 0) ? m : n;
    
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
