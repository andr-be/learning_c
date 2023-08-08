// REPDIGIT2.c
// andr-be 07/2023
/*
    Shows which digits in a string of numbers are repeated (if any)
*/
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    int digit_seen[10] = {0},
        digit;
    long n;
    bool repeats = true;

    printf("Enter a number: ");
    scanf("%ld", &n);

    for (; n > 0; n /= 10) {
        digit = n % 10;
        digit_seen[digit] += 1;
    }

    printf("Digit:\t\t");
    for (int i = 0; i < 10; i++) 
        printf("%d  ", i);

    printf("\nOccurences:\t");
    for (int i = 0; i < 10; i++) 
        printf("%d  ", digit_seen[i]);

    return 0;
}
