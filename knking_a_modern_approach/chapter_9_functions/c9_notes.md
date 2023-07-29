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

```C
// prime.c
// tests whether a number is prime

#include <stdbool.h>
#include <stdio.h>

bool is_prime(int n)
{
    int divisor;

    if (n <= 1)
        return false;
    for (divisor = 2; divisor * divisor <= n; divisor++)
        if (n % divisor == 0)
            return false;
    return true;
}

int main(void)
{
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    if (is_prime(n))
        printf("Prime\n");
    else
        printf("Not prime\n");

    return 0;
}
```

`is_prime` demonstrates, a function may have more than one `return` statement. However, we can execute just one of these statements during a given call of the function.

***

## 9.2 Function Declarations

C doesn't actually require you to declare entire functions before you call them. However, the compiler still needs to know that the function exists in advance.
If it encounters a function call and doesn't know how many parameters it should take, or if they're correct, it will assume that the function returns an int properly and attempts to promote the arguments. If it later finds out that the function should have returned differently, it will then throw an error and fail to compile.

One way to avoid the problem of call-before-definition is to arrange the program so that the definition of each function precedes all of its calls. This will solve the issue in some cases, but cause new ones related to structure and readability in others, and may not actually be feasible.

The alternative is to declare each function before calling it. A function declaration provides the compiler with a brief glimpse at a function whose full definition will appear later. A function declaration resembles the first line of a function definition with a semicolon added at the end:

```txt
return-type  function-name  ( parameters ) ;
```

This 'function prototype' must be consistent with the later function declaration that contains the procedure to follow. The prototype provides a complete description of how to call a function, how many arguments to supply, what their types should be and what type of result will be returned.

```C
double average(double a, double b);     // function prototype

int main(void) 
{
    // ...
    double x = average(12.2, 13.5);     // function call
}

double average(double a, double b)      // function definition
{
    return (a + b) / 2;
}
```

Function prototypes do not have to declare the names of a function's parameters, so long as the types are present. 

```C
double average(double, double);
```

But it is considered best practice not to omit them ass they help docum,ent the purpose of each parameter and remind the programmer of the order in which arguments must appear.

C99 has adopted the rule that either a declaration or a definition of a function must be present prior to any call of the function. Calling a function for which the compiler has not yet seen a declaration or definition is an error.

***

## 9.3 Arguments

***Parameters*** and ***arguments*** are not the same thing. ***Parameters*** appear in function definitions; they're dummy names that represent values to be supplied when the function is called. ***Arguments*** are expressions that appear in function calls. When the distinction between ***argument*** and ***parameter*** isn't important, ***argument*** can be used to mean either.  

In C, arguments are ***passed by value***; when a function is called, each argument is evaluated and its value assigned to the corresponding parameter. Since the parameter contains a copy of the argument's value, any changes made to the parameter during the execution of a function don't affect the argument.

In effect, each parameter behaves like a variables that's been initialised to the value of the matching argument. This has both advantages and disadvantages; since a parameter can be modified without affecting the corresponding argument, we can use parameters as variables within the function, reducing the number of genuine variables needed.

```C
int power(int x, int n)
{
    int i, result = 1;

    for (i = 1; i <= n; i++)
        result = result * x;

    return result;
}
```

Since n is a *copy* of the original exponent, we can modify it inside the function, thus removing the need for i:

```C
int power(int x, int n)
{
    int result = 1;

    while (n-- > 0)
        result = result * x;

    return result;
}
```

Unfortunately, C's requirement that arguments be passed by value makes it difficult to write certain kinds of functions.

Suppose that we need a function that will decompose a `double` value into an integer part and a fractional part. Since a function can't ***return*** two numbers, we might try passing a pair of variables to the function and have it modify them.

```C
void decompose(double x, long int_part, double frac_part)
{
    int_part = (long) x;    // drops the fractional part of x
    frac_part = x - int_part;
}
```

Suppose we call the function in the following way:

```C
decompose(3.14159, i, d);
```

At the beginning of the call, `3.14159` is copied into `x`, `i`'s value is copied into `int_part`, and `d`'s value is copied into `frac_part`. The statements inside `decompose` then assign `3` to `int_part` and `.14159` to `frac_part`, and the function returns. Unfortunately, `i` and `d` weren't affected by the assignments to `int_part` and `frac_part`, so they have the same value after the call as they did before the call.  

With some more work, `decompose` can be made to work like we intend it to, but we'll need to wait until section 11.4 after covering more of C's features.

***

### Argument Conversions

C allows function calls where the types of the arguments don't match the types of the parameters. The rules for whether the arguments will be converted depend on whether or not the compiler has seen a prototype for the function prior to the call.

