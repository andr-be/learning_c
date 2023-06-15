// Instantiating Arrays

#include <stdio.h>

#define COUNT 5

int main (void) {

    int a[COUNT] = {[COUNT-3]=3, 2, 1};

    int b[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < COUNT; i++) {
        printf("%d ", a[i]);
        printf("%d\n", b[i]);
    }

}