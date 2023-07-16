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

void print_array(int input[99][99], int n);

int main(void)
{
    int n = 1;
    printf("Enter size of magic square: ");
    scanf("%d", &n);

    int square[99][99] = {0},
        i_row = 0,
        i_col = n/2;

    square[i_row][i_col] = 1;
    
    for (int i = 2; i <= n * n; i++) {
        i_row -= 1; 
        if (i_row < 0) i_row = n - 1;

        i_col += 1; 
        if (i_col >= n) i_col = 0;

        while (square[i_row][i_col] != 0) {
            i_row += 2; 
            if (i_row >= n) i_row = 0;
            i_col -= 1;
            if (i_col < 0) i_col = n - 1;
            
            if (square[i_row][i_col] != 0) {
                i_row += 1;
                if (i_row >= n) i_row = 0;
            }
        }
        square[i_row][i_col] = i;
    }
    print_array(square, n);
    return 0;
}

void print_array(int input[99][99], int n) {
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            printf("%5d", input[j][k]);
        }
        putchar('\n');
    }
}
