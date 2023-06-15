// Arrays and Pointers

#include <stdio.h>

int main(void) 
{
    int a[5] = {11, 22, 33, 44, 55};
    int *p;

    p = &a[0];      // p points to the array
                    // actually, it points to the first element

    printf("%d\n", *p);     // prints "11"

    int array[5] = {99, 88, 77, 66, 55};
    int *array_pointer;

    array_pointer = array; // equivalent to array_pointer = &array[0]

    printf("%d\n", *array_pointer); // dereferences to display first element
}