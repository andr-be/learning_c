// CALENDAR PRETTY PRINTER
// andr-be 06/2023

#include <stdio.h>

int main(void)
{
    // accept user inputs
    int days = 0, start_day = 0;
    printf("Enter number of days in month: ");
    scanf("%d", &days);
    printf("Enter starting day of the week (1=Sun, 7=Sat): ");
    scanf("%d", &start_day);

    for (int j = 1; j < start_day; j++)
        printf("   ");

    for (int i = 0; i < days; i++) {
        printf("%2d ", i + 1);
        if (((i + start_day) % 7) == 0)
            printf("\n");
    }
   
}