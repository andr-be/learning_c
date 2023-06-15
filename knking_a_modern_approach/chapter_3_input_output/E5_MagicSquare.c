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

void print_array(int[], int);
void print_row_sums(int[], int);
void print_col_sums(int[], int);
void print_dia_sums(int[], int);

int calculate_row_sum(int[], int, int);
int calculate_column_sum(int[], int, int);
int calculate_diagonal_sum(int[], int, int);


int main(void)
{
    int array[GRID_SIZE] = {0};
    printf("Enter the numbers from 1 to 16 in any order:\n");

    scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 
        &array[ 0], &array[ 1], &array[ 2], &array[ 3], 
        &array[ 4], &array[ 5], &array[ 6], &array[ 7], 
        &array[ 8], &array[ 9], &array[10], &array[11], 
        &array[12], &array[13], &array[14], &array[15]
    );

    print_array(array, ROW_SIZE);
    
    print_row_sums(array, ROW_SIZE);
    print_col_sums(array, ROW_SIZE);
    print_dia_sums(array, ROW_SIZE);
}


void print_array(int array[GRID_SIZE], int row_size){
    putchar('\n');
    for (int j = 0; j < GRID_SIZE; j++)
    {
        printf("%2d\t", array[j]);
        if ((j + 1) % row_size == 0)
            putchar('\n');
    }
}

void print_row_sums(int array[GRID_SIZE], int row_size){
    printf("\nRow sums:\n");
    for (int i = 0; i < ROW_SIZE; i++)
    {
        int row_sum = calculate_row_sum(array, row_size, i);
        printf("  R%d: %3d, ", i, row_sum);
    }
}

void print_col_sums(int array[GRID_SIZE], int row_size){
    printf("\nColumn sums:\n");
    for (int i = 0; i < row_size; i++)
    {
        int col_sum = calculate_column_sum(array, row_size, i);
        printf("  C%d: %3d, ", i, col_sum);
    }
}

void print_dia_sums(int array[GRID_SIZE], int row_size){
    printf("\nDiagonal sums:\n");
    for (int i = 0; i < 2; i++)
    {
        int dia_sum = calculate_diagonal_sum(array, row_size, i);
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