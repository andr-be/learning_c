// Basic Functions

#include <stdio.h>

int plus_one(int n);
void hello(void);

int main(void)
{
    int i = 10, j;
    j = plus_one(i); // the call
    printf("i + 1 is %d\n", j);
    hello(); // look, it's this fucking function again!
}

int plus_one(int n) // the "definition"
{
    return n + 1;
}

// take no arguments, return no values
void hello(void)
{
    printf("Hello, world!\n");
}