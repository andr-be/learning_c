// EARLIEST DATE FINDER
// andr-be 06/2023

#include <stdio.h>

int main(void) {
    int dd1, mm1, yy1,
        dd2, mm2, yy2;

    printf("Enter first date (dd/mm/yy): ");
    scanf("%d / %d / %d", &dd1, &mm1, &yy1);

    printf("Enter second date (dd/mm/yy): ");
    scanf("%d / %d / %d", &dd2, &mm2, &yy2);

    if ((dd1 + mm1 * 28) < (dd2 + mm2 * 28))
        printf("%02d/%02d/%02d is earlier in the year than %02d/%02d/%02d\n", 
                dd1, mm1, yy1, 
                dd2, mm2, yy2 );
    else
        printf("%02d/%02d/%02d is earlier in the year than %02d/%02d/%02d\n", 
                dd2, mm2, yy2,
                dd1, mm1, yy1 );
}