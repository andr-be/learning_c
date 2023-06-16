// NUMBER OF DIGITS CALCULATOR
// andr-be 06/2023

#include <stdio.h>

int digits_pos(int input);
int digits_neg(int input);

int main(void) {
    int input = 0;
    printf("Enter a number: ");
    scanf("%d", &input);
    int result = input > 0 ? digits_pos(input) : digits_neg(input);
    if (result < 1)
        printf("Invalid numberL: %d", input);
    else
        printf("The number %d has %d digits.", input, result);
    return 0;
}

int digits_pos(int input) {
    if      (input < 10)         return 1;
    else if (input < 100)        return 2;
    else if (input < 1000)       return 3;
    else if (input < 10000)      return 4;
    else if (input < 100000)     return 5;
    else return 0;
}

int digits_neg(int input) {
    if      (input > -10)        return 1;
    else if (input > -100)       return 2;
    else if (input > -1000)      return 3;
    else if (input > -10000)     return 4;
    else if (input > -100000)    return 5;
    else return 0;
}