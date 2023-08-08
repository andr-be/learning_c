// GENERALISED NUMBER REVERSER
// andr-be 06/2023

#include <stdio.h>

void reverser(void);

int main(void)
{
    for(;;) reverser();
    return 0;
}

void reverser(void) {
    int input  = 0, 
        temp   = 0, 
        digits = 0,
        output[9] = {0}; 

    printf("enter an an integer up to 999,999,999: ");
    scanf("%d", &input);
    temp = input;
    
    for (temp = input; temp > 0; temp /= 10, digits++) {
        output[digits] = input % 10;
        input /= 10;
    }

    for (int i = 0; i < digits; i++)
        printf("%d", output[i]);

    printf("\n");
}