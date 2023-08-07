# Chapter 11: Pointers

> The 11th commandment was "Thou Shalt Compute" or "Thou Shalt Not Compute" - I forget which.

Pointers are one of C's most important - and most often misunderstood - features. Because of their importance, this will be the first of 3 chapters that focus specifically on pointers. This chapter covers the basics, chapters 12 and 17 will cover more advanced uses.

## 11.1 Pointer Variables

In most modern computers, main memory is divided into *bytes*, with each byte capable of storing eight bits of information:

```txt
[0][1][0][1][0][0][1][1]    (int) 83; (char) 'S';
```

Each byte has a unique *address* to distinguish it from the other bytes in memory. If the are $n$ bytes in memory, we can think of addresses as numbers that range from $0$ to $n - 1$.

An executable program consists of both code (machine instructions built from the C source) and data (variables in the original program). Each variable in the program occupies one or more bytes of memory:

| Address | Contents     |
| :-----: | :----------: |
|  `0`    | `[01010011]` |
|  `1`    | `[01110101]` |
|  `2`    | `[01110011]` |
|  `3`    | `[01100001]` |
|  `4`    | `[01101110]` |
|         |     ...      |
|  `n-1`  | `[01000011]` |

The address of the first byte is said to be the address of the variable. In the following figure, the variable `i` occupies the bytes at addresses 2000 and 2001, so `i`'s address is 2000:

```txt
        [ ... ]
2000    [  i  ] 
2001    [  i  ]
        [ ... ]
```

This is where pointers come in. Although addresses are represented by numbers, their range of values may differ from that of integers, so we can't necessarily store them in ordinary integer variables. We can however store them in special ***pointer variables***. 

When we store the address of a variable `i` in the pointer variable `p`, we say that `p` "points to" `i`. In other words, a pointer is nothing more than an address, and a pointer variable is just a variable that stores an address.

### Declaring Pointer Variables

A pointer is declared in the same way as a normal variable, but with the addition of an asterisk before the variable name.

```C
int *p;     // a pointer called p
```

This delcaration states that `p` is a pointer variable capable of pointing to *objects* of type `int`.

Pointer variables can appear in declarations alongside other variables:

```C
int i, j, a[10], b[20], *p, *q;
```

C requires that every pointer variable point only to objects of a particular type:

```C
int *p;     // points ONLY to integers
double *q;  // points only to doubles
char *r;    // points only to characters
```

There are no restrictions on what the referenced type may be. In fact, a pointer variable can even point to another pointer.

## The Address and Indirection Operators

C provides two operators designed specifically for use with pointers.

- to find the address of a variable, we use the `&` (***address***) operator.<br> If `x` is a variable, then `&x` is the address of `x` in memory.
- to gain access to the object that a pointer points to, we use the `*` (***indirection***) operator <br> If `p` is a pointer, then `*p` represents the object to which `p` currently points.

### The Address Operator

Declaring a pointer variable sets aside space for a pointer but doesn't make it point to an object; it's crucial to initialise `p` before we attempt to use it. It's also possible to initialise a pointer variable at the time we declare it; including in the same statement we declare the variable we're pointing at.

```C
int i, *p;
...
p = &i;
```

```C
int i;
int *p = &i;
```

```C
int i, *p = &i;
```

By assigning the address of `i` to the variable `p`, this statement makes `p` point to `i`.

```txt
p[-]--> i[ ? ]
```

### The Indirection Operator

Once a pointer variable points to an object, we can use the `*` (indirection) operator to access what's stored in the object. e.g. if `p` points to `i`, we can print the value of `i`:

```C
printf("%d\n", *p);     // displays the value of i, not the address of i
```

It might help to think of `*` as the inverse of `&`: applying `&` to a variable produces a pointer to the variable; applying `*` to the pointer takes us back to the original variable:

```C
j = *&i;    // same as j = i; !
```

As long as `p` points to `i`, `*p` is an ***alias*** for `i`. Not only does `*p` have the same value as `i`, but changing the value of `*p` also changes the value of `i`. 

```C
int p = &i;             // p[ --]--> i[ ? ]
i = 1;                  // p[ --]--> i[ 1 ]

printf("%d\n", i);      // prints 1
printf("%d\n", *p);     // also prints 1

*p = 2;                 // p[ --]--> i[ 2 ]

printf("%d\n", i);      // prints 2
printf("%d\n", *p);     // also prints 2
```

#### WARNING

 Never attempt to apply the indirection operator to an uninitialised pointer variable. If a pointer variable `p` hasn't been initialised, attempting to use the value of `p` in any way causes undefined behaviour. In the following example, the call of `printf` may print garbage, cause the program to crash, or have some other effect:

 ```C
 int *p;
 *p = 1;       // UNFORGIVABLE!
 ```

 If the location modified by this assignment belongs to the program, it can basically do anything. If it belongs to the OS, it'll likely crash. Pay attention to any warnings that the compiler gives about pointers not being initialised!

 ## 11.3 Pointer Assignment

 C allows the use of the assignment operator to copy pointers, provided that they have the same type. Suppose that `int i, j, *p, *q;` the statement `p = &i;` is an example of pointer assignment. The address of `i` is copied into `p`. 

 The statement `q = p;` copies the contents of `p` (the address of `i`) into `q`, in effect making `p` point to the same place as `p`:

 ```txt
 p[ --]--> i[ ? ] <--q[-- ]
 ```

Both `p` and `q` not point to `i`, so we can change `i` by assigning a new value to either `*p` or `*q`. Any number of pointer variables may point to the same object. Be careful not to confuse `q = p;` with `*q = *p;` the first statement is a pointer assignment, the second is not.

```C
p = &i;     // p[ --]--> i[ ? ]
q = &j;     // q[ --]--> j[ ? ]

i = 1;      // p[ --]--> i[ 1 ]

*q = *p;    // p[ --]--> i[ 1 ]
            // q[ --]--> j[ 1 ]
```

The assignment `*q = *p` copies the value that `p` points to (the value of `i`) into the object that `q` points to (the variable `j`).

## 11.4 Pointers As Arguments

What are pointers good for? There's no single answer to that question, since pointers have several distinct uses in C. In this section, we'll look at how a pointer to a variable can be useful as a function argument. 

We saw previously that a variable supplied as an argumen t in a function call is protected against change, because C passes arguments by value. This can be an issue if we want the function to be able to modify the variable, such as in the `decompose` function we tried in section 9.3.

Pointers offer us a solution to this problem: instead of passing a variable `x` as the argument to a function, we'll supply `&x`, a pointer to `x`. We'll declare the corresponding parameter `p` to be a pointer.

When the function is called, `p` will have the value `&x` hence `*p` (the object that `p` points to) will be an alias for x. Each appearance of `*p` in the body of the function will be an indirect reference to `x`, allowing the function to both read **and** modify `x`.

```C
// Prototype:
void decompose(double x, long *int_part, double *frac_part);
// or
void decompose(double, long *, double *);
```

```C
// Definition:
void decompose(double x, long *int_part, double *frac_part)
{
    *int_part = (long) x;
    *frac_part = x - *int_part;
}
```

```C
// Calling:
decompose(3.14159, &i, &d);
```

Because of the `&` operator in front of `i` and `d`, the arguments to decompose are ***pointers*** to `i` and `d`, not the values of `i` and `d`. When `decompose` is called, the value 3.14159 is copied into `x`, a pointer to `i` is stored in `int_part` and a pointer to `d` is stored in `frac_part`.

When `decompose` returns, `i` and `d` will have the values `3` and `.14159`, just as we originally wanted.

```txt
        x[3.41459]
 int_part[ --]-> i[ ? ]
frac_part[ --]-> d[ ? ]
        ...
        x[3.41459]
 int_part[ --]-> i[ 3 ]
frac_part[ --]-> d[.14159]
```

This approach isn't actually anything new; we've been doing it in calls of `scanf` since way back in Chapter 2.

```C
int i;
scanf("%d", &i);
```

We must put the `&` operator in front of `i` so that `scanf` is given a *pointer* to `i`; that pointer tells `scanf` where to put the value that it reads. Without the `&`, `scanf` would be supplied with the *value* of `i`. We don't require the `&` operator if the value passed to `scanf` is a pointer already:

```C
int i, *p;
...
p = &i;
scanf("%d", p);
```

### Pointers Can Be Dangerous!

 Failing to pass a pointer to a function when one is expected can have disastrous results. Suppose that we call decompose without the `&` operators in front of `i` and `d`:
 
```C
decompose(3.14159, i, d);
```
 
`decompose` is expecting pointers as its sdecond and third arguments, but it's been given the ***values*** of `i` and `d` instead. Because it has no way to tell the difference, it will use the values of `i` and `d` as if they were pointers. 
 
***When `decompose` stores values in `*int_part` and `*frac_part` it wil attempt to change unknown memory locations instead of modifying `i` and `d`.***
 
If we've provided a prototype for `decompose`, the compiler will let us know that we're attempting to pass arguments of the wrong type. In the case of `scanf`, however, failing to pass pointers often goes undetected by the compiler,which makes it an especially error-prone function.

### Program: Finding the Largest and Smallest Elements in an Array

To illustrate how pointers are passed to functions, we'll create a function called `max_min` that finds the largest and smallest elements in an array. When we call it, we'll pass it pointers to two external variables which it will store the answers in.

```C
// prototype:
//    a: an array of integers
//    n: the length of the array
// *max: pointer to an int var
// *min: " --- "
void max_min(int a[], int n, int *max, int *min);

// call:
max_min(b, N, &big, &small);
```

To test this program out, we'll write a program that reads 10 numbers into an array, passes the array to `max_min` and prints the results.

```C
// maxmin.c
// finds the largest and smallest elements in an array

#include <stdio.h>

#define N 10

void max_min(int a[], int n, int *max, int *min);

int main(void)
{
    int b[N], i, big, small;

    printf("Enter %d numbers: ", N);
    for (i = 0; i < N; i++)
        scanf("%d", &b[i]);

    max_min(b, N, &big, &small);

    printf("Largest: %d\n", big);
    printf("Smallest: %d\n", small);

    return 0;
}

void max_min(int a[], int n, int *max, int *min)
{
    *max = *min = a[0];
    for (int i = 1; i < n; i++) {
             if (a[i] > *max) *max = a[i];
        else if (a[i] < *min) *min = a[i];
    }
}
```

### Using `const` to Protect Arguments

When we call a function and pass it a pointer to a variable, we normally assume that the function will modify the variable. If we see `f(&x);` in a program, we'd probably expect that `f` modifies the value of `x` somehow. 

However, another possibility exists: ***efficiency***. Passing the value of a variable can waste time and space if the variable requires a large amount of storage. 

We can use the word `const` to document that a function won't change an object whose address is passed to the function. `const` goes in the parameter's declaration, just before the specification of its type:

```C
void f(const int *p)
{
    // *p = 0; <--COMPILER ERROR
    GlobalVar += *p;
}
```

The use of `const` indicates that `p` is a pointer to a "constant integer". Attempting to modify `*p` is an error that the compiler will detect.

## 11.5 Pointers as Return Values

Not only can we pass pointers to functions: we can also write functions that *return* pointers. The following function, when given pointers to two integers, returns a pointer to whichever integer is largest: 

```C
int *max(int *a, int *b)
{
    if (*a > *b) return a;
    else         return b;
}
```

When we call `max` we'll pass pointers to two `int` variables and store the result in a pointer variable:

```C
int *p, i, j;
...
p = max(&i, &j);
```

During the call of max, `*a` is an alias for `i`, while `*b` is an alias for `j`. If `i` has a larger value than `j`, max returns the address of `i`; otherwise it returns the address of `j`. After the call, `p` points to either `i` or `j`. 

Although the `max` function returns one of the pointers passed to it as an argument, that's not the only possibility. A function could also return a pointer to an external variable or to a local variable that's been declared `static`.

***

### Never return a pointer to an *automatic* local variable:

```C
int *f(void)
{
    int i;
    ...
    return &i;
}
```

The variable `i` doesn't exist once `f` returns, sot the pointer to it will be invalid. Some vompilers issue a warning such as *"function returns address of local variable"* in this situation.

***

Pointers can also pointer to array elements, not just ordinary variables. If `a` is an array, then `&a[i]` is a pointer to element `i` of `a`. 

When a function has an array argument, it's sometimes useful for the function to return a pointer to one of the elements in the array. For example, the following function returns a pointer to the middle element of the array `a`, assuming that `a` has `n` elements:

```C
int *find_middle(int a[], int n) {
    return &a[n/2];
}
```

> Also, recently for Exercism I wrote  program that does an iterative binary search and employs this exact method to return pointers to the calling function:
>
> ```C
> const int *binary_search(int value, const int *arr, size_t length)
> {
>     size_t low = 0,
>            high = length - 1;
> 
>     if (value < arr[low] || value > arr[high] || !length) 
>         return NULL;
>     
>     for(;;) {
>         int index = midpoint(high, low),
>             test = arr[index];
> 
>         if (test == value)     return &arr[index];
>         else if (low >= high)  break;
>         else if (test < value) low = index + 1;
>         else if (test > value) high = index - 1;
>     }
>     return NULL;
> }
> 
> size_t midpoint(size_t high, size_t low) {
>     return (high - (high - low) / 2);
> }
> 
> void safe_print(int *result){
>     if (result != 0) printf("%p: %d\n", result, *result);
>     else             printf("NOT FOUND\n");
> }
> ```

## Pointers Q&A

> **Q. Is a pointer always the same as an address?**

Usually, but not always. A pointer to a character may need to be stored in a different form than other pointers. A pointer to a character might consist of an address (the word in which the character is stored) plus a small integer (the position of the character within the word).

On some computers, pointers may be "offsets" rather than complete addresses. For example, CPUS in the Intel x86 family can execute programs in several modes. The oldest of these, which dates back to the 8086 processor of 1978 is called ***real mode***.  

In ***real mode*** addresses are sometimes represented by a single 16-bit number (an offset) and sometimes by two 16-bit numbers (a segment:offset pair). An offset isn't a true memory address: the CPU must combine it with a segment value stored in a special register.

To support real mode, older C ompilers often provide two kinds of pointers: ***near pointers*** (16-bit offsets) and ***far pointers*** (32-bit segment:offset pairs). These compilers usually reserve the words near and far as nonstandard keywords that can be used to declare pointer variables.

> **Q. If a pointer can point to *data* in a program, is it possible to have a pointer to *program code*?**

Yes, these are known as **Function Pointers**. We'll cover them in Section 17.7.

> **Q. It seems to me that there's an inconsistency between `int *p = &i;` and `p = &i;`: why isn't `p` preceded by a `*` in the statement, as it is in the declaration?**

`*` can have different meanings in C, depending on the context in which it's used. In the declaration `int *p = &i;` the `*` symbol is not the indirection operator; it instead specifies the type of `p`, informing the compiler that `p` is a pointer to an `int`.  

However, when it appears in a statement, the `*` symbol performs indirection (when used as a unary operator). The statement `*p = &i;` would be wrong because it assigns the address of `i` to the object that `p` points to, not to `p` itself.  

> **Q. How do you print the address of a variable?**

Any pointer, including the address of a variable, can be displayed by calling `printf` with the format specifer `%p`.

> **Q. does this statement: `void f(const int *p);` say that I can't modify `p`?**

No, it says that `f` can't change the integer that `p` points to; it doesn't prevent `f` from changing `p` itself. However, since arguments are passed by value, assigning `p` to a new value by making it point somewhere else won't have any effect outside of the function.  

## Written Exercises

### 1. If `i` is a variable and `p` points to `i`, which of the following expressions are aliases for `i`?

```C
1.  *p      <-- the thing pointed at by p                 (i)
2.  &p      x   the address of p                          (a new pointer)
3. *&p      <-- the thing pointed to by the address of p  (i)
4. &*p      x   the address of the thing pointed at by p  (p)
5.  *i      x   the thing pointed to by i                 (½∟1 7x1^Öƒ)
6.  &i      x   the address of i                          (p)
7. *&i      <-- the object at the address of i            (i)
8. &*i      <-- the address of the object pointed to by i (i)
```

### 2. If `i` is an `int` variable and `p` and `q` are pointers to `int`, which of the following assignments are legal?

```C
1.  p =   i;    x   an int pointer is not an int
2. *p =  &i;    x   object pointed to by p cannot be the address of i (p)
3. &p =   q;    <-- a pointer is /technically/ an int
4.  p =  &q;    <-- same here
5.  p = *&q;    <-- also fine; p is an object containing the address of q
6.  p =   q;    <-- fine, p and q are pointers
7.  p =  *q;    x   p is not an int
8. *p =   q;    x   i is not an int pointer
9. *p =  &q;    x   i is not the address of a pointer
```

### 3. The following function supposedly computes the sum and average of the numbers in the array `a`, which has length `n`. `avg` and `sum` point to variables that the function should modify. Unfortunately, the function contains several errors: find and correct them.

```C
void avg_sum(double a[], int n, double *avg, double *sum)
{
    int i;

    sum = 0.0;                 // sum is a pointer
    for (i = 0; i < n; i++)
        sum += a[i];           // sum is a pointer
    avg = sum / n;             // avg and sum are pointers
}
```

```C
void avg_sum(double a[], int n, double *avg, double *sum)
{
    int i;

    *sum = 0.0;                 // int pointed to by sum = 0
    for (i = 0; i < n; i++)
        *sum += a[i];           // int p.t.b. sum += a[i]
    *avg = *sum / n;            // int p.t.b. avg += int p.t.b. sum / n
}
```

### 4. Write the following function:  

```C
void swap(int *p, int *q);
``` 

When passed the addresses of the variables, `swap` should exchange the values of the variables.

```C
void swap(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}
```

### 5. Write the following function:  

```C
void split_time(long total_sec, int *hr, int *min, int *sec);
```

`total_sec` is a time represented as the number of seconds since midnight, `hr`, `min` and `sex` are pointers to variables in which the function will store the equivalent time in hours (0-23), minutes (0-59) and seconds (0-59) respectively.

```C
void split_time(long total_sec, int *hr, int *min, int *sec)
{
    *hr = (int) (total_sec / 60) / 60;

    *min = (int) (total_sec - (*hr * 60 * 60)) / 60;

    *sec = (int) total_sec - (*hr * 60 * 60) - (*min * 60);
}
```

### 6. Write the following function:  

```C
void find_two_largest(int a[], int n, int *largest,
                      int *second_largest);
```

When passed an array `a` of length `n`, the function will search `a` for its largest and second largest elements, storing them in the variables pointed to by `largest and second_largest` respectively.

```C
void find_two_largest(int a[], int n, int *largest, int *second_largest)
{
    *largest = *second_largest = a[0];

    for (int i = 0; i < n; i++)
        if (a[i] > *largest) 
            *largest = a[i];

    for (int i = 0; i < n; i++)
        if (a[i] > *second_largest && a[i] != *largest) 
            *second_largest = a[i];
}
```

### 7. Write the following function:  

```C
void split_date(int day_of_year, int year, int *month, int *day);
```

`day_of_year` is an integer between 1 and 366, specifying a particular day within the year designated by `year`. `month` and `day` point to variables in which the function will store the equivalent month (1-12) and day within that month (1-31).

```C
void split_date(int day_of_year, int year, int *month, int *day)
{
    int Months = {
        31, 28, 31, 30,     // JAN FEB MAR APR
        31, 30, 31, 31,     // MAY JUN JUL AUG
        30, 31, 30, 31      // SEP OCT NOV DEC
    };

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
        Months[1]++;        // adds a day to February on leap years

    for (int i = 0; i < 12; i++) {
        // take every month's days away from the total
        day_of_year -= Months[i];
        // if you go below 0, you're in that month
        if (day_of_year < 0) 
        {
            *day = day_of_year + Months[i];
            *month = i + 1;
            return;
        }
    }
}
```

### 8. Write the following function:  

```C
int *find_largest(int a[], int n);
```

When passed an array `a` of length `n`, the function will return a pointer to the array's largest element.

```C
int *find_largest(int a[], int n)
{
    if (!n) return NULL;

    int *largest = &a[0];

    for (int i = 1; i < n; i++)
        if (a[i] > *largest) 
            largest = &a[i];

    return largest;
}
```
