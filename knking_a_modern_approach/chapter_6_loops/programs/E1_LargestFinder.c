// FIND THE LARGEST NUMBER PROGRAM
// andr-be 06/2023

#include <stdio.h>

#define ARRAY_MAX 1024

float get_number(void) {
    float i = 0;
    printf("Enter a number: ");
    scanf("%f", &i);
    return i;
}

float get_largest(float array[], int array_size){
    float max = 0;
    for (int i = 0; i < array_size; i++)
        max = (array[i] > max) ? array[i] : max;
    return max;
}

int main(void)
{
    float array[ARRAY_MAX] = {0};
    int size = 0;
    for (;;)
    {
        // take user input
        float input = get_number();
        // break if (input <= 0)
        if (input <= 0) break;
        // add new float to array and increase size
        array[size] = input;
        size++;
    }
    float largest = get_largest(array, size);
    printf("The largest number entered was %f.2\n", largest);
    return 0;
}
