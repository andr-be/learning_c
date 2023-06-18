// SIMPLEST FRACTION
// andr-be 06/2023
/*
    I'm going to pit my algorithm to get the simplest fraction against
    the algorithm provided in the previous exercise and see which
    is fastest!

    @ 2000 ITERATIONS           @ 4000 ITERATIONS
    EUCLID START: 00:03:27      EUCLID START: 00:06:55
    EUCLID END:   00:03:27      EUCLID END:   00:06:57
                    +00:00                      +00:02
    FRAC START:   00:03:27      FRAC START:   00:06:57
    FRAC FINISH:  00:03:42      FRAC END:     00:08:56
                    +00:15                      +01:59
    welp
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_ITER 4000

typedef struct frac {
    int n;
    int d;
} frac;

frac from_ints(int n, int d)
{
    frac result = { .n = n, .d = (d == 0) ? 1 : d };
    return result;
}

frac from_user(void){
    int n, d;
    printf("ENTER FRACTION (x/y): ");
    scanf("%d/%d", &n, &d);
    return from_ints(n, d);
}

int gc_div(int n, int m) {
    if (n == 0 || m == 0)
        return (n == 0) ? m : n;
    
    while (n != 0) {
        int temp = m % n;
        m = n, n = temp;
    }
    return m;
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

char* time_as_str(void)
{
    time_t raw_start_time;
    struct tm *rst;
    char *string;
    string = malloc(sizeof(char) * 80);

    time ( &raw_start_time );
    rst = localtime( &raw_start_time );
    strftime(string, 80, "%X", rst);

    return string;
}

int main(void)
{
    _Bool stress_test = 1;
    int gc_find = 0, frac_find = 0;
    if (!stress_test) {
        frac input = from_user();
        frac result_1 = gc_simp(input);
        frac result_2 = frac_simp(input);
        printf("GC METHOD: %d/%d\nMY METHOD: %d/%d", 
            result_1.n, result_1.d, result_2.n, result_2.d);
    } else {
        printf("TEST 1 START TIME: %s\n", time_as_str());
        for (int i = 1; i < MAX_ITER; i++) {
            for (int j = 1; j <= MAX_ITER; j++) {
                frac test_1 = from_ints(i, j);
                frac result_1 = gc_simp(test_1);
                if ((result_1.d < 5 && result_1.d > 1) && (i != result_1.n && j != result_1.d)) {
                    // printf("%d/%d simplified to %d/%d\n", i, j, result_1.n, result_1.d);
                    gc_find++;
                }
            }
        }
        printf("TEST 1 END TIME: %s\n", time_as_str());
        printf("TEST 2 START TIME: %s\n", time_as_str());
        for (int i = 1; i < MAX_ITER; i++) {
            for (int j = 1; j <= MAX_ITER; j++) {
                frac test_2 = from_ints(i, j);
                frac result_2 = frac_simp(test_2);
                if ((result_2.d < 5 && result_2.d > 1) && (i != result_2.n && j != result_2.d)) {
                    // printf("%d/%d simplified to %d/%d\n", i, j, result_2.n, result_2.d);
                    frac_find++;
                }
            }
        }
        printf("FINISH TIME: %s\n", time_as_str());
        printf("GC FIND: %d\nFRAC FIND: %d\n", gc_find, frac_find); 
    }
    return 0;
}


