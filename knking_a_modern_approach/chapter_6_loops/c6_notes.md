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
### `for` Statement Idioms
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
### Omitting Expressions in a `for` Statement
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
### `for` Statements in C99
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
Sometimes we need to write `for` statements with two (or more) initialisers, or one that increments several variables every loop.

This is done by use of a ***comma expression*** as the first or third expression in the `for` statement.

```C
// comma expression
expr1 , expr2
```
First, `expr1` is evaluated and the value is discarded.
Second, `expr2` is evaluated; its value is the value of the entire expression.

**The comma operator is left associative and has the lowest precedence of all other C operators.**

```C
i = 1, j = 2, k = i + j

// is evivalent to

( (i = 1), (j = 2) ), ( k = (i + j) )
```
***
### Program: `square2.c`
```C
// SQUARE GENERATOR V2
// andr-be 06/2023
/*
    prints a table of squares using a for statement
    improved the size and readability by condensing it down
    into half as many lines
*/

#include <stdio.h>

int main(void)
{
    int i, n;

    printf("This program prints a table of squares.\n");
    printf("Enter number of entries in table: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) 
        printf("%10d%10d\n", i, i * i);

    return 0;
}
```
***
### Program: `square3.c`
```C
// SQUARE GENERATOR V3
// andr-be 06/2023
/*
    prints a table of squares using an... odd method
*/

#include <stdio.h>

int main(void)
{
    int i, n, odd, square;

    printf("This program prints a table of squares.\n");
    printf("Enter number of entries in table: ");
    scanf("%d", &n);

    i = 1;
    odd = 3;
    for (square = 1; i <= n; odd += 2) {
        printf("%10d%10d\n", i, square);
        ++i;
        square += odd;
    }

    return 0;
}
```
This for loop would be much clearer if we rearranged its pieces so that the loop is clearly controlled by `i`.
***
## Exiting from a Loop
6.4 - Page 111
### The `break` Statement
The break statement can be used to transfer control out of a `switch` statement, but it can also be used to jump out of a `while`, `do`, or `for` loop.
```C
for (d = 2; d < n; d++)
  if (n % d == 0)
    break;
  if (d < n)
    printf("%d is divisble by %d\n", n, d);
  else
    printf("%d is prime!\n", n);
```
```C
for (;;) {
    printf("Enter a number (enter 0 to stop): ");
    scanf("%d", &n);
    if (n == 0)
      break;
    printf("%d cubed is %d\n", n, n * n * n);
}
```
A `break` statement only returns out of the current loop it's in; in the example below the `while` loop will continue even after the nested `switch` statement `break`s.

```C
while (...) {
    switch (...) {
        ...
        break;
        ...
    }
}
```
***
### The `continue` Statement
`continue` doesn't actually exit from a loop. Whereas `break` transfers control to a point *just past* the end of a loop, `continue` transfers control to a point *just before* the end of a loop.

`continue` can only be used in loops, and cannot be used in `switch` statements (at least in C99...)

```C
i = 0, n = 0, sum = 0;
while (n < 10) {
    scanf("%d", &i);
    if (i == 0)
        continue;
    sum += i;
    n++;
    /* continue jumps to here */
}
```
***
### The `goto` Statement
`break` and `continue` are jump statements that transfer control from one point in the program to another. They are restricted to points that are relative to the loop they're currently within.

`goto` on the other hand, is capable of jumping to any statement in a function, provided that the statement has a ***label***.

C99 places an additional restriction on the `goto` statement, it can't be used to bypass the declaration of a variable-length array.

```C
identifier  :  statement
...
goto  identifier  ;
```
Executing the statement `goto L;` transfers control of the statement that follows the label `L`, which must be in the same function as the `goto` statement itself.
```C
for (d = 2; d < n; d++)
  if (n % d == 0)
    goto done;
done:
if (d < n)
  printf("%d is divisible by %d\n", n, d);
else
  printf("%d is prime", n);
```
While the `goto` statement doesn't see much use in C, it's occasionally useful for exiting from a loop within or a switch or nested loop.
```C
while (...) {
    switch (...) {
        ...
        goto loop_done;     /* break won't work here */
        ...
    }
}
loop_done: ...
```
***
### Menu-Based Interactivity
Many simple interactive programs are menu-based. They present the user with a list of commands to choose from and once the user selects one, the program performs the desired action.

This process continues until the user selects an exit or quit command.
```C
for (;;) {
    prompt_user_to_enter_command();
    read_command();
    execute_command();
}

// This often involves a switch or nested if statement

for (;;) {
    prompt_user_to_enter_command();
    read_command();
    switch (command) {
        case command_1: perform_operation_1(); break;
        case command_2: perform_operation_2(); break;
        // ~
        // ~
        case command_n: perform_operation_n(); break;
        default:        print_error_message(); break
    }
}
```
***
### Program: `checking.c`
```C
// CHECKBOOK BALANCER
// andr-be 06/2023
#include <stdio.h>

int main(void)
{
    int cmd;
    float balance = 0.0f, credit, debit;

    printf("*** ACME CHECKBOOK-BALANCING PROGRAM ***\n");
    printf("Commands: 0=clear, 1=credit, 2=debit, ");
    printf("3=balance, 4=exit\n\n");

    for (;;) {
        printf("Enter a command: ");
        scanf("%d", &cmd);
        switch (cmd) {
            case 0:
                balance = 0.0f;
                break;
            case 1:
                printf("Enter amount of credi: ");
                scanf("%f", &credit);
                balance += credit;
                break;
            case 2:
                printf("Enter amount of debit: ");
                scanf("%f", &debit);
                balance -= debit;
                break;
            case 3: 
                printf("Current balance: $%.2f\n", balance);
                break;
            case 4:
                return 0;
            default:
                printf("Commands: 0=clear, 1=credit, 2=debit, ");
                printf("3=balance, 4=exit\n\n");
                break;
        }
    }
}
```
***
## The Null Statement
A statement can be ***null*** - devoid of symbols except for the semicolon at the end. Here's an example;
```C
i = 0; ; j = 1;
```
The null statement is primarily good for one thing; writing loops whose bodies are empty. 
```C
for (d = 2; d < n; d++)
    if (n % d == 0)
        break;

// this is equivalent to:
for (d = 2; d < n && n % d != 0; d++)
    /* empty loop body! */ ;
```
It's good practice to put the null statement on its own on a line with a semi colon; this allows others who read the code to better understand its intent.
***
### Accidentally Creating Null Statements
```C
// performs action regardless of condition
if (d == 0); // <-- ';'
    printf("Error: Division by 0\n");

// accidental infinite loop
i = 10;
while (i > 0); // <-- ';'
{
    printf("T mins %d and counting\n", i);
    --i;
}

// only doing one loop
i = 11;
while (--i > 0); // <-- ';'
    printf("T minus %d and counting\n", i);
```
***
## Q&A: Should you use `continue`?
Sure, whatever. Sometimes they come in handy:
```C
for (;;) {
    Data data = read_data();
    if (validate_1(data) == 0)
        continue;
    if (validate_2(data) == 0)
        continue;
    // ~~
    if (validate_n(data) == 0)
        continue;
    process(data);
}
```
