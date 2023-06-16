// FIND MINIMUM & MAXIMUM
// andr-be 06/2023
/* 
    "Use as few if statements as possible!" 

    This solution exploits the fact that you can add booleans together in C because
    they're just integers really.

    If you get true for each expression, you get 3, which means it's larger
    than every other number.

    If you get false for each expression, you get 0, which means it's smaller
    than every other number.
*/

#include <stdio.h>

int main(void) {
    int num1, num2, num3, num4,
        min = 0, max = 0;

    printf("Enter four integers: ");
    scanf("%d %d %d %d", &num1, &num2, &num3, &num4);

    switch( (num1 > num2) + (num1 > num3) + (num1 > num4) ) {
        case 0: min = num1; break;
        case 3: max = num1; break;
    }
    switch( (num2 > num1) + (num2 > num3) + (num2 > num4) ) {
        case 0: min = num2; break;
        case 3: max = num2; break;
    }
    switch( (num3 > num2) + (num3 > num1) + (num3 > num4) ) {
        case 0: min = num3; break;
        case 3: max = num3; break;
    }
    switch( (num4 > num2) + (num4 > num1) + (num4 > num3) ) {
        case 0: min = num4; break; 
        case 3: max = num4; break; 
    }

    printf("MIN: %d\nMAX: %d", min, max);   
}