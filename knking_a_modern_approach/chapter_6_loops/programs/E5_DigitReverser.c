// GENERALISED NUMBER REVERSER
// andr-be 06/2023

#include <stdio.h>

void reverser(void);

int main(void)
{
    for(;;)
        reverser();
    return 0;
}

void reverser(void) {
    int input = 0, 
        output[9] = {0}, 
        temp = 0, 
        digits = 0;

    printf("enter an an integer up to 999,999,999: ");
    scanf("%d", &input);
    temp = input;
    
    while (temp > 0) { temp /= 10; digits++; }

    for (int i = 0; i < digits; i++) {
        output[i] = input % 10;
        input /= 10;
    }

    for (int j = 0; j < digits; j++)
        printf("%d", output[j]);

    printf("\n");
}