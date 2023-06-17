# Chapter 6: Loops - Notes
`// andr-be 06/2023`
***
## The `while` Statement
```C
while (i < n)   // controlling expressions
    i = i * 2;  // loop body

int i = 10;
while (i > 0) 
    printf("T minus %d and counting!\n", i--);
```
***
### Program: `square.c`
```C
// SQUARE GENERATOR
// andr-be 06/2023
/*
    prints a table of squares using a while statement
*/

#include <stdio.h>

int main(void)
{
    int i, n;

    printf("This program prints a table of squares.\n");
    printf("Enter number of entries in table: ");
    scanf("%d", &n);

    i = 1;
    while (i <= n) {
        printf("%10d%10d\n", i, i * i);
        i++;
    }
    return 0;
}
```
***
### Program: `sum.c`
```C
// SERIES SUMMER
// andr-be 06/2023
/*
    sums a series of integers entered by the user
*/

#include <stdio.h>

int main(void)
{
    int n, sum = 0;

    printf("This program sums a series of integers.\n");
    printf("Enter integers (0 to terminate): ");

    scanf("%d", &n);
    while (n != 0) {
        sum += n;
        scanf("%d", &n);
    }
    printf("The sum is: %d\n", sum);

    return 0;
}
```
***
## The `do` Statement
```C
do  statement  while  ( expression ) ;

i = 10;
do {
    printf("T minus %d and counting\n", i);
    --i;
} while (i > 0);
```
The difference between the `while` statement and the `do` statement is that **the body of a `do` statement is always executed at least once** while the body of a `while` statement is skipped entirely if the controlling expression is 0 initially.
***
### Program: `numdigits.c`
```C
// NUMBER OF DIGITS COUNTER
// andr-be 06/2023

#include <stdio.h>

int main(void)
{
    int digits = 0, n;

    printf("Enter a nonnegative integer: ");
    scanf("%d", &n);

    do {
        n /= 10;
        digits++;
    } while (n > 0);

    printf("The number has %d digits(s).\n", digits);

    return 0;
}
```
If we were to replace the `do` loop with a similar while loop:
```C
while (n > 0) {
    n /= 10;
    digits++;
}
```
If `n` is `0` initially, this loop won't execute at all, and the program would print 
```
The number has 0 digit(s).
```
***
## The `for` Statement
```C
for  ( expre1 ; expr2 ; expr3 )  statement;

for (i = 10; i > 0; i--)
    printf("T minus %d and counting\n", i);
```
The `for` statement is closely related to the `while` statement. In fact, except in a few rare cases, a `for` loop can always be replaced by an equivalent `while` loop:
```C
expr1;
while  ( expr2 ) {
    statement
    expr3;
}
```
***
## `for` Statement Idioms
```C
// counting up from 0 to n-1
for (i = 0; i < n; i++) ...

// counting up from 1 to n
for (i = 1; i <= n; i++) ...

// counting down from n-1 to 0
for (i = n - 1; i >= 0; i--) ...

// counting down from n to 1
for (i = n; i > 0; i--) ...
```

### Common Errors
- Using the wrong comparion operator
- Using `==` in the controlling expression
- "Off-by-one" error caused by a mistake in the controlling expression

***
## Omitting Expressions in a `for` Statement
```C
// omitting the initialising expression
i = 10;
for (; i > 0; --i)
    printf("T minus %d and counting\n", i);

// omitting the increment expression
for (i = 10; i > 0; )
    printf("T minus %d and counting\n", i--);

// omitting the first and third expressions
for (; i > 0;)
    printf("T minus %d and counting\n", i--);
// IS THE SAME AS
while (i > 0)
    printf("T minus %d and counting\n", i--);

// Omitting all expressions for infinite loop
for (;;)
    printf("ONE MILLION DOLLARS\n")
```
***
## `for` Statements in C99
In C99, the first expression in a for statement can be replaced by a declaration. This feature allows the programmer to declare a variable for use by the loop:
```C
for (int i = 0; i < n; i++)
    ...
```
If a variable is already in use for `i`, the statement creates a *new* version that will be used only for the loop.
Doing things this way is usually a good idea, as it can make your programs easier to understand, as well as being convenient.

You can also declare *multiple* variables in the same `for` loop opening expression;
```C
for (int i = 0, j = 0; i < n; i++)
    for (; j < n; j++)
        ...
```
***
## The Comma Operator

