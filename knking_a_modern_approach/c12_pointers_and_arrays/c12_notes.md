# Chapter 12: Pointers and Arrays

> *Optimisation hinders evolution.*

When pointers point to array elements, C allows us to perform arithmetic on the pointers, which leads to an alternative way of precessing arrays where pointers take the place of array subscripts.

One thing to be aware of is that one of the primary reasons people used array arithmetic was that it was more efficient; however now (in 2008) compilers have improved to the extent that this is less of a factor, and so pointer arithmetic is relatively less important for efficiency.

## 12.1 Pointer Arithmetic

Suppose that `a` and `p` have been declared: `int a[10], *p;` we can make `p` point to `a[0]` by writing `p = &a[0];` which means We can now access `a[0]` through `p`. 

e.g. we can store the value 5 in `a[0]` by writing: `*p = 5`.

Making a pointer `p` point to an element of an array isn't particular groundbreaking. By performing ***pointer arithmetic*** (address arithmetic) on `p`, we can access the other elements of `a`. C supports 3 forms of pointer arithmetic:

- Adding an integer to a pointer
- Subtracting an integer from a pointer
- Subtracting one pointer from another

The following examples assume:

```C
int a[10], *p, *q, i;
```

### Adding an Integer to a Pointer

Adding an integer `j` to a pointer `p` yields a pointer to the element `j` places after the one that `p` points to. If `p` points to the array element `a[i]` then `p+j` points to `a[i+j]` if it exists.

```C
int *p, a[10] = {0};

p = &a[2];      /*          [p]
                             v 
                     a[0][1][2][3][4][5][6][7][8][9]
                */  
q = p + 3;      /*          [p]      [q]
                             v        v
                     a[0][1][2][3][4][5][6][7][8][9]
                */  
p += 6;         /*                   [q]      [p]
                                      v        v
                     a[0][1][2][3][4][5][6][7][8][9]         
                */  
```

### Subtracting an Integer from a Pointer

If `p` points to the array element `a[i]`, then `p-j` points to `a[i-j]`.

```C
int *p, a[10] = {0};

p = &a[8];      /*                            [p]
                                               v 
                     a[0][1][2][3][4][5][6][7][8][9]
                */  
q = p - 3;      /*                   [q]      [p]
                                      v        v
                     a[0][1][2][3][4][5][6][7][8][9]
                */  
p -= 6;         /*          [p]      [q]
                             v        v
                     a[0][1][2][3][4][5][6][7][8][9]         
                */  
```

### Subtracting One Pointer from Another

When one pointer is subtracted from another, the result is the distance (measured in array elements) between the pointers. Thus, if `p` points to `a[i]` and `q` points to `a[j]`, then `p-q` is equal to `i-j`.

```C
int *p, *q, a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

p = &a[5];      //      [q]         [p]
q = &a[1];      //       v           v
                //  a[0][1][2][3][4][5][6][7][8][9]

i = p - q;      //  i is 4
i = q - p;      //  i is -4
```

> Performing arithmetic on a pointer that doesn't point to an array element causes undefined behaviour. Furthermore, the effect of subtracting one pointer from another is undefined unless both point to elements of the *same* array.

### Comparing Pointers

We can compare pointers using the relational (<, <=, >, >=) and equality (==, !=) operators. These are only meaningful when both point to elements of the same array. The outcome depends on their relative positions within the array.

```C
p = &a[5];      // p <= q == 0
q = &a[1];      // p >= q == 1
```
 
### Pointers to Compound Literals

It's legal for a pointer to point to an element within an array created by a compound literal. A compound literal is a C99 feature that can be used to create an array with no name.

```C
int *p = (int []){3, 0, 3, 4, 1};
```

`p` points to the first element of a five-element array containing the integers 3, 0, 3, 4 and 1. Using a compound literal saves us the trouble of first declaring an array variable and then making `p` point to the first element of that array.

```C
int a[] = {3, 0, 3, 4, 1};
int *p = &a[0];
```

## 12.2 Using Pointers for Array Processing

Pointer arithmetic allows us to visit the elements of an array by repeatedly incrementing a pointer variable. 

In the following example, `p` initially points to `a[0]`, and is incremented every loop. The loop terminates when `p` steps past the last element of `a`.

```C
#define N 10
...
int a[N], sum, *p;
...
sum = 0;
for (p = &a[0]; p < &a[N]; p++)
    sum += *p;
```

The condition `p < &a[N]` in the `for` statement deserves special attention, as it may seem very strange to apply the address operator to `a[N]`, which actually can't exist.

Using `&a[N]` in this fashion is perfectly safe, since the loop doesn't actually ever attempt to read its value. The body of the loop will be executed with `p` equal to `&a[0]`, ... , `&a[N-1]`, but when `p` is equal to `&a[N]` the loop terminates.

> *We could just as easily have written this without pointers, using subscripting instead. The argument most often cited in support of pointer arithmetic is that it can save execution time, but that actually depends on the implementation. Some C compilers actually produce better code for loops that rely on subscripting.*

### Combining the `*` and `++` Operators

C programmers often combine the `*` (indirection) and `++` operators in statements that process array elements. If we wanted to store a value into an array element and then advance to the next one normally, we might write:

```C
a [i++] = j;
```

However, there are a few different combinations of `*` and `++` that can mean drastically different things you don't want to mess up with. 

|     Expression     |                            Meaning                                 |
| :----------------: | :----------------------------------------------------------------: |
| `*p++` or `*(p++)` | Value of expression is `*p` before incremenet; increment `p` later |
| `(*p)++`           | Value of expression is `*p` before increment; increment `*p` later |
| `*++p` or `*(++p)` | Increment `p` first, value of expression is `*p` after increment   |
| `++*p` or `++(*p)` | Increment `*p` first; value of expression is `*p` after increment. |

All four combinations appear in programs, although some are far more common than others. The one we'll see most frequently is `*p++` which is useful for loops.

```C
// boring, lame, shit
for (p = &a[0]; p < &a[N]; p++)
    sum += *p;

// we can instead write
p = &a[0];
while (p < &a[N]) sum += *p++;
```

The `*` and `--` operators mix in the same was as `*` and `++`. For an application that combines `*` and `--`, let's return to the stack example of **C10.2**. Originally we used `int top` to keep track of the top position in the array. Let's instead use a pointer variable that initially points to element 0 of the array.

```C
int *top_ptr = &contents[0];

void push(int i)
{
    if ( is_full() ) stack_overflow();
    else             *top_ptr++ = i;        
    // increment after placing value
}

int pop(void)
{
    if ( is_empty() ) stack_underflow();
    else              return *--top_ptr;     
    // decrement before fetching value
}
```

I think if I was writing this API, I'd rearrange it to make it more visually appealing.

```C
void push(int i)
{
    if ( !full() ) *top_ptr++ = i;
    else stack_overflow();
}

int pop(void)
{
    if ( !empty() ) return *--top_ptr;
    else stack_underflow();
}
```

## 12.3 Using an Array Name as a Pointer

Pointer arithmetic is one way in which arrays and pointers are related, but it's not the only connection between the two. *The name of an array can be used as a pointer to the first element in the array.* This relationship simplifies pointer arithmetic and makes both arrays and pointers more versatile.

```C
int a[10];

*a = 7;         // stores 7 in a[0]
*(a+1) = 12;    // stores 12 in a[1]
```

In general, `a+i` is the same as `&a[i]` (both represent a pointer to element `i` of `a`) and `*(a+i)` is equivalent to `a[i]` (both represent element `i` itself). In other words, array subscripting can actually be seen as a form of pointer arithmetic.

The fact that an array name can serve as a pointer makes it easier to write loops that step through an array. Consider the simplified form of an earlier loop from 12.2:

```C
// array subscripting
for (p = &a[0]; p < &a[N]; p++)
    sum += *p;

// pointer arithmetic
for (p = a; p < a + N; p++)
    sum += *p;
```

> *Although an array name can be used as a pointer, it's not possible to assign it a new value. Attempting to make it point elsewhere is an error. However, we're always free to copy `a` into a pointer variable, and then change that variable.*
>
> ```C
> while (*a != 0) a++;              // WRONG!
>
> p = a;
> while (*p != 0) p++;              // IMPROVED!
>
> for (p = a; *p != 0; p++)
>   ;                               // BASED!
> ```

### Program: Reversing a Series of Numbers (Revisited)

The `reverse.c` program of Chapter 8.1 reads 10 numbers, then writes the numbers in reverse order. As the program reads the numbers, it stores them in an array. Once all the numbers are read, the program steps through the array backwards as it prints the numbers.

The original program used subsscripting to acces elements of the array.

```C
// reverse3.c
// reverses a series of numbers (pointer version)

#include <stdio.h>

#define N 10

int main(void)
{
    int a[N], *p;

    printf("Enter %d numbers: ", N);
    for (p = a; p < a + N; p++)
        scanf("%d", p);

    printf("In reverse order:");
    for (p -= 1; p >= a; p--)
        printf(" %d", *p);

    printf("\n");

    return 0;
}
```

Note that the second argument to `scanf` is `p`, not `&p`; this is because `p` points to an array element and is therefore a pointer to an `int`.

### Array Arguments (Revisited)

When passed to a function, an array name is always treated as a pointer. Consider the following function, which returns the largest element in an array of integers:

```C
int find_largest(int a[], int n)
{
    int i, max;

    max = a[0];
    
    for (i = 1; i < n; i++)
        if (a[i] > max) max = a[i];
    
    return max;
}
```

When  we call `int max = find_largest(b, N);` we cause a pointer to the first element of `b` to be assigned to `a`; ***the array itself is not copied***. The fact that an array argument is treated as a pointer has some important consqeuences.

- **When an array is used as an argument, it isn't protected against change** <br>To indicate that an array parameter won't be changed, we can include the word `const` in its declaration: the compiler will check that no assignment to an element of `a` appears:  <br>`int find_largest(const int a[], int n) { ... }`
- **The time required to pass an array to a function doesn't depend on the size of the array.**<br>There's no penalty for passing a large array, since no copy of the array is made.
- **An array parameter can be declared as a pointer if desired.** <br>For example, `find_largest` could be declared `int find_largest(int *a, int n)` and the compiler would treat them as though they were identical.
- **A function with an array parameter can be passed an array "slice" - a sequence of consecutive elements.** <br>Suppose that we can `find_largest` to locate the largest element in some portion of an array `b`, say elements `b[5]`, ..., `b[14]`. When we call `find_largest`, we'll pass it the address of `b[5]` and the number `10`, indicating that we want `find_largest` to examine 10 array elements starting at `b[5]`: <br>`max = find_largest(&b[5], 10);`


> *Although declaring a parameter to be an array is the same as declaring it to be a pointer, the same isn't true for a variable. The declaration `int a[10];` causes the compiler to set aside space for 10 integers. In contrast, the declaration `int a*;` causes the compiler to allocate space for a pointer variable.*
>
> *In the latter case, `a` is not an array; attempting to use it as an array can have disastrous results. For example, the assignment `*a = 0;` will store 0 where `a` is pointing. Since we don't know where that is, this causes undefined behaviour.*

### Using a Pointer as an Array Name

If we can use an array name as a pointer, will C allow us to subscript a pointer as though it were an array name? As you'd expect, the answer is a resounding yes.

```C
#define N 10
...
int a[N], i, sum = 0, *p = a;
...
for (i = 0; i < N; i++)
    sum += p[i];
```

The compiler treats `p[i]` as `*(p+i)`, which is a perfectly legal use of pointer arithmetic. We'll see in Chapter 17.3 that this is a very useful ability.

## 12.4 Pointers and Multidimensional Arrays

Just as pointers can point to elements of on-dimensional arrays, they can also point to elements of multidimensional arrays. For simplicity, we'll only look at two-dimensional arrays, but the use of higher-dimensional arrays is left as an exercise to the reader.

### Processing the Elements of a Multidimensional Array
We saw in section 8.2 that C stores 2-d arrays in row-major order; in other words, the elements of row 0 come first, followed by the elements of two 1, and so forth. An array with $r$ rows would have the following appearance:

```txt
 v-- row 0 --v  v-- row 1 --v       v- row r-1 -v
[   ][...][   ][   ][...][   ] ... [   ][...][   ]
```

We can use pointers to take advantage of this layout. If we make a pointer `p` point to the first element in a two-dimensional array (the element in row 0, column 0), we can visit every element in the array by incrementing p repeatedly.

```C
int a[NUM_ROWS][NUM_COLS];

// obvious approach
int row, col;
for (row = 0; rol < NUM_ROWS; row++)
    for (col = 0; col < NUM_COLS; col++)
        a[row][col] = 0;

// single-loop pointer approach
int p*;
...
for (p = &a[0][0]; p <= &a[NUM_ROWS-1][NUM_COLS-1]; p++)
    *p = 0;
```

Although treating a two-dimensional array as one-dimensional may seem like cheating, it works with most C compilers. Whether or not this is a good idea is another matter. Techniques like this hurt readability, but with some older compilers actually produce a compensating increase in efficiency.

With modern compilers, there's often little or no speed advantage.

### Processing the Rows of a Multidimensional Array

If we wanted to process the elements in just one row of a 2d array, we again have the option of using a pointer variable `p`. To visit the elements of row `i`, we've initialise `p` to element `0` in row `i` in the array `a`:

```C
p = &a[i][0];

// or:

p = a[i];
```

For any two-dimensional array `a`, the expression `a[i]` is a pointer to the first element in row `i`. Recall that for any array `a`, the expression `a[i]` is equivalent to `*(a+i)`. Thus, `&a[i][0]` is the same as `&(*(a[i] + 0))`, which is equivalent to `&*a`, which is the same as `a[i]` since the `&` and `*` operators cancel.

```C
int a[NUM_ROWS][NUM_COLS], *p, i;
...
for (p = a[i]; p < a[i] + NUM_COLS; p++)
    *p = 0;
```

Since `a[i]` is a pointer to row `i` of the array `a`, we can pass `a[i]` to a function that's expecting a one-dimensional array as its argument. In other words, a function that's designed to work with one-dimensional arrays will also work with a row belonging to a two-dimensional array.

As a result, functions such as `find_largest` and `store_zeros` are more versatile than you might expect. Consider `find_largest`; we can just as easily use it to determine the largest element in row `i` of the two-dimensional array a:

```C
largest = find_largest(a[i], NUM_COLS);
```

### Processing the Columns of a Multidimensional Array

Processing the elements in a *column* of a two-dimensional array isn't quite as easy because arrays are stored by row, not by column.

```C
int a[NUM_ROWS][NUM_COLS], (*p)[NUM_COLS], i;
...
for (p = &a[0]; p < &a[NUM_ROWS]; p++)
    (*p)[i] = 0;
```

`p` is declared to be a pointer to an array of length `NUM_COLS` whose elements are integers. The parentheses around `*p` in `(*p)[NUM_COLS]` are required; without them the compiler would treat `p` as an array of pointers instead of a pointer to an array!

The expression `p++` advances `p` to the beginning of the next row. In the expression `(*p)[i]`, `*p` represents an entire row of `a`, so `(*p)[i]` selects the element in column `i` of that row. The parenthese in `(*p)[i]` are essential, because the compiler would interpret `*p[i]` as `*(p[i])`.

### Using the Name of a Multidimensional Array as a Pointer

Just as the anme of a one-dimensional array can be used as a pointer, so can the name of *any* array, regardless of how many dimensions it has. Some care is required though. 

Consider the following array: `int a[NUM_ROWS][NUM_COLS];` `a` is *not* a pointer to `a[0][0]`; instead it's a pointer to `a[0]`. This makes more sense if we consider that C doesn't think about multidimensional arrays at all; it sees it as a one-dimensional array whose elements are one-dimensional arrays.

When used as a pointer, `a` has type int `(*)[NUM_COLS]`; pointer to an integer array of length `NUM_COLS`. This is useful for simplifying loops that process the elements of 2d arrays. 

```C
// original
for (p = &a[0]; p < &a[NUM_ROWS]; p++)
    (*p)[i] = 0;

// new style
for (p = a; p < a + NUM_ROWS; p++)
    (*p)[i] = 0;
```

This can also come in handy when we want to "trick" a function into thinking that a multidimensional array is really one dimensional.

For example, consider how we might use `find_largest` to find the largest element in `a`. As the first argument to `find_largest`, let's try passing `a` (the address of the array); as the second we'll pass `NUM_ROWS * NUM_COLS` (the total number elements in `a`).

```C
largest = find_largest(a, NUM_ROWS * NUM_COLS);   // WRONG!
```

The compiler will object to this statement, because the type of `a` is `int(*)[NUM_COLS]`, but `find_largest` is expecting an argument of type `int *`. The correct call is:

```C
largest = find_largest(a[0], NUM_ROWS * NUM_COLS);
```

as `a[0]` points to element 0 in row 0, and it has type `int *` (after conversion by the compiler) so the latter call will still work correctly.

## 12.5 Pointers and Variable-Length Arrays (C99)

Pointers are allowed to point to elements of variable length arrays (VLAs), a feature of C99. An ordinary pointer variable would be used to point to an element of a one-dimensional VLA;

```C
void f(int n)
{
    int a[n], *p;
    p = a;
    ...
}
```

When the VLA has more than one dimension, the type of the pointer depends on the length of each dimension except for the first. Let's look at a 2d case;

```C
void f(int m, int n)
{
    int a[m][n], (*p)[n];
    p = a;
    ...
}
```

Since the type of `p` depends on `n`, which isn't constant, `p` is said to have a ***variably modified type***. Note that the validity of an assignment such as `p = a` can't always be determined by the compiler. For example, the following code will compile but is incorrect if `m` and `n` are not equal.

```C
int a[m][n], (*p)[m];
p = a;
```

If $m \neq n$ any subsequent use of `p` will caus eundefined behaviour.

Variably modified types  must be inside the body of a function or in a function prototype. Pointer arithmetic works with VLAs just as it does for ordinary arrays. Returning to **12.4**, let's declare `a` as a VLA this time:

```C
// Variable Length Array
int a[m][n];

// Pointer to row of a
int (*p)[n];

// loop that clears column i
for (p = a; p < a + m; p++)
    (*p)[i] = 0;
```

## Q&A: Pointers & Arrays

> ***If a pointer is an address, does that mean that an expression like `p + j` adds `j` to the address stored in `p`?***
>
> No, integers used in pointer arithmetic are scaled depending on the type of the pointer. If `p` is of type `int *`, then `p + j` typically adds $4 \times$ `j` to `p`, assuming that `int` values are stored using 4 bytes. If `p` has the type `double *`, the `p + j` will probably add $8 \times$ `j` to `p`, since `double` values are usually 8 bytes long.

> ***When writing an array traversal loop, is it better to use array subscripting or pointer arithmetic?***
>
> There's no easy answer, but for the most part unless you're working on a PDP-11 it basically doesn't make any difference in terms of performance. Learn both ways and use whichever is more natural for the kind of program you're writing.

> ***I read somewhere that `i[a]` is the same as `a[i]`; is this true?***
>
> Yes, oddly enough. The compiler treats `i[a]` as `*(i + a)`, which is the same as `*(a + i)`, which is equivalent to `a[i]`. Pointer addition, like regular addition, is commutative. However, this is a very odd thing to do and will confuse anyone reading your code.

> ***Is it better style to declare an array parameter as \*a or `a[]`?***
>
> Some programmers switch between `*a` and `a[]` depending on whether the function uses pointer arithmetic or subscripting to access the elements of the array. In practice, `*a` is far more common than `a[]`, so you'd better get used to it. Dennis Ritchie refers to the `a[]` notation as "a living fossil" that "serves as much to confuse the learner as to alert the reader".

## Written Exercises: Pointers & Arrays

### 1. Suppose that the following declarations are in effect:

```C
int a[] = {5, 15, 34, 54, 14, 2, 52, 72};
int *p = &a[1], *q = &a[5];
```

...

| Q | What is the value of: | Answer |
| - | :-------------------: | :----: |
| 1.| `*(p + 3)`            | 14     |
| 2.| `*(q - 3)`            | 34     |
| 3.| `q - p`               | 4      |
| 4.| `p < q`               | TRUE   |
| 5.| `*p < *q`             | FALSE  |

### 2. Suppose that `high`, `low`, and `middle` are all pointer variables of the same type, and that `low` and `high` point to elements of an array. Why is the following statement illegal, and how could it be fixed?

```C
middle = (low + high) / 2;
```

...

The memory address of `low + high` is some random memory address we might not want to modify anything in beyond the end of our selection. Dividing this memory offset by an integer means very little to the compiler.

Instead, we can work out the length of the slice by subtracting `low` from `high`, and then divide this quantity by 2 to get half the length of the slice. We then add this half-length to `low`, which offsets middle by half the array length.

```C
middle = low + (high - low / 2);
```

### 3. What will be the contents of the `a` array after the following statements are executed?

```C
#define N 10

int a[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int *p = &a[0], *q = &a[N-1], temp;

while (p < q) {
    temp = *p;
    *p++ = *q;
    *q-- = temp;
}
```

...

```C
temp = a[0];    // temp == 1
(*p)++ = *q     // a[0] == 10; p == &a[1]
(*q)-- = temp;  // a[9] == 1; q == &a[8]
```

The program reverses the array!

### 4. Rewrite the `make_empty`, `is_empty` and `is_full` functions of section 10.2 to use the pointer variable `top_ptr` instead of the integer variable `top`

```C
// section 10.2
#include <stdbool.b>

#define STACK_SIZE 100

// external variables
int contents[STACK_SIZE];
int top = 0;

void make_empty(void) {
    top = 0;
}

bool is_empty(void) {
    return top == 0;
}

bool is_full(void) {
    return top == STACK_SIZE;
}
```

...

```C
// STACK STRUCTURE w/ POINTERS
#include <stdbool.h>
#define STACK_SIZE 100

int contents[STACK_SIZE];
int *top_ptr = contents;

void make_empty(void) {
    top_ptr = contents;
}

bool is_empty(void) {
    return top == contents;
}

bool is_full(void) {
    return top >= contents + STACK_SIZE;
}
```

### 5. Suppose that `a` is a one-dimensional array and `p` is a pointer variable

Assuming that the assignment `p = a` has just been performed, which of the following expressions are illegal because of mismatched types? Of the remaining expression, which are true? (Have a non-zero value...)

...

| Q | Expression     | Legal?                                 | True? |
| - | -------------- | -------------------------------------- | ----- |
| a | `p == a[0]`    | NO - a[0] is an `int`                  | xxx   |
| b | `p == &a[0]`   | YES - both pointers to `int`           | YES   |
| c | `*p == a[0]`   | YES - `int` can be compared with `int` | YES   |
| d | `p[0] == a[0]` | YES - pointers & arrays are similar    | YES   |

### 6. Rewrite the following function to use pointer arithmetic instead of array subscripting

In other words, eliminate the variable i and all uses of the [] operator. Make as few changes as possible.

```C
int sum_array(const int a[], int n)
{
    int i, sum;

    sum = 0;
    
    for (i = 0; i < n; i++)
        sum += a[i]
    
    return sum;
}
```

...

```C
int sum_array(const int *a, int n)
{
    int *p, sum;

    sum = 0;

    for (p = a; p < a + n; p++)
        sum += *p;

    return sum;
}
```

### 7. Write the following function: `bool search(const int a[], int n, int key);`

`a` is an array to be searched, `n` is the number of elements in the array, and `key` is the search key. `search` should return `true` is `key` matches some element of `a` and `false` if it doesn't. 

Use pointer arithmetic, not subscripting, to visit array elements.

...

```C
#include <stdbool.h>

bool search(const int a[], int n, int key)
{
    int *p = a;

    while (p < a + n) 
        if (*p++ == key) return true;
    
    return false;
}
```

### 8. Rewrite the following function to use pointer arithmetic instead of array subscripting

In other words, eliminate the variable `i` and all of the uses of the `[]` operator. Make as few changes as possible.

```C
void store_zeros(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        a[i] = 0;
}
```

...

```C
void store_zeros(int a*, int n)
{
    int *p;
    for (p = a; p < a + n; p++)
        *p = 0;
}
```

### 9. Write the following function: `double inner_product(const double *a, const double *b, int n);`

`a` and `b` both point to arrays of length `n`. The function should return `a[0] * b[0] + a[1] + b[1] + ... + a[n-1] * b[n-1]`. Use pointer arithmetic, not subscripting, to visit array elements.

...

```C
double inner_product(const double *a, const double *b, int n)
{
    int sum = 0,
        *p = a, 
        *q = b;

    while (p < a + n && q < b + n)
        sum += (*p++) * (*q++);

    return sum;
}
```

### 10. Modify the `find_middle` function of Section 11.5 so that it uses pointer arithmetic to calculate the return value.

```C
// section 11.5:
int *find_middle(int a[], int n) {
    return &a[n/2];
}
```

...

```C
int *find_middle(int *a, int n) {
    return a + n / 2;
}
```

### 11. Modify the `find_largest` function so that is uses pointer arithmetic - not subscripting - to calculate the return value

```C
int find_largest(int a[], int n)
{
    int i, max;

    max = a[0];
    
    for (i = 1; i < n; i++)
        if (a[i] > max) max = a[i];
    
    return max;
}
```

...

```C
int find_largest(int *a, int n)
{
    int *p = a, max = *p;

    while (p < a + n) if (*p > max) max = *p++;

    return max; 
}
```

### 12. Write the following function: `void find_two_largest(const int *a, int n, int *largest, int *second_largest);`

`a` points to an array of length `n`. The function searches the array for its largest and second largest elements, storing them in the variables pointed to by `largest` and `second_largest`. Use pointer arithmetic, not subscripting, to visit array elements.

...

```C
void find_two_largest(const int *a, int n, int *largest, int *second_largest)
{
    int *p = a;
    
    largest = a;
    second_largest = a + n - 1;
    
    for (p = a; p < a + n; p++) {
        if (*p > *largest) {
            *second_largest = *largest;
            *largest = *p;
        }
        else if (*p > *second_largest) 
            *second_largest = *p;
    }
}
```

### 13. Section 8.2 had a program fragment in which two nested `for` loops initialised the array `ident` for use as an identity matrix. Rewrite this code, using a single pointer to step through the array one element at a time

Hint: Since we won't be using `row` and `col` index variables, it won't be easy to tell where to store 1. Instead, we can use the fact that the first element of the array should be 1, the next N elements should 0, the next element should be 1, and so on.

Use a variable to keep track of how many consecutive 0s have been stored, when the count reches N it's time to store 1.

```C
// section 8.2 ident
#define N 10

double ident[N][N];
int row, col;

for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
    {
        if (row == col) ident[row][col] = 1.0;
        else ident[row][col] = 0.0;
    }
```

...

```C
#define N 10

double ident[N][N],
       *p = ident;

for (int i = 0; p < ident + N * N; p++, i++) 
{
    if (i % N == 0) *p = 1.0;
    else            *p = 0.0;
}
```

### 14. Assume that the following array contains a week's worth of hourly temperature readings, with each row containing the readings for one day.

```C
int temperatures[7][24];
```

Write a statement that uses the `search` function (exercise 7) to search the entire `temperatures` array for the value 32.

```C
#include <stdbool.h>

bool search(const int a[], int n, int key)
{
    int *p = a;

    while (p < a + n) 
        if (*p++ == key) return true;
    
    return false;
}
```

...

```C
#define HOURS_IN_WEEK 7 * 24

search(*temperatures, HOURS_IN_WEEK, 32);
```

### 15. Write a loop that prints all temperature readings stored in row `i` of the `temperatures` array (see exercise 14) 

Use a pointer to visit each element of the row.

...

```C
#include <stdio.h>

#define HOURS_IN_DAY 24

int temperatures[7][24];

void print_temps_on_day(const int *a, int i) 
{
    printf("TEMPERATURES ON DAY %d", i);
    int *p = a + HOURS_IN_DAY * i;
    const int *q = p;
    
    while (p - q < 24)
        printf("TEMP AT %02d:00hrs: %d\n", p - a, *p++)
}
```

### 16. Write a loop that prints the highest temperature in the `temperatures` array for each day of the week

The loop body should call the `find_largest` function, passing it one row of the array at a time.

...

```C
#include <stdio.h>

#define HOURS_IN_DAY 24
#define DAYS_IN_WEEK 7

int temperatures[7][24];

int find_largest(int *a, int n)
{
    int *p = a, 
        max = *p;

    while (p < a + n) 
        if (*p > max) max = *p++;

    return max; 
}

void print_highest_temp_per_day(const int *a)
{
    printf("YOUR WEEKLY HIGHS: \n";)

    for (int i = 0; i < DAYS_IN_WEEK; i++)
        printf("%s:\t%d DEG C\n", day_string(i), find_largest(a[i], HOURS_IN_DAY));
}

char *day_string(int i)
{
    switch (i)
    {
    case 0: return "SUNDAY";
    case 1: return "MONDAY";
    case 2: return "TUESDAY";
    case 3: return "WEDNESDAY";
    case 4: return "THURSDAY";
    case 5: return "FRIDAY";
    case 6: return "SATURDAY";
    }
    return 0;
}
```

### 17. Rewrite the following function to use pointer arithmetic instead of array subscripting.

In other words, eliminate the variables `i` and `j` and all uses of the `[]` operator. Use a single loop instead of two nested loops.

```C
int sum_two_dimensional_array(const int a[][LEN], int n)
{
    int i, j, sum = 0;

    for (i = 0; i < n; i++)
        for (j = 0; j < LEN; j++)
            sum += a[i][j];

    return sum;
}
```

...

```C
int sum_2d_array(const int a[][LEN], int n)
{
    int *p = (int *) a,
        *end = p + n * LEN,
        sum = 0;

    while (p < end) sum += *p++;

    return sum;
}
```

### 18. Write the `evaluate_position` function described in C9_W13. Use pointer arithmetic, not subscripting, to visit array elements. Use a single loop instead of nested loops.

```C
// C9_W13
// starting position board; evaluate_position(start_board) should == 0;
char start_board[8][8] = {
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
}

int evaluate_position(char board[8][8])
{
    int white_sum = 0, 
        black_sum = 0;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) 
        {
            switch (board[i][j])
            {
            case 'Q': white_sum += 9; break;
            case 'q': black_sum += 9; break;
            
            case 'R': white_sum += 5; break;
            case 'r': black_sum += 5; break;

            case 'B': 
            case 'N': white_sum += 3; break;
            case 'b': 
            case 'n': black_sum += 3; break;

            case 'P': white_sum += 1; break;
            case 'p': black_sum += 1; break;

            default: break;
            }
        }

    return white_sum - black_sum;
}
```

...

```C
int evaluate_position(char board[8][8])
{
    int *p = (char *) board,
        *end = p + 8 * 8,
        sum = 0;

    while (p < end)
        switch(*p++)
        {
        case 'Q': sum += 9; break;
        case 'q': sum -= 9; break;
        
        case 'R': sum += 5; break;
        case 'r': sum -= 5; break;

        case 'B': /*    f-t    */
        case 'N': sum += 3; break;
        case 'b': /*    f-t    */
        case 'n': sum -= 3; break;

        case 'P': sum += 1; break;
        case 'p': sum -= 1; break;

        default: break;
        }

    return sum;
}
```