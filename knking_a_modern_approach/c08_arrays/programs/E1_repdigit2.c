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

    for (int i = 0; digit_seen[i] < 2 && i < 10; i++)
        if (i == 9) repeats = false; 
        
    if (repeats == false) printf("No repeated digit\n");

    else {
        printf("Repeated digit(s): ");
        for (int i = 0; i < 10; i++)
            if (digit_seen[i] > 1) printf("\n%d (x%d)", i, digit_seen[i]);
    }

    return 0;
}
