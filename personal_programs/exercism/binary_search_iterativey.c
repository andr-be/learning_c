// ITERATIVE BINARY SEARCH v2
// andr-be 08/2023
/*
    Significant improvement over previous iteration. 
    No longer requires the MAX_ITER fallback!
*/

#include <stddef.h>
#include <stdio.h>

#define MAX_ITER 64

const int *binary_search(int value, const int *arr, size_t length);
void safe_print(int *result);
size_t midpoint(size_t high, size_t low);

int main(void) {
    int arr[] = { 6 },                      a = 10,
        brr[] = { 1, 3, 4, 6, 8, 9, 11 },   b =  6, 
        crr[] = { 1, 3, 4, 6, 8, 9, 11 },   c = 10,
        drr[] = { 1, 3, 4, 6, 8, 9, 11 },   d = 11,
        err[] = { 1, 2, 3, 4, 5, 6, 8, 9 }, e =  9;

    const int *a_a = binary_search(a, arr, 1),
              *b_b = binary_search(b, brr, 7),
              *c_c = binary_search(c, crr, 7),
              *d_d = binary_search(d, drr, 7),
              *e_e = binary_search(e, err, 8);


    safe_print(a_a);
    safe_print(b_b);
    safe_print(c_c);
    safe_print(d_d);
    safe_print(e_e);
}

const int *binary_search(int value, const int *arr, size_t length)
{
    size_t low = 0,
           high = length - 1;

    if (value < arr[low] || value > arr[high] || !length) 
        return NULL;
    
    for(;;) {
        int index = midpoint(high, low),
            test = arr[index];

        if (test == value)     return &arr[index];
        else if (low >= high)  break;
        else if (test < value) low = index + 1;
        else if (test > value) high = index - 1;
    }
    return NULL;
}

size_t midpoint(size_t high, size_t low) {
    return (high - (high - low) / 2);
}

void safe_print(int *result){
    if (result != 0) printf("%p: %d\n", result, *result);
    else             printf("NOT FOUND\n");
}