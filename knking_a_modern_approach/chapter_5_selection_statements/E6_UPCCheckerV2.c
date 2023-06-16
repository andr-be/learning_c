// UPC CHECK DIGIT VALIDATOR
// andr-be 06/2023
/*
    French Bread Pepperoni Pizza:   0 13800 15173 5
    Jif's Creamy Peanut Butter:     0 51500 24128 ? -> 8
    Ocean Spray Cranberry Sauce:    0 31200 01005 ? -> 6
*/

#include <stdio.h>

int main(void)
{
    int d, 
        i1, i2, i3, i4, i5, 
        j1, j2, j3, j4, j5,
        first_sum, second_sum, total,
        user_check, check;

    printf("Enter the full UPC code: ");
    scanf("%1d %1d%1d%1d%1d%1d %1d%1d%1d%1d%1d %1d", 
            &d, 
            &i1, &i2, &i3, &i4, &i5, 
            &j1, &j2, &j3, &j4, &j5,
            &user_check);

    first_sum  =  d + i2 + i4 + j1 + j3 + j5;
    second_sum = i1 + i3 + i5 + j2 + j4;
    total      = 3 * first_sum + second_sum;
    check      = 9 - ((total - 1) % 10);

    printf("%s", check == user_check ? "VALID" : "INVALID");
}