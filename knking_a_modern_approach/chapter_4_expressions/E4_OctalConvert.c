// OCTAL CONVERSION PROGRAM
// andr-be 06/2023

#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint16_t input = 0;
    printf("Enter a number between 0 and 32767: ");
    scanf("%hd", &input);
    printf("In octal, your number is: %05o\n", input);
}