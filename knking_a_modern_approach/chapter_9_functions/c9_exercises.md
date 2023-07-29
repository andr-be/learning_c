# Chapter 9: Functions - Written Exercises

andr-be 07/2023

***

## 1. The following function, which computes the area of a triangle, contains two errors. Locate the errors and show how to fix them. 

(Hint: There are no errors in the formula.)

```C
double triangle_area(double base, height)
double product;
{
    product = base * height;
    return product / 2;
}
```

I think the first error is that no type has been given for height, which should be a double.

I think the second error is that the product declaration should happen in-line with the calculation; the corrected version would look as follows;

```C
double triangle_area(double base, double height)
{
    double product = base * height;
    return product / 2;
}
```

If you wanted to get really one-liney, you can do the following;

```C
double triangle_area(double base, double height) {
    return (base * height) / 2;
}
```

Which is my preference, personally.

***

## 2. Write a function `check(x, y, n)` that returns 1 if both `x` and `y` fall between 0 and `n - 1`, inclusive. The function should return 0 otherwise.

Assume that `x`, `y`, and `n` are all of type `int`.

```C
#include <stdbool.h>

bool check(int x, int y, int n)
{
    return (x >= 0 && x < n) && (y >= 0 && y < n);
}
```

***

## 3. Write a function `gcd(m, n)` that calculates the greatest common divisor of the integers `m` and `n`.

Programming Project 2 in Chapter 6 describes Euclid's algorithm for computing the GCD.

[C6_E2](../chapter_6_loops/programs/E2_GreatestCommonDivisor.c)

```C
int gcd(int m, int n) 
{
    if (n == 0 || m == 0) return (n == 0) ? m : n;
    
    while (n != 0) {
        int temp = m % n;
        m = n, n = temp;
    }

    return m;
}
```

***

## 4. Write a function `day_of_year(month, day, year)` that returns the day of the year (an integer between 1 and 366) specified by the three arguments.

```C
// naive interpretation
int day_of_year(int month, int day, int year)
{
    return ((month - 1) * 30) + day;
}

// array interpretation
int day_of_year(int day, int month, int year)
{
    static int months[] = {
        31, 28, 31,     // JAN, FEB, MAR
        30, 31, 30,     // APR, MAY, JUN
        31, 31, 30,     // JUL, AUG, SEP
        31, 30, 31      // OCT, NOV, DEC
    }

    int sum = 0;

    for (int i = 0; i < month - 1, i++) 
        sum += months[i]

    return sum + day;
}
```
```txt
INPUT: 25 12 1994

sum = 0;

i = 0;     i < 11?   y   sum += 31;     sum ==  31;
i = 1;     i < 11?   y   sum += 28;     sum ==  59;
i = 2;     i < 11?   y   sum += 31;     sum ==  90;
i = 3;     i < 11?   y   sum += 30;     sum == 120;
i = 4;     i < 11?   y   sum += 31;     sum == 151;
i = 5;     i < 11?   y   sum += 30;     sum == 181;
i = 6;     i < 11?   y   sum += 31;     sum == 212;
i = 7;     i < 11?   y   sum += 31;     sum == 243;
i = 8;     i < 11?   y   sum += 30;     sum == 273;
i = 9;     i < 11?   y   sum += 31;     sum == 304;
i = 10;    i < 11?   y   sum += 30;     sum == 334;
i = 11;    i < 11?   n   break;

return sum (334) + day (31) == 365
```

```txt
INPUT 1 1 2001
sum = 0

i = 0;     i < 0?    n   break;

return sum (0) + day (1) == 1
```

***

## 5. Write a function `num_digits(n)` that returns the number of digits in `n` (a positive integer).

Hint: To determine the number of digits in a number `n`, divide it by 10 repeatedly. When `n` reaches 0, the number of divisions indicates how many digits `n` originally had.

```C
num_digits(int n)
{
    int divs = 0;

    for (; n > 0; n /= 10) divs++;

    return divs;
}
```

***

## 6. Write a function `digit(n, k)` that returns the $k^{th}$ digit (from the right) in `n` (a positive integer).

For example, `digit(829, 1) == 9`, `digit(829, 2) == 2`, `digit(829, 3) == 8`

If `k` is greater than the number of digits in `n`, have the function return 0.

```C
int digit(int n, int k)
{
    for (; k > 1; k--) n /= 10;

    return n % 10;
}
```

```txt
INPUT: 829 3

k == 3;     k > 1? y;       n == 82;
k == 2;     k > 2? y;       n ==  8;
k == 1;     k > 1? n;       break;

return 8 % 10 == 8
```

```txt
INPUT = 12345 4

k == 4;     k > 1? y;       n == 1234;
k == 3;     k > 1? y;       n ==  123;
k == 2;     k > 1? y;       n ==   12;
k == 1;     k > 1? n;       break;

return 12 % 10 == 2
```

***

## 7. Suppose that the function $f$ has the following definition: 

```C
int f(int a, int b) { ... }
```

Which of the following statements are legal? (Assume that `i` has type `int` and `x` has type `double`.)

| Statement               | Status  | Reason                                 |
| ----------------------- | ------- | -------------------------------------- |
| 1) `i = f(83, 12);`     | LEGAL   | i is an int, a and b are ints          |
| 2) `x = f(83, 12);`     | ILLEGAL | x is a double: f returns an integer!   |
| 3) `i = f(3.15, 9.28);` | LEGAL   | arguments a and b are converted to int |
| 4) `x = f(3.15, 9.28);` | ILLEGAL | x is a double: f returns an integer!   |
| 5) `f(83, 12);`         | LEGAL   | does nothing, no issues.               |

***

## 8. Which of the following would be valid prototypes for a function that returns nothing and has one double parameter?

1. `void f(double x);`
2. `void f(double);`
3. `void f(x);`
4. `f(double x)`

1 and 2 are valid, 3 lacks a type for x and 4 lacks a type for f.

***

## 9. What will be the output of the following `swap` program?

```C
#include <stdio.h>

void swap(int a, int b);

int main(void)
{
    int i = 1; j = 2;

    swap(i, j);
    printf("i = %d, j = %d\n", i, j);
    return 0;
}

void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}
```

The output will be whatever is put into it. In this case, `i = 1, j = 2`.

This is because functions in C pass by value, you can only achieve this kind of result by using an array, because they're passed by reference.

***

## 10. Write functions that return the following values. Assume that `a` and `n` are parameters, where `a` is an array of `int` values and `n` is the length of the array.

1. The largest element in `a`.
2. The average of all elements in `a`.
3. The number of positive elements in `a`.

```C
int largest(int n, int a[n])
{
    int largest = a[0];

    for (int i = 1; i < n; i++)
        largest = (a[i] > largest) ? a[i] : largest;

    return largest;
}

double average(int n, int a[n])
{
    int sum = 0;

    for (int i = 0; i < n; i++) 
        sum += a[i];

    return (double) sum / (double) n;
}

int positive(int n, int a[n])
{
    int pos = 0;

    for (int i = 0; i < n; i++)
        pos += (a[i] > 0) ? 1 : 0;

    return pos;
}
```

Could I make some of them more concise?

```C
double average(int n, int a[n])
{
    int sum = 0, count = n;

    for (; n >= 0; --n) 
        sum += a[n];
    
    return sum / count;
}


int positive(int n, int a[n])
{
    int pos = 0;

    for (; n >= 0; --n) 
        pos += (a[n] > 0) ? 1 : 0;

    return pos;
}
```

***

## 11. Write the following function: `float compute_GPA(char grades[], int n);`

The `grades` array will contain letter grades (A, B, C, D, or F, either upper or lower case); `n` is the length of the array. The function should return the average of the grades. Assume that A = 4, B = 3, C = 2, D = 1 and F = 0.

```C
#include <stdlib.h>

float compute_GPA(char grades[], int n)
{
    float sum = 0;

    for (int i = 0; i < n; i++) 
        sum += grade_score(grades[i]);

    return sum / (float) n;
}

float grade_score(char grade)
{
    switch (toupper(grade))
    {
    case 'A': return 4.0f;
    case 'B': return 3.0f;
    case 'C': return 2.0f;
    case 'D': return 1.0f;

    default:  return 0;
    }
}
```

This is technically two functions, but it's much nicer to look at it this way. If you wanted to change the grade scores, you'd just need to alter `grade_score`.

I think this could feasibly be done with an `enum`? Not sure right now though.

***

## 12. Write the following function: `double inner_product(double a[], double b[], int n);`

The function should return `a[0] * b[0] + a[1] * b[1] + ... + a[n-1] * b[n-1]`.

```C
double inner_product(double a[], double b[], int n)
{
    double sum = 0;

    for (int i = 0; i < n; i++)
        sum += (a[i] * b[i]);

    return sum;
}
```

***

## 13. Write the following function, which evaluates a chess position.

```C
int evaluate_position(char board[8][8]);
```

`board` represents a configuration of pieces on a chessboard, where the letters K, Q, R, B, N, P represent white pieces and the letters k, q, r, b, n, and p represent Black pieces. 

`evaulate_position` should sum the values of the White pieces (Q = 9, R = 5, B = 3, N = 3, P = 1). It should also sum the values of the Black pieces (done in a similar way). The function will return the difference between the two numbers. This value will be positive if White has advantage, or negative if Black has advantage. 

```C
// starting position board; should result in 0
char board[8][8] = {
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
}
```

```C
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

***

## 14. The following function is supposed to return `true` if any element of the array `a` has the value `0` and `false` if all elements are nonzero. Sadly, it contains an error. Find the error and show how to fix it:

```C
bool has_zero(int a[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        if (a[i] == 0)
            return true;
        else
            return false;
}
```

The issue with this function is that it will return false the instant that there isn't a non-zero value, instead of looking through the entire array.

```C
bool has_zero(int n, int a[n])
{
    for (int i = 0; i < n; i++) 
        if (a[i] == 0) return true;

    return false;
}
```

This rewrite ensures that if the for-loop never returns `true`, then the function as a whole will return false. This ensure that it will never return `false` early, until it has checked every element is not a 0.

***

## 15. The following (rather confusing) function finds the median of three numbers. Rewrite the function so that it has just one `return` statement.

```C
double median(double x, double y, double z)
{
    if (x <= y)
        if (y <= z) return y;
        else if (x <= z) return z;
        else return x;
    if (z <= y) return y;
    if (x <= z) return x;
    return z;
}
```

```C
double median(double x, double y, double z)
{
    double median = 0;

    if ( (y <= x && x <= z) || (y >= x && x >= z) )  median = x;
    if ( (x <= y && y <= z) || (x >= y && y >= z) )  median = y;
    if ( (x <= z && z <= y) || (x >= z && z >= y) )  median = z; 

    return median;
}
```

```txt
x: 1,   y: 2,   z: 3

if ( (2 <= 1 && 1 <= 3) || (2 >= 1 && 1 >= 3)) -> FALSE
if ( (1 <= 2 && 2 <= 3) -> TRUE
    median = 2;

return 2;
```

***

## 16. Condense the `fact` function in the same way we condense `power`.

```C
int fact(int n)
{
    if (n <= 1) return 1;
    else        return n * fact(n - 1);
}

int power_condensed(int x, int n)
{
    return n == 0 ? 1 : x * power(x, n - 1);
}
```

```C
int fact_condensed(int n)
{
    return (n <= 1) ? 1 : n * fact(n - 1);
}
```

***

## 17. Rewrite the `fact` function so that it's no longer recursive.

```C
int fact_inline(int n)
{
    int sum = n;

    for (; n > 1; --n) sum *= i;

    return sum;
}
```

***

## 18. Write a recursive version of the `gcd` function (see Exercise 3)  

Here's the strategy to use for computing `gcd(m, n)`: If `n` is 0, return `m`. Otherwise, call `gcd` recursively, passing `n` as the first argument and `m % n` as the second.

```C
int gcd_inline(int m, int n) 
{
    if (n == 0 || m == 0) return (n == 0) ? m : n;
    
    while (n != 0) {
        int temp = m % n;
        m = n, n = temp;
    }

    return m;
}

int gcd_r(int m, int n)
{
    if (n == 0) return m;

    else return gcd_r(n, m % n);
}
```

***

## 19. Consider the following "mystery" function:

```C
void pb(int n)
{
    if (n != 0) {
        pb(n / 2);
        putchar('0' + n % 2);
    }
}
```

Trace the execution of the function by hand, then write a program that calls the function passing it a number entered by the user. What does the function do?

```txt
INPUT: 4

n == 4;     n != 0? y;      pb(2);
    n == 2;     n != 0? y;      pb(1);
        n == 1;     n != 0? y;      pb (0);
            n == 0;     n != 0? n;
        putchar('0' + (1 % 2));             --> 1
    putchar('0' + (2 % 2));                 --> 0
putchar('0' + (4 % 2));                     --> 0

100
```

I think it displays numbers in binary?

pb == print_binary?

***

