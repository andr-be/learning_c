// Passing by Reference

#include <stdio.h>

void increment(int *p) // note that it accepts a pointer to an int
{
    *p = *p + 1;       // ad one to the thing p points to
}

int main(void)
{
    int i = 10;
    int *j = &i;    // note the address-of, turns it into a pointer to i

    printf("i is %d\n", i);         // prints "10"
    printf("i is also %d\n", *j);   // also prints "10"

    increment(j);                   // j is an int*--to i
    printf("i is %d\n", i);         // prints "11"!

    increment(&i);                  // &i is an intpointer to i
    printf("i is %d\n", i);         // prints "12"?
}