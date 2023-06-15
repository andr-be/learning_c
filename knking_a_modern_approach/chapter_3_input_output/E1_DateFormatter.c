// DATE FORMATTER
// andr-be 06/2023

#include <stdio.h>

int main(void)
{
    for (int i = 0; i < 3; i++)
    {
        int mm, dd, yyyy;
        printf("Enter a date (mm/dd/yyyy): ");
        scanf("%d/%d/%d", &mm, &dd, &yyyy);
        
        printf("You entered the date %0.4d%0.2d%0.2d\n", yyyy, mm, dd);
        
        fflush(stdin);
    }
}