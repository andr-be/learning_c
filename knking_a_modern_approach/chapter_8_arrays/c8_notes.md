# Chapter 8: Arrays - Notes

> *If a program maniupulates a large amount of data, it does so in a small number of ways*.

Up until now, we've been working with scalar variables that hold a single data item. In C, there are also aggregate forms, which hold multiple data items. They are known as **arrays** and **structures**, and this chapter will focus primarily on one-dimensional arrays.

***

## One-Dimensional Arrays

An array is a data structure containing a number of data values (known as elements), all of which have the same type.

The simplest type of array has only one dimension, and the elements are conceptually arranged one after another in a single row.

```C
#define N 10
...
int a[N];      // create an array of 10 integer values
```

which we can visualise in the following way

```
  [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ]   [ ] 
  a[0]  a[1]  a[2]  a[3]  a[4]  a[5]  a[6]  a[7]  a[8]  a[9]
```

these can be used in ways that should be familiar by now;

```C
a[0] = 1;
printf("%d\n", a[5]);
++a[i];
```

If an array contains elements of type **T**, then each element of the array is treated as if it were a variable of type **T**. In the examples above, the elements `a[0]`, `a[5]` and `a[i]` behave like `int` variables.

Arrays and `for` loops are often employed together in idiomatic C. 

```C
for (i = 0; i < N; i++)
    a[i] = 0;               // clears the array

for (i = 0; i < N; i++)
    scanf("%d", &a[i]);     // reads data into an array

for (i = 0; i < N; i++)
    sum += a[i];            // sums the elements of the array
```

Array subscripts can be any integer expression, or even have side effects:

```C
a[i+j*10] = 0;

i = 0;
while (i < N)
    a[i++] = 0;
```

After `i` is set to `0` the `while` statement checks whether `i` is less than `N`. If it is, `0` is assigned to `a[0]`, `i` is incremented and the loop repeats. 

`++i` wouldn't be right, because 0 would be assigned to `a[1]` on the first loop.

In general, having increment operators within array subscripts isn't considered best practice for easy to understand code. The following example demonstrates two methods of copying one array into another.

```C
// using increment subscripts
i = 0;
while (i < N)
    a[i] = b[i++];

// using classic for loop
for (i = 0; i < N; i++)
    a[i] = b[i]
```

***

### Program: Reversing a Series of Numbers

***reverse.c***

```txt
Enter 10 numbers: 34 82 49 102 7 94 23 11 50 31
In reverse order: 31 50 11 23 94 7 102 49 82 34
```

```C
// Reverses a series of numbers

#include <stdio.h>

#define N 10

int main(void) {
    int a[N], i;

    printf("Enter %d numbers: ", N);
    for (i = 0; i < N; i++)
        scanf("%d", &a[i]);
    
    printf("In reverse order:");
    for (i = N - 1; i >= 0; i--)
        printf(" %d", a[i]);

    return 0;
}
```

Pay attention to how useful the Macro N is in this program, we utilise it 4 times in different places and can change the maximum number of elements in the array simply by modifying N's value. Everything else will change to fit.

***

### Array Initialisation

