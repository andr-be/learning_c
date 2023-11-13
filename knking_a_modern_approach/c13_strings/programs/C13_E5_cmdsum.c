// Chapter 13 - Exercise 5 - cmdsum.c
// andr-be 11/2023
/*
    Sums up all numbers given to the program via the command line
    -> assume all arguments are valid integers
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int sum = 0;
    for (int i = 1; i < argc; i++) {
        int input = atoi(argv[i]);
        printf("%d + %d = %d\n", sum, input, sum + input);
        sum += input;
    }
    return 0;
}
