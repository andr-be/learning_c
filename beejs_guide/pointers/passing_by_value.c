// Passing By Value

/*  
    this program prints, somewhat counterintuitively, 
    the value 10, not 11. why? well, basically, the
    value is modified by increment(), but all values
    in C passed this way are done so via copy, not
    by reference!
    so, essentially, we're copying i (10), adding 1, 
    throwing the result (11) away and then printing i
    again...
*/

#include <stdio.h>

void increment(int a)
{
    a++;
}

int main(void)
{
    int i = 10;

    increment (i);

    printf("i == %d\n", i); // what does this print?
}

