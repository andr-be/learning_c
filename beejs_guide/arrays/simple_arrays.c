// Simple Arrays

#include <stdio.h>

int main(void)
{
    int a[100] = {0};

    for (int i = 0; i < 100; i++)
    {
        a[i] = i;
    }

    for (int j = 99; j >= 0; j--)
    {
        printf("\n%d", a[j]);
    }
}