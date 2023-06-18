// GREATEST COMMON DIVISOR PROGRAM
// andr-be 06/2023
/*
    This program implements Euclids Method for finding the greatest common divisor.
    I should probably have left comments explaining what the algorithm is doing,
    but I like it this way. It's mysterious. 
    I'll have to look up Euclid's Methods on Wikipedia
*/

#include <stdio.h>

typedef struct nums {
    int first;
    int second;
} nums;

nums get_input(void) {
    int first, second;
    printf("Enter two integers: ");
    scanf("%d %d", &first, &second);
    nums result = {first, second};
    return result; 
}

int g_c_div(int n, int m) {
    if (n == 0 || m == 0)
        return (n == 0) ? m : n;
    
    while (n != 0) {
        int temp = m % n;
        m = n, n = temp;
    }

    return m;
}

int main(void)
{
    nums numbers = get_input();
    int gc_divisor = g_c_div(numbers.first, numbers.second);
    printf("Greatest common divisor: %d", gc_divisor);
    return 0;
}
