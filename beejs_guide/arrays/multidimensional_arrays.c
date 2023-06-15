// Multidimensional Arrays & print_2darray
// andr-be 06/2023

#include <stdio.h>

// prints every element within a 2d array, given the row & column totals
int print_2darray(int rows, int cols, int arr[rows][cols])
{
    int row = 0, col = 0, sum = 0;

    for ( row; row < rows; row++ ) {
        for ( col; col < cols; col++ )
            printf("(%d,%d) = %d\n", row, col, arr[row][col]);
    }
}

int main(void)
{    
    int a[2][5] = {
        {0, 1, 2, 3, 4},
        {5, 6, 7, 8, 9}
    };

    print_2darray(2, 5, a);
}