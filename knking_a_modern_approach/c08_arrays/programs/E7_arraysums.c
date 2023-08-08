// ARRAY SUMS
// andr-be 07/2023
/*
    When given 5 rows of 5 numbers, this program will calculate the
    row totals and the column totals.
    it does no error checking!
*/

#include <stdio.h>

int main(void)
{
    int a[5][5] = {0};
    for (int i = 0; i < 5; i++) {
        printf("Enter row %d: ", i + 1);
        scanf("%d %d %d %d %d", 
            &a[i][0], &a[i][1], &a[i][2], &a[i][3], &a[i][4]);
    }

    printf("ROW TOTALS: ");
    for (int i = 0; i < 5; i++) {
        int sum = 0;
        for (int j = 0; j < 5; j++)
            sum += a[i][j];
        printf("%d ", sum);
    }

    printf("\nCOLUMN TOTALS: ");
    for (int i = 0; i < 5; i++) {
        int sum = 0;
        for (int j = 0; j < 5; j++)
            sum += a[j][i];
        printf("%d ", sum);
    }

    return 0;
}
