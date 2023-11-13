// Chapter 13 - Exercise 4 - reverse.c
// andr-be 11/2023
/*
    Reverses all of the command line arguments given to it.
*/

#include <stdio.h>

int main(int argc, char const *argv[])
{
    for (argc -= 1; argc > 0; argc--) {
        printf("%s ", argv[argc]);
    }
    return 0;
}
