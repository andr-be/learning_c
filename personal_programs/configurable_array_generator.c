// CONFIGURABLE ARRAY GENERATOR
// andr-be 06/2023
/*
    By defining the number of rows, columns, the increment amount and the initial values
    of each cell, as well as the starting display axis values, you too can create a 
    lovely looking 2d cartesian grid!
*/

#include <stdio.h>

#define ROWS 9999    // total number of: rows
#define COLS 9       //                  columns

#define INCR 1      // how much to increment each value by
#define INIT 0      // the starting value in (0,0)

#define X_ST 1      // initial x co-ordinate
#define Y_ST 1      // initial y co-ordinate

int main(void)
{
    // initialise an array of size y = ROWS & x = COLS with initial value INIT
    int a[ROWS][COLS] = {{0}},
        v = INIT;

    for (int y = 0; y < ROWS; y++) {

        int *b[ROWS];

        for (int x = 0; x < COLS; x++) {
            a[y][x] = v;
            v += INCR;
        }
        b[y] = a[y];
    }

    for (int y = ROWS - 1; y >= 0; y--) {
        
        for (int x = 0; x < COLS; x++)
            printf(
                "(%2d,%4d):%4d  ", 
                (x + X_ST) % 9999, 
                y + Y_ST, 
                a[y][x] % 9999
            );
        
        putchar('\n');
    }
    char *exit; 
    scanf("%d", &exit);
}
