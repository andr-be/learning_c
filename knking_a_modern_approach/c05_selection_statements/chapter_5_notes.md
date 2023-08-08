# Chapter 5: Selection Statements

## Table 1: C LOGICAL EXPRESSIONS

| Symbol       | Meaning                  |
| -----------: | :----------------------- |
| `<`          | less than                |
| `>`          | greater than             |
| `<=`         | less than or equal to    |
| `>=`         | greater than or equal to |
| `==`         | equal to                 |
| `!=`         | not equal to             |
| `!`          | logical negation         |
| `&&`         | logical *and*            |
| `\|\|`       | logical *or*             |

***

## RELATIONAL OPERATORS  

The expression `i < j < k` is legal in C, but it doesn't have the meaning you might expect from the expression.

The `<` operator is left associative, so the actual expression is equivalent to `(i < j) < k`.

This means that it first tests if `i < j`, which evaluates either to `0` or `1`.

*This* value is then compared to `k`; this equation does not test if `j` is in between `i` and `k`.

***

## LOGICAL OPERATORS

- `!expr` has the value `1` if `expr` has the value `0`.
- `expr1 && expr2` has the value `1` if the values of `expr1` and `expr2` are both non-zero.
- `expr1 || expr2` has the value `1` if either `expr1` or `expr2` (or both) has a non-zero value.

In all other cases, these operators produce the value `0`.

`&&` and `||` perform 'short-circuit' evaluations of their operands. That means that when they evaluate the left hand operand, if the total value can be deduced from this, the right hand operand is never evaluated.

Consider the following expression;
`i > 0 && ++j > 0`

Although we might expect `j` to increment as a side effect of this expression, if the left hand side evaluates to `0` (`i` is not greater than `0`) then the `&&` must necessarily evaluate to `0`, and `j` is never incremented!
***

## PRECEDENCE & ASSOCIATIVITY

The `!` operator has the same precedence as the unary plus and minmus operators.

The precedence of `&&` and `||` is lower than that of the relational and equality operators.

e.g. `i < j && k == m` means `(i < j) && (k == m)`

The `!` operator is right associative; `&&` and `||` are left associative.
***

## THE `if` STATEMENT

```C
if ( expression )  
   statement;

if ( expression )
{
   do_this();
   do_this_too();
}
```

***

## RANGE IDIOMS

```C
// used to test if something is outside a range
if (0 <= i && i >= n) ...

// used to test if something is inside a range
if (i < 0 || i >= n) ...
```

***

## THE `else` CLAUSE

```C
// one-line if-else
if ( expression ) statement; else statement;

// multiline if-else
if ( expression )
    do_this();
else
    do_other_thing();

// nested sorting inf-else
if (i > j) 
    if (i > k) 
        max = i;
     else 
        max = k;
else 
    if (j > k) 
        max = j;
    else 
        max = k;  
```

***

## CASCADED `if` STATEMENTS

```C
if (n < 0)
  printf("n is less than 0\n");
else if (n == 0)
  printf("n is equal to 0\n");
else
  printf("n is greater than 0\n")
```

***

## PROGRAM: `broker.c`

```C
// BROKER COMMISSION CALCULATOR
// andr-be 06/2023

#include <stdio.h>

int main(void)
{
    float commission, value;

    print("Enter value of trade: ");
    scanf("%f", &value);

    if (value < 2500.00f)
      commission = 30.00f + 0.17f * value;
    else if (value < 6250.00f)
      commission = 56.00f + 0.66f * value;
    else if (value < 20000.00f)
      commission = 76.00f + 0.34f * value;
    else if (value < 50000.00f)
      commission = 100.00f + 0.22f * value;
    else if (value < 500000.00f)
      commission = 155.00f + 0.11f * value;
    else
      commission = 255.00f + 0.09f * value;

    if (commission < 39.00f)
      commission = 39.00f;

    printf("Commission: $%.2f\n", commission);

    return 0;
}
```

***

## CONDITIONAL EXPRESSIONS

```C
// if expr1, then expr2, else expr3
expr1 ? expr2 : expr3

int i, j, k;
i = 1; j = 2;

// if i is greater than j, k = i; else k = j;
k = i > j ? i : j;          
// k is now 2 (== j)

// (if i is greater than or equal to 0, k = i + j; else k = 0 + j
k = (i >= 0 ? i : 0) + j;   
// k is now 3 (== i + j)
```

***

## CONDITIONAL EXPRESSION IDIOMS

```C
// instead of writing
if (i > j)
    return i;
else
    return j;

// you can use a conditional expression!
return i > j ? i : j;

// similarly, using `prinf()`;
if (i > j)
    printf("%d\n", i);
else
    printf("%d\n", j);

// we could instead replace it with
printf("%d\n", i > j ? i : j);
```

***

## BOOLEAN VALUES IN C89

```C
// CONFUSING & BAD
int flag;
flag = 0; // false
flag = 1; // true

// MORE IDIOMATIC
#define TRUE 1
#define FALSE 0
flag = FALSE;
flag = TRUE;

// COMMON WAY TO MAKE A BOOL TYPE
#define BOOL int
BOOL flag = TRUE;

// `if (!flag)/(flag)` IS CONSIDERED BETTER
if (flag == TRUE)
  do_thing();
else if (!flag)
  do_other_thing();
```

***

## BOOLEAN VALUES IN C99

```C
// C99 has a _Bool type
_Bool flag;

// _Bools can only ever be 1 or 0
flag = 5;     /* flag is assigned 1 */
if (flag)     /* tests whether flag is 1 */

#include <stdbool.h>
bool flag;    /* same as _Bool flag; */
flag = false;
flag = true;
```

***

## THE `switch` STATEMENT

```C
// General Form
switch ( expression ) {
  case constant-expression : statements
  ...
  case constant-expression : statements
  default : statements
}

// Practical Example
switch (grade) {
  case 4:   printf("Excellent!");
            break;
  case 3:   printf("Good!");
            break;
  case 2:   printf("Average!");
            break;
  case 1:   printf("Poor!");
            break;
  case 0:   printf("Fail!");
            break;
  default:  printf("ILLEGAL GRADE");
            break;
}

// Alternative Syntax with all similar cases on one line
switch (grade) {
  case 4: case 3: case 2: case 1:
            printf("Pass!");
            break;
  case 0:   printf("Fail!");
            break;
  default:  printf("Illegal grade!");
            break;
}
```

- `case`s must be constants, and cannot be ranges or variables.
- They can be stacked to allow fallthrough clausing.
- A `switch` statement is not required to have a `default` clause, if it's missing and the value of the expression doesn't match any of the `cases`, control passes to the next statement after the `switch`.

***

## THE ROLE OF THE `break` STATEMENT

```C
// A common error in C is forgetting to put break clauses in switches
switch (grade) {
  case 4:   printf("Excellent!");
  case 3:   printf("Good!");
  case 2:   printf("Average!");
  case 1:   printf("Poor!");
  case 0:   printf("Fail!");
  default:  printf("ILLEGAL GRADE");
}

// if the grade value is 3, we'll get this output:
Good!Average!Poor!Fail!ILLEGAL GRADE

// most people don't expect deliberate fallthrough
switch (grade) {
  case 4:   /*              */
  case 3:   /* FALL THROUGH */
  case 2:   /*              */
  case 1:   num_passing++;
            /* FALL THROUGH */
  case 0:   total_grades++;
            break;
}
```

***

## PROGRAM: `legal_date.c`

```C
// LEGAL DATE PRINTER
// andr-be 06/2023

#include <stdio.h>

in main(void)
{
  int month, day, year;

  printf("Enter date (dd/mm/yy): ");
  scanf("%d /%d /%d", &day, &month, &year);

  printf("Dated this %d", day);
  switch (day) {
    case 1: case 21: case 31:
      printf("st"); break;
    case 2: case 22:
      printf("nd"); break;
    case 3: case 23:
      printf("rd"); break;
    default:
      printf("th"); break;
  }
  printf(" day of ");
  
  switch (month) {
    case 1:   printf("January");     break;
    case 2:   printf("February");    break;
    case 3:   printf("March");       break;
    case 4:   printf("April");       break;
    case 5:   printf("May");         break;
    case 6:   printf("June");        break;
    case 7:   printf("July");        break;
    case 8:   printf("August");      break;
    case 9:   printf("Semptember");  break;
    case 10:  printf("October");     break;
    case 11:  printf("November");    break;
    case 12:  printf("December");    break;
  }

  printf(", 20%.2d.\n", year);
  return 0;
}
```

***
