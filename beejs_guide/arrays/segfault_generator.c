// SEGFAULT GENERATOR
// andr-be 06/2023
/*
    This program creates a segfault. I don't really know why yet.
    One to come back to! Maybe?

    The intent was to create an array of arrays, and I wanted to do
    that by creating an array of array-pointers, and then changing 
    each array pointer to the address of an array!
*/

#include <stdio.h>

int main(void)
{
    int a[10][10] = {{0}};
    for (int i = 0; i < 10; i++)
    {
        int *b[10];
        for (int j = 0; j < 10; j++)
        {
            a[i][j] = j;
        }
        b[i] = a[i];
    }
    for (int k = 0; k < 10; k++)
    {
        for (int l = 0; l < 10; l++)
        {
            printf("(%d, %d): %d\n", k, l, a[k][l]);
        }
    }
}