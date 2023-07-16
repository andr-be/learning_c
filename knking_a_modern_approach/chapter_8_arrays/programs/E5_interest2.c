// INTEREST2
// andr-be 07/2023
/*
    modified so that it compounds interest monthly instead of annually. 
    The form of the output is the same, the balance should be shown
    at annual intervals still
*/

#include <stdio.h>

#define NUM_RATES ((int) (sizeof(value) / sizeof(value[0])))
#define INITIAL_BALANCE 100.00

int main(void)
{
    int i, low_rate, num_years, year;
    double value[5];

    printf("Enter interest rate: ");
    scanf("%d", &low_rate);
    printf("Enter number of years: ");
    scanf("%d", &num_years);

    // top row
    printf("\nYears");
    for (i = 0; i < NUM_RATES; i++) {
        printf("%7d%%", low_rate + i);
        value[i] = INITIAL_BALANCE;
    }
    printf("\n");

    // data rows
    for (year = 1; year <= num_years; year++) {
        printf("%3d    ", year);
        for (i = 0; i < NUM_RATES; i++) {
            for (int j = 0; j < 12; j++) 
                value[i] += (low_rate / 12 + i) / 100.00 * value[i];
            printf("%8.2f", value[i]);
        }
        printf("\n");
    }
    return 0;
}