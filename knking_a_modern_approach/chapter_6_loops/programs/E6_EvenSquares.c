// EVEN SQUARE PRINTER
// andr-be 06/2023

#include <stdio.h>

int main(void)
{
    int n = 0;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("All even square numbers less than %d:\n", n);
    
    for (int i = 2; (i * i) <= n; i++)
        if (!((i * i) % 2)) 
          printf("%d\n", i * i);
}
