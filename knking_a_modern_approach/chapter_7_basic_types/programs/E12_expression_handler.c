// EXPRESSION HANDLER
// andr-be 07/2023
/*
    A program that evaluates a mathetmatical expression.
    1) only works on floats
    2) evaluated left-to-right (no operator priority)

    TODO: fgets into a buffer, sscanf to parse the string
*/

#include <stdio.h>

int main(void)
{
    char ch;
    float total, next;
    printf("Enter an expression: ");
    scanf("%f ", &total);
    do
    {
        scanf("%c %f", &ch, &next);
        switch (ch)
        {
        case '+': total += next; break;
        case '-': total -= next; break;
        case '*': total *= next; break;
        case '/': total /= next; break;

        default:                 break;
        }
    } while (getchar() != '\n');
    
    printf("TOTAL: %.3f\n", total);
    return 0;
}
