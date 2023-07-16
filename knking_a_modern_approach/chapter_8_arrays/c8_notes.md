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

The `sizeof` operator can determine the size of an array (in bytes).

We can also use `sizeof` to measure the size of an array element. Dividing the array size by the element size gives the length of the array.

```C
sizeof(a) / sizeof(a[0])

...
// clearing an array with sizeof
for (i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    a[i] = 0;
```

On some compulers this will produce a warning message for `i < sizeof(a) / sizeof(a[0])`. This is because `i` likely has a signed `int` type, whereas `size_t` is unsigned. We know this can be a dangerous practice, although in this case it's safe because `i` and `sizeof(a) / sizeof(a[0])` have nonnegative values.

```C
// avoid the warning with an explicit cast!
for (i = 0; i < (int) (sizeof(a) / sizeof(a[0])); i++)
    a[i] = 0;
```

This is quite unwieldy, we can represent it as a macro.

```C
#define SIZE ((int) (sizeof(a) / sizeof(a[0])))

for (i = 0; i < SIZE; i++)
    a[i] = 0;
```

If we still need to use a macro, what's the benefit of this approach over a `BUFF_SIZE` one? With the macro approach, we can actually create it with parameters; but this won't be a thing we look at until chapter 14.

***

### Program: Computing Interest

```txt
Enter interest rate: 6
Enter number of years: 5

Years     6%      7%      8%      9%     10%
  1     106.00  107.00  108.00  109.00  110.00
  2     112.36  114.49  116.64  118.81  121.00
  3     119.10  122.50  125.97  129.50  133.10
  4     126.25  131.08  136.05  141.16  146.41
  5     133.82  140.26  146.93  153.86  161.05
```

```C
// /interest.c/
// prints a table of compound interest

#include <stdio.h>

#define NUM_RATES ((int) (sizeof(value) / sizeof(value[0])))
#define INITIAL_BALANCE 100.00

int main(void)
{
    int i, low_rate, num_years, year;
    double value[5];

    printf("Enter interest rate: ");
    scanf("%d", &low_rate);
    printf("Enter number of years: ");
    scanf("%d", &num_years);

    printf("\nYears");
    for (i = 0; i < NUM_RATES; i++) {
        printf("%6d%%", low_rate + i);
        value[i] = INITIAL_BALANCE;
    }
    printf("\n");

    for (year = 1; year <= num_years; year++) {
        printf("%3d    ", year);
        for (i = 0; i < NUM_RATES; i++) {
            value[i] += (low_rate + i) / 100.00 * value[i];
            printf("%7.2f", value[i]);
        }
        printf("\n");
    }
    return 0;
}
```

***

## Multidimensional Arrays

An array may have any number of dimensions. The following declaration creates a two-dimensional array or *matrix* with 5 rows and 9 columns. Both are indexed from 0:

```C
int m[5][9];
```

```txt
    0   1   2   3   4   5   6   7   8
0   []  []  []  []  []  []  []  []  []
1   []  []  []  []  []  []  []  []  []
2   []  []  []  []  []  []  []  []  []
3   []  []  []  []  []  []  []  []  []
4   []  []  []  []  []  []  []  []  []
```

To access the element of `m` in row `i`, column `j`, we must write `m[i][j]`. The expression `m[i]` designates row `i` of `m` and `m[i][j]` then selects element `j` in this row. This essentially means you're thinking in terms of `m[y][x]`.

Although we visualise two-dimensional arrays as tables, that's not how they're stored in memory. C stores arrays in row-major order, with row 0 first, then row 1, and so forth.

```txt
      ROW 0            ROW 1                ROW4
  [ ][ ][ ][ ] ... [ ][ ][ ][ ] ... ... [ ][ ][ ][ ]
[0][0]    [0][4]  [1][0]               [4][0]
```

Typically we ignore this, but sometimes it will affect our code.

Nested for loops are ideal for processing multidimensional arrays. Consider the problem of making an identity matrix. These have 1's on the main diagonal, and 0's everywhere else. A pair of nested for loops; one that steps through every row index and one that steps through every column index, can accomplish our goal.

```C
#define N 10

double ident[N][N];
int row, col;

for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
        if (row == col)
            ident[row][col] = 1.0;
        else
            ident[row][col] = 0.0;
```

Multidimensional arrays play a minor role in C, because in C you're provided with a more flexible way to store multidimensional data in the form of arrays of pointers. 

***

### Initialising a Multidimensional Array

We can create an initialiser for a two-dimensional array by nesting one-dimensional initialisers:

```C
int m[5][9] = {{1, 1, 1, 1, 1, 0, 1, 1, 1},
               {0, 1, 0, 1, 0, 1, 0, 1, 0},
               {0, 1, 0, 1, 0, 1, 0, 1, 0},
               {1, 1, 0, 1, 0, 0, 0, 1, 0},
               {1, 1, 0, 1, 0, 0, 1, 1, 1}};
```

There are ways to abbreviate initialisers for multidimensional arrays:

If an initialiser isn't large enough to fill a multidimensional array, the remaining elements are given the value 0:

```C
int m[5][9] = {{1, 1, 1, 1, 1, 0, 1, 1, 1},
               {0, 1, 0, 1, 0, 1, 0, 1, 0},
               {0, 1, 0, 1, 0, 1, 0, 1, 0}};
```

If an inner list isn't long enough to fill a row, the remaining elements in the row are initialised to 0.

```C
int m[5][9] = {{1, 1, 1, 1, 1, 0, 1, 1, 1},
               {0, 1, 0, 1, 0, 1, 0, 1},
               {0, 1, 0, 1, 0, 1, 0, 1},
               {1, 1, 0, 1, 0, 0, 0, 1},
               {1, 1, 0, 1, 0, 0, 1, 1, 1}};
```

We can even omit the inner braces; once the compiler has seen enough values to fill one row, it begins filling the next.

```C
int m[5][9] = {1, 1, 1, 1, 1, 0, 1, 1, 1,
               0, 1, 0, 1, 0, 1, 0, 1, 0,
               0, 1, 0, 1, 0, 1, 0, 1, 0,
               1, 1, 0, 1, 0, 0, 0, 1, 0,
               1, 1, 0, 1, 0, 0, 1, 1, 1};
```

This is a risky strategy, since an extra element (or a missing element) will fuck up the rest of the initialiser. Some compilers will warn you about `missing braces around initialiser`.

C99's designated initialisers work with mulidimensional arrays. For example, we could create a 2x2 identity matrix with them; as usual all elements with no specified value will default to zero.

```C
double ident [2][2] = {[0][0] = 1.0, [1][1] = 1.0};
```

***

### Constant Arrays

Any array, whether one or multidimensional, can be made "constant" by starting its declaration with the word `const`.

```C
const char hex_char[] =
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
     'A', 'B', 'C', 'D', 'E', 'F'};
```

This helps the compiler catch errors, by informing it we don't intend to modify the array it can inform us when we attempt to.

***

### Program: Dealing a Hand of Cards

```txt
Enter number of cards in hand: 5
Your hand: 7c 2s 5d as 2h
```

It's not immediately obvious how we'd write such a program. How do we pick cards randomly from the deck? How do we avoid picking the same card twice? 

- To pick cards randomly, we'll use several C library functions. The `time` function (`<time.h>`) returns the current time, encoded in a single number. The `srand` function (`<stdlib.h>`) initialises C's random number generator. Passing the return value of `time` to `srand` seeds it to prevent the same cards being drawn every time.
- To avoid picking the same card twice, we'll need to keep track of those already chosen. For that purpose, we'll use an array named `in_hand` that has a row for each suit and 13 columns for each rank.
- Once we've verified that a card is not alrady selected we'll need to translate its numerical rank and suit into characters, then display the card.

deal.c

```C
// Deals a random hand of cards

#include <stdbool.h>    // C99 only
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SUITS 4
#define NUM_RANKS 13

int main(void)
{
    bool in_hand[NUM_SUITS][NUM_RANKS] = {false};
    int num_cards, rank, suit;
    const char rank_code[] = {'2', '3', '4', '5', '6', '7', '8', 
                              '9', 't', 'j', 'q', 'k', 'a'};
    const char suit_code[] = {'c', 'd', 'h', 's'};

    srand((unsigned) time(NULL));

    printf("Enter number of cards in hand: ");
    scanf("%d", &num_cards);

    printf("Your hand:");
    while (num_cards > 0) {
        suit = rand() % NUM_SUITS;  // picks a random suit
        rank = rand() % NUM_RANKS;  // picks a random rank
        if (!in_hand[suit][rank]) {
            in_hand[suit][rank] = true;
            num_cards--;
            printf(" %c%c", rank_code[rank], suit_code[suit]);
        }
    }
    printf("\n");

    return 0;
}
```

***


## Variable-Length Arrays (C99)

In C99, it's sometimes possible to use an expression that's *not* constant. The following modification of the `reverse.c` program illustrates this ability:

reverse2.c

```C
// Reverses a series of numbers using a variable-length array - C99 Only

#include <stdio.h>

int main(void)
{
    int i, n;

    printf("How many numbers do you want to reverse? ");
    scanf("%d", &n);

    int a[n];   // C99 only, length of array depends on n

    printf("Enter %d numbers: ", n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("In reverse order:");
    for (i = n - 1; i >= 0; i--)
        printf(" %d", a[i]);
    printf("\n");

    return 0;
}
```

The array `a` in this program is an example of a ***variable-length array*** (or ***VLA*** for short). The length of a VLA is computed when the program is executed, not when the program is compiled.

The chief advantage of a variable length array is that the programmer doesn't have to pick an arbitrary length that is likely to either waste memory or cause an access out of bounds error.

The length of an array doesn't have to be specified by a single varaible, arbitrary expressions possibly containing operators are also legal.

```C
int a[3*i+5];
int b[j+k];

// multidimensional VLAs
int c[m][n]
```

The primary restrictions on VLAs are that

- a VLA can't have static storage duration
- a VLA may not have an initialiser

They're seen most often in functions other than `main`. One big advantage of a VLA that belongs to a function `f` is that it can have a different length each time `f` is called. We'll explore this feature more in Section 9.3.

***

### Using a Character as an Array Subscript

We can't use the letters to subscript `letter_count` directly, because their integers values don't fall between 0 and 25. To scale a lowe-case letter to the proper range, we can simply subtract `'a'`: to scale an upper case letter we'll subtract `'A'`. 

```C
letter_count[ch-'a'] = 0;
```

This approach only works with character sets that encode consecutively, like ASCII.

***

### Copying Arrays

```C
// ILLEGAL
a = b;

// copy one array into another with loops
for (i = 0; i < N; i++)
    a[i] = b[i]

// using memcopy from <string.h>
memcpy(a, b, sizeof(a));
```

Many programmers prefer to use the `memcpy` approach, especially for larger arrays, because they're potentially faster than an ordinary loop.

***