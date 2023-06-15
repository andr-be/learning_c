// TELEPHONE NUMBER PARSER
// andr-be 06/2023

#include <stdio.h>

int main(void)
{
    int area_code, first, second;
    printf("Enter phone number [(xxx) xxx-xxxx]:  ");
    scanf("(%d) %d-%d", &area_code, &first, &second);
    printf("You entered %d.%d.%d", area_code, first, second);
    return 0;
}

