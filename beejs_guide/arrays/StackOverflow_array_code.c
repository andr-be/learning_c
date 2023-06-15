// Stackoverflow Array Code
// https://stackoverflow.com/a/50013322/20751776

#include <stdio.h>
#include <stdlib.h>

#define COL 5
#define MAX 5

int main (void) {

    int arr2d[MAX][COL] = {{ 0 }},  // simple 2D array
        *arr[MAX] = { NULL },       // 5 pointers to int
        i, j, v = MAX * COL;

    for ( i = 0; i < MAX; i++) {    // fill 2d array
        for ( j = 0; j < COL; j++)
            arr2d[i][j] = v--;
        arr[i] = arr2d[i];          // assign row-pointer to arr
    }

    for (i = 0; i < MAX; i++) {     // for each pointer
        for (j = 0; j < COL; j++)   // output COL ints
            printf(" %4d", arr[i][j]);
        putchar('\n');
    }
}