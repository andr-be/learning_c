// SQUARE GENERATOR w/ PROMPT
// andr-be 07/2023
/*
    You're not supposed to fflush stdin, but it works and I don't care.
*/

#include <stdio.h>

int main(void)
{
    int i, n;
    char e;

    printf("This program prints a table of squares.\n");
    printf("Enter number of entries in table: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        printf("%10d%10d\n", i, i * i);
        
        if (i % 24 == 0) {
            printf("Press Enter to continue...\t");
            fflush(stdin);
            do { e = getchar(); } while (e != '\n');
        }
    }

    return 0;
}