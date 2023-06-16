// 12HR TIME GENERATOR
// andr-be 06/2023

#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    int hrs, mins;
    printf("Enter a 24-hour time: ");
    scanf("%d : %d", &hrs, &mins);

    // if midday or later, xM = PM
    char* xM = (hrs > 11) ? "PM" : "AM";

    // if 13pm or later, % 12 the number
    hrs = (hrs > 13) ? hrs %= 12 : hrs;  

    printf("Equivalent 12-hour time: %d:%02d %s\n", hrs, mins, xM);
}