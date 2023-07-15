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

The rules for array initialisation are a bit involved, but the simplest ways we can tackle head on. The most common form of initialiser is a list of constant expressions enclosed in braces and separated by commas;

```C
int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
```

If the initialiser is shorter than the array, the remaining elements of the array are given the value `0`.

```C
int a[10] = {1, 2, 3, 4, 5, 6};
    // initial value of a is {1, 2, 3, 4, 5, 6, 0, 0, 0, 0}

int a[10] = {0};
    // initial value of a is {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
```

If an initialiser is present, the length of the array may be omitted:

```C
int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
```

as the compiler will use the length of the initialiser to determine how long the array is. The array still has a fixed number of elements, just as if we'd specified the length explicitly.

***

### Designated Initialisers

It's often the case that most of the variables in an array will be 0, and only a few specific ones have values. To avoid having to write out massive array initialisers full of zeros, which is error-prone and tedious, we can instead use C99's ***designated initialisers***.

```C
// the virgin manual: error-prone, looks dumb, tedious
int a[15] = {0, 0, 29, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 48};

// the chad designated: modern, slick, C99 approved
int a[15] = {[2] = 29, [9] = 7, [14] = 48};
```

Another benefit is that the order they're written in makes no different;

```C
// exactly equivalent to
int a[15] ={[9] = 7, [2] = 29, [14] = 48};
```

Designators must have integer constant expressions. If the array has length `n`, each designator must be between `0` and `n - 1`. However, if the length of thge array is omitted, a designator can be any nonnegative int. You can also mix-and-match with old style sequential and new-style designated techniques;

```C
int b[] = {[5] = 10, [23] = 13, [11] = 36, [15] = 29};
// has length 24 as the largest designator is [23]

int c[10] = {5, 1, 9, [4] = 3, 7, 2, [8] = 6};
// for all elements with no explicit value, 0 is assigned
```

***

### Program: Checking a Number for Repeated Digits

***repdigit.c***

```txt
Enter a number: 28212
Repeated digit

...

Enter a number: 123456
No repeated digit
```

```C
// checks numbers for repeated digits

#include <stdbool.h> // C99 only!
#include <stdio.h>

int main(void)
{
    bool digit_seen[10] = {false};
    int digit;
    long n;

    printf("Enter a number: ");
    scanf("%ld", &n);

    while (n > 0) {
        digit = n % 10;
        if (digit_seen[digit]) break;
        digit_seen[digit] = true;
        n /= 10;
    }

    if (n > 0)  printf("Repeated digit\n");
    else        printf("No repeated digit\n");
}
```

***

### Using the `sizeof` Operator with Arrays

