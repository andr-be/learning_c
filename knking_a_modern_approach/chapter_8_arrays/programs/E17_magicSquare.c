// NxN MAGIC SQUARE GENERATOR
// andr-be 07/2023
/*
    prints an n x n magic square: a square of all the numbers 1, 2,..., n^2
    where the sums of all rows, columns and diagonals are the same

    e.g. Enter size of magic square: 5
            17   24   1   8  15
            23    5   7  14  16
             4    6  13  20  22
            10   12  19  21   3
            11   18  25   2   9
*/

#include <stdio.h>

#define ARR_MAX 99

void print_array(int input[ARR_MAX][ARR_MAX], int n);
void fill_array(int input[ARR_MAX][ARR_MAX], int n);

int main(void)
{
    int n = 1;
    printf("Enter size of magic square: ");
    scanf("%d", &n);

    int square[ARR_MAX][ARR_MAX] = {0},
        i_row = 0,
        i_col = n/2;

    square[i_row][i_col] = 1;
    fill_array(square, n);
    print_array(square, n);

    return 0;
}

void print_array(int input[ARR_MAX][ARR_MAX], int n) {
    for (int j = 0; j < n; j++) 
    {
        for (int k = 0; k < n; k++) 
            printf("%5d", input[j][k]);
        
        putchar('\n');
    }
}

void fill_array(int input[ARR_MAX][ARR_MAX], int n) {
    int i_row = 0, 
        i_col = n/2;

    input[i_row][i_col] = 1;

    for (int i = 2; i <= n * n; i++) {
        i_row = (i_row < 1) ? n - 1 : i_row - 1;
        i_col = (i_col + 1 >= n) ? 0 : i_col + 1;

        if (input[i_row][i_col] != 0) 
        {
            i_row = (i_row + 2 >= n) ? 0 : i_row + 2;
            i_col = (i_col - 1 < 0) ? n - 1 : i_col - 1;

            if (input[i_row][i_col] != 0)
                i_row = (i_row + 1 >= n) ? 0 : i_row + 1;
        }
        input[i_row][i_col] = i;
    }
}
