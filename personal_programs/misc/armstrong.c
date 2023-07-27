#include <stdbool.h>
#include <stdio.h>
#include <math.h>
bool is_armstrong_number(int candidate);

int main(void) {
    printf("153: %d\n", is_armstrong_number(153));
}

bool is_armstrong_number(int input) {
    int digits[8] = {0},
        candidate = input,
        sum = 0,
        i = 0;
    
    for (; candidate > 0; i++) {
        digits[i] = candidate % 10;
        candidate /= 10;
    }

    for (int j = i - 1; j >= 0; j--)
        sum += pow(digits[j], i);

    return sum == input;
}