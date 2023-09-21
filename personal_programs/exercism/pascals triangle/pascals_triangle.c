// pascal's triangle
/*
    Creates and displays a Pascal's Triangle of a given row number
*/

#include "pascals_triangle.h"

int main(void)
{
    for (;;) 
    {
        size_t rows = 0;
        printf("Enter a positive integer number (999 to exit): ");
        scanf("%llu", &rows);
        if (rows == 999) break;    
        
        uint8_t **triangle = create_triangle(rows);
        print_triangle(triangle, rows);
        free_triangle(triangle, rows);
    }

    return 0;
}

void free_triangle(uint8_t **triangle, size_t rows)
{
    for (size_t i = 0; i < rows; i++)
        free(triangle[i]);

    free(triangle);
}

uint8_t **create_triangle(size_t rows)
{
    uint8_t **triangle = calloc(rows, sizeof(*triangle));
    for (size_t i = 0; i < rows; i++)
        triangle[i] = calloc(rows, sizeof(*triangle[i]));

    for (size_t n = 0; n < rows; n++)
        for (size_t x = 0; x < n + 1; x++)
            triangle[n][x] = (n > 0 && x > 0) 
                ? triangle[n-1][x-1] + triangle[n-1][x] : 1;

    return triangle;
}

void print_triangle(uint8_t **triangle, size_t rows)
{
    for (uint8_t i = 0; i < rows; i++) {
        printf("%d\t", i + 1);

        for (size_t s = rows - i; s > 0; s--)
            printf("  ");
        
        for (uint8_t j = 0; j < rows; j++)
            if (triangle[i][j]) printf("%3d ", triangle[i][j]);

        putchar('\n');        
    }
}

uint8_t sum_of_nth_row(uint8_t rows)
{
    return (uint8_t) pow(2, rows);
}

uint8_t sum_to_nth_row(uint8_t rows)
{
    return (uint8_t) pow(2, rows + 1) - 1;
}

