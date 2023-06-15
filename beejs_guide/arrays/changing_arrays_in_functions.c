#include <stdio.h>

void double_arry(int *a, int len)
{
    // multiply each element by 2
    //
    // this doubles the values in x in main() since x and a both
    // point to the same array in memory!

    for (int i = 0; i < len; i++)
        a[i] *= 2;
}

int main(void) {
    int x[5] = {1, 2, 3, 4, 5};

    double_arry(x, 5);

    for (int i = 0; i < 5; i++)
        printf("%d, ", x[i]);       // 2, 4, 5, 6, 8, 10!
}