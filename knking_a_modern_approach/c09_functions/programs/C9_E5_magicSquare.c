// NxN MAGIC SQUARE GENERATOR
// andr-be 07/2023
/*
    Hilariously it turns out I've already basically done the problem already
    - void create_magic_square(int n, char magic_square[n][n]);
    - void print_magic_square(int n, char magic_square[n][n]);

    Gonna refactor for the experience though.
*/

#include <stdio.h>

#define ARR_MAX 99

void create_magic_square(int n, int input[n][n]);
void print_magic_square(int n, int input[n][n]);

int main(void)
{
    int n = 0;
    printf("Enter size of magic square: ");
    scanf("%d", &n);

    int square[ARR_MAX][ARR_MAX] = {0};
    create_magic_square(n, square);
    print_magic_square(n, square);

    return 0;
}

void print_magic_square(int n, int input[n][n]) {
    for (int j = 0; j < n; j++) 
    {
        for (int k = 0; k < n; k++) 
            printf("%5d", input[j][k]);
        
        putchar('\n');
    }
}

void create_magic_square(int n, int input[n][n]) {
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
