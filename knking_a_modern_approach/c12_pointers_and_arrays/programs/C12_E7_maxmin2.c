// MAXMIN POINTER
// andr-be 08/2023
/*
    Does the same as maxmin.c but uses pointer arithmetic instead of
    array subscripting.
*/

#include <stdio.h>
#define N 10

void max_min_ptr(int *a, int n, int *max, int *min);

int main(void)
{
    int b[N], *p, max, min;

    printf("Enter %d numbers; ", N);
    for (p = b; p < b + N - 1; p++)
        scanf("%d", p);

    max_min_ptr(b, N, &max, &min);

    printf("Maximum: %d\n", max);
    printf("Minimum: %d\n", min);
}

void max_min_ptr(int *a, int n, int *max, int *min)
{
    int *p;
    for (p = a; p < a + n; p++) {
        if (*p > *max)      *max = *p;
        else if (*p < *min) *min = *p;
    }
}