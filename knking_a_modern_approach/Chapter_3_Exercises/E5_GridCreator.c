// MAGIC SQUARE PROGRAM
// andr-be 06/2023
/*
    This program will take a string of 16 numbers,
    display them in a 4x4 grid and then calculate
    the sums of the columns, rows and diagonals.

    TEST: `16 3 2 13 5 10 11 8 9 6 7 12 4 15 14 1`
*/

#include <stdio.h>

#define GRID_SIZE   16
#define ROW_SIZE    4
#define COL_SIZE    GRID_SIZE / ROW_SIZE

int calculate_row_sum(int[], int, int);
int calculate_column_sum(int[], int, int);
int calculate_diagonal_sum(int[], int, int);

int main(void)
{
    int nums[GRID_SIZE] = {0};
    printf("Enter the numbers from 1 to 16 in any order:\n");

    scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 
        &nums[ 0], &nums[ 1], &nums[ 2], &nums[ 3], 
        &nums[ 4], &nums[ 5], &nums[ 6], &nums[ 7], 
        &nums[ 8], &nums[ 9], &nums[10], &nums[11], 
        &nums[12], &nums[13], &nums[14], &nums[15]
    );

    for (int j = 0; j < GRID_SIZE; j++)
    {
        printf("%2d\t", nums[j]);
        if ((j + 1) % ROW_SIZE == 0)
            putchar('\n');
    }

    printf("\nRow sums:\n");
    for (int i = 0; i < ROW_SIZE; i++)
    {
        int row_sum = calculate_row_sum(nums, ROW_SIZE, i);
        printf("  R%d: %3d, ", i, row_sum);
    }

    printf("\nColumn sums:\n");
    for (int i = 0; i < COL_SIZE; i++)
    {
        int col_sum = calculate_column_sum(nums, ROW_SIZE, i);
        printf("  C%d: %3d, ", i, col_sum);
    }

    printf("\nDiagonal sums:\n");
    for (int i = 0; i < 2; i++)
    {
        int dia_sum = calculate_diagonal_sum(nums, ROW_SIZE, i);
        printf("  D%d: %3d, ", i, dia_sum);
    }
}

int calculate_row_sum(int array[GRID_SIZE], int row_size, int row_index){
    int sum = 0,
        start_idx = row_size * row_index,
        end_idx = start_idx + row_size;

    for (int i = start_idx; i < end_idx; i++)
        sum += array[i];

    return sum;
}

int calculate_column_sum(int array[GRID_SIZE], int row_size, int col_index){
    int sum = 0;

    for (int i = col_index; i < GRID_SIZE; i += row_size)
        sum += array[i];

    return sum;
}

int calculate_diagonal_sum(int array[GRID_SIZE], int row_size, int dia_idx){
    int sum = 0;

    if (dia_idx == 0)
        for (int i = 0; i < GRID_SIZE; i += row_size + 1)
            sum += array[i];
    else
        for (int j = row_size - 1; j < row_size * row_size - 1; j += row_size - 1)
            sum += array[j];

    return sum;
}