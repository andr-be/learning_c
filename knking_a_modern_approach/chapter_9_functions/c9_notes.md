# Chapter 9: Functions - Notes

> *If you have a procedure with ten parameters, you probably missed some*.

A function is simply a series of statements that have been grouped together and given a name. 

Functions are the building blocks of C programs. Each function is essentially a small self-contained program with its own declarations and statements. Functions are easier to reason about, allow us to avoid duplicating code and are reusable.

Our programs so far have consisted of just the `main` function. In this chapter, we'll see how to write functions other than `main`, and we'll learn more about `main` itself.

We will also explore arguments, returns, termination and recursion.

***

## 9.1 Defining and Calling Functions

Suppose we often need to compute the average of two `double` values. C doesn't have a baked in `average` function, but we can easily define our own.

```C
double average(double a, double b)
{
    return (a + b) / 2;
}

...

return_type function_name(p_type param_1, ...) 
{ 
    return value;  /* function body */ 
}
```

A function parameter is essentially a cariable whose initial value will be supplied later, when the function is called. The body is the executable section of the function, `average`'s body consists of a single `return` statement. `return` is literal, it **returns** execution to the place from which it was called, in this case with the value `(a + b) / 2`.

To call a function, we write the function name, followed by a list of arguments. e.g. `average(x, y)` is a call of the `average` function on two variables, `x` and `y`. The value of these variables is **copied** into the parameters `a` and `b`, then the body is executed. `x` and `y` don't need to be variables, they can be any values of the correct type.

***

### Program: Computing Averages

```C
// average.c
// computes pairwise averages of three numbers

#include <stdio.h>

double average(double a, double b) {
    return (a + b) / 2;
}

int main(void)
{
    double x, y, z;

    printf("Enter three numbers: ");
    scanf("%lf%lf%lf", &x, &y, &z);
    printf("Average of %g and %g: %g\n", x, y, average(x, y));
    printf("Average of %g and %g: %g\n", y, z, average(y, z));
    printf("Average of %g and %g: %g\n", x, z, average(x, z));

    return 0;
}
```

Notice that the definition of `average` comes before `main`, putting them the other way around will cause problems.

***

### Program: Printing a Countdown

Not all functions return a value. To indicate this, we specify that its return type is `void`. (a type with no value).

```C
// countdown.c
// prints a countdown

#include <stdio.h>

void print_count(int n) {
    printf("T minus %d and counting\n", n);
}

int main(void)
{
    int i;

    for (i = 10; i > 0; i--)
        print_count(i)
    
    return 0;
}
```

```txt
OUTPUT: 
T minus 10 and counting
T minus 9 and counting 
T minus 8 and counting 
T minus 7 and counting 
T minus 6 and counting 
T minus 5 and counting 
T minus 4 and counting 
T minus 3 and counting 
T minus 2 and counting 
T minus 1 and counting 
```

***

### Program: Printing a Pun (Revisited)

Some functions have no parameters at all, like the following function that prints a bad pun every time it's called.

```C
// pun2.c
// prints a bad pun

#include <stdio.h>

void print_pun(void) {
    printf("To C, or not to C: that is the question.\n");
}

int main(void)
{
    print_pun();
    return 0;
}
```

***

### Function Definitions

```C
return_type function_name( parameters ) 
{ 
    declarations;
    statements();
}
```

- Functions may not return arrays, but there are no other restrictions on the return type.
- Specifiying that the return type is `void` indicates that the function doesn't return a value.
- If the return type is omitted in C89, the function is presumed to return a value of type `int`. In C99, it's illegal to omit the return type of a function.

As a matter of style, some people put the return type above the function name. This can be especially useful if the return type is lengthy, like `unsigned long int`.

```C
double
average(double a, double b)
{
    return (a + b) / 2;
}
```

The body of a function can be written with both declarations and statements.

```C
double average(double a, double b)
{
    double sum;         // declaration

    sum = a + b;        // statement
    return sum / 2;     // statement
}
```

In C89, all declarations must come before statements. In C99 and onwards, you can mix declarations and statements so long as any variables used are declared first.

The body of a function can be empty if the return type is void. This can be useful during program development to fill out functions without having to complete them, so we can later come back and write the body.

```C
void do_nothing(void)
{
}
```

***

### Function Calls

A function call consists of a function name followed by a list of arguments, enclosed in parentheses. If the parentheses are missing, the function won't get called. The result is a legal (and meaningless) expression statement that looks correct but has no effect. 

```C
average(x, y);
print_count(i);
print_pun();

print_pun;      // WRONG, statement with no effect
```

A call to a non-`void` function is always followed by a semicolon to turn it into a statement. 

A non-`void` function produces a value that can be stored in a variable, tested, printed or used in some other way.

```C
double avg = average(x, y);

if average(x, y) > 0)
    printf("Average is positive.\n");

printf("The average is %g\n", average(x, y));
```

The value returned by a non-`void` statement can always be discarded if it's not needed. This is common with `printf`, which returns as a value the number of characters that it prints.

```C
num_chars = printf("Hi, Mom!\n");   // num_chars == 9
```

To make it clear that we're deliberately discarding the return value of a function, C allows us to put `(void)` before the call;

```C
(void) printf("Hi, Mom!\n");
```

Which is just casting the return value as a `void` type. "Casting to `void`" is a euphemism for throwing something away, using `(void)` makes is clear that you deliberately discarded it.

***

### Program: Testing Whether a Number is Prime

pg 190

