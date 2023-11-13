#include <stddef.h>
#include <stdio.h>

#define MAX_ARR 64
const int *binary_search(int value, const int *arr, size_t length);


int main(void) {
    int arr[] = { 6 },                      a = 10,
        brr[] = { 1, 3, 4, 6, 8, 9, 11 },   b =  6, 
        crr[] = { 1, 3, 4, 6, 8, 9, 11 },   c =  1,
        drr[] = { 1, 3, 4, 6, 8, 9, 11 },   d = 11,
        err[] = { 1, 2, 4, 5, 6, 8,  9 },   e =  9;

    const int *a_a = binary_search(a, arr, 1),
              *b_b = binary_search(b, brr, 7),
              *c_c = binary_search(c, crr, 7),
              *d_d = binary_search(d, drr, 7),
              *e_e = binary_search(e, err, 7);


    if (a_a != 0) printf("%p: %d\n", a_a, *a_a);
    else          printf("%d: NOT FOUND\n", a);

    printf("%p: %d\n", b_b, *b_b);
    printf("%p: %d\n", c_c, *c_c);
    printf("%p: %d\n", d_d, *d_d);
    printf("%p: %d\n", e_e, *e_e);

}


const int *binary_search(int value, const int *arr, size_t length)
{
    size_t half = length / 2;
    int split = arr[half];
    
    if (split == value) 
        return &arr[half];

    else if (length == 1) return NULL;
    
    else if (split > value) 
        return binary_search(value, arr, half); 
    
    else if (split < value) {
        int new_arr[MAX_ARR] = {0};
        for (size_t i = 0; i <= half; i++)
            new_arr[i] = arr[half + i];
        return binary_search(value, new_arr, half + 1);
    }

    return NULL;
}