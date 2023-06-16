// FIND MINIMUM & MAXIMUM
// andr-be 06/2023
/* 
    This is another 0-if approach, this one using the ternary operator.

    It first assigns min and max to the first number's value then
    goes through every other number and if any are bigger 
    reassigns max to be their value

    It does the same for min, and then displays the results.
*/

#include <stdio.h>

int main(void) {
    int num1, num2, num3, num4,
        min = 0, max = 0;

    printf("Enter four integers: ");
    scanf("%d %d %d %d", &num1, &num2, &num3, &num4);

    min = max = num1;

    max = (num2 > max) ? num2 : max;
    max = (num3 > max) ? num3 : max;
    max = (num4 > max) ? num4 : max;

    min = (num2 < min) ? num2 : min;
    min = (num3 < min) ? num3 : min;
    min = (num4 < min) ? num4 : min;

    printf("MIN: %d\nMAX: %d", min, max);   
}