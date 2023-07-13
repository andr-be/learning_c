// YET MORE FRACTION CALCULATORS
// andr-be 07/2023
/*
    this is a general fractionator that allows the user to enter operations
    TODO: implement this into the Frac calculator, or otherwise implement
          the simplification function from Frac in this program.
*/

#include <stdio.h>

int main(void)
{
    int num1, denom1, num2, denom2, 
        result_num = 0, result_denom = 1,
        scale_factor = 1;
    char operation;

    printf("Enter Fractions to Perform Operation (e.g. x/y + a/b):  ");
    scanf("%d/%d %c %d/%d", &num1, &denom1, &operation, &num2, &denom2);

    switch (operation)
    {
    case '+':
        result_num = num1 * denom2 + num2 * denom1;
        result_denom = denom1 * denom2;
        break;
    case '*': case 'x':
        result_num = num1 * num2;
        result_denom = denom1 * denom2;
        break;
    case '/':
        result_num = num1 * denom2;
        result_denom = num2 * denom1;
        break;
    case '-':
        scale_factor = (denom1 > denom2) ? denom1 : denom2;
        result_num = scale_factor * (num1 + num2);
        result_denom = scale_factor * (denom1 * denom2);
    default:
        break;
    }

    printf("The sum is %d/%d\n", result_num, result_denom);

    return 0;
}