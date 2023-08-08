// SELECTION SORT
// andr-be 07/2023
/*
    sorts an array of integers by
    1) searches the array to find the largest element
    2) moves largest to the last position in the array
    3) calls itself recursively to sort the first n-1 elements of the array
*/

#include <stdio.h>

#define N 5

void selection_sort(int a[], int n);

int main(void)
{
    int a[N], i = 0;
    printf("Enter a series of %d integers to be sorted: ", N);
    for (; i < N; i++) scanf("%d", &a[i]);

    selection_sort(a, N);

    printf("In sorted order: ");
    for (i = 0; i < N; i++) printf("%d ", a[i]);
    putchar('\n');

    return 0;
}

void selection_sort(int a[], int n)
{
    int b_index = 0, last;

    // if there's only one element or fewer, return
    if (n <= 1) return;

    // find the biggest element, store its index
    for (int i = 0; i < n; i++)
        b_index = a[i] > a[b_index] ? i : b_index;

    // take the last element, swap it with the biggest
    last = a[--n];
    a[n] = a[b_index];
    a[b_index] = last;

    // recurse; sort will end when only one element is unsorted
    selection_sort(a, n);
}