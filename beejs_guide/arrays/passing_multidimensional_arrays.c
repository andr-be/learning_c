// Passing Multidimensional Arrays to Functions
/*
    The compiler really only needs the second dimension so it can figure out
    how far in memory to skip for each increment of the first dimension. 
    In general, it needs to know all the dimensions except the first one.

    Also, remember that the compiler does minimal compile-time bounds 
    checking (if you’re lucky), and C does zero runtime checking of bounds. 
    No seat belts! Don’t crash by accessing array elements out of bounds! 
*/

#include <stdio.h>

void print_2d_array(int a[2][3])
{
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 3; col++)
            printf("%d ", a[row][col]);
        printf("\n");
    }
}

int main(void)
{
    int x[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    print_2d_array(x);
}