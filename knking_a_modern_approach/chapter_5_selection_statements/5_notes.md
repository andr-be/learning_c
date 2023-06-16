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
> ## RELATIONAL OPERATORS  
> The expression `i < j < k` is legal in C, but it doesn't have the meaning you might expect from the expression. 
>
> The `<` operator is left associative, so the actual expression is equivalent to `(i < j) < k`.
>
> This means that it first tests if `i < j`, which evaluates either to `0` or `1`. 
>
> *This* value is then compared to `k`; this equation does not test if `j` is in between `i` and `k`.

***

> ## LOGICAL OPERATORS
> - `!expr` has the value `1` if `expr` has the value `0`.
> - `expr1 && expr2` has the value `1` if the values of `expr1` and `expr2` are both non-zero.
> - `expr1 || expr2` has the value `1` if either `expr1` or `expr2` (or both) has a non-zero value.
>
> In all other cases, these operators produce the value `0`.
>
> `&&` and `||` perform 'short-circuit' evaluations of their operands. That means that when they evaluate the left hand operand, if the total value can be deduced from this, the right hand operand is never evaluated. 
> 
> Consider the following expression;
> `i > 0 && ++j > 0`
> 
> Although we might expect `j` to increment as a side effect of this expression, if the left hand side evaluates to `0` (`i` is not greater than `0`) then the `&&` must necessarily evaluate to `0`, and `j` is never incremented!
***
> ## PRECEDENCE & ASSOCIATIVITY
> The `!` operator has the same precedence as the unary plus and minmus operators.
>
> The precedence of `&&` and `||` is lower than that of the relational and equality operators.
>
> e.g. `i < j && k == m` means `(i < j) && (k == m)`
>
> The `!` operator is right associative; `&&` and `||` are left associative.
***
> ## THE `if` STATEMENT
> ```C
> if ( expression )  
>    statement;
>
> if ( expression )
> {
>    do_this();
>    do_this_too();
> }
> ```
***
> ## RANGE IDIOMS    
> ```C
> // used to test if something is outside a range
> if (0 <= i && i >= n) ...
>
> // used to test if something is inside a range
> if (i < 0 || i >= n) ...
> ```
***
> ## THE `else` CLAUSE
> ```C
> // one-line if-else
> if ( expression ) statement; else statement;
> 
> // multiline if-else
> if ( expression )
>     do_this();
> else
>     do_other_thing();
> 
> // nested sorting inf-else
> if (i > j) 
>     if (i > k) 
>         max = i;
>      else 
>         max = k;
> else 
>     if (j > k) 
>         max = j;
>     else 
>         max = k;  
> ```
***
> ## CASCADED `if` STATEMENTS
> ```C
> if (n < 0)
>   printf("n is less than 0\n");
> else if (n == 0)
>   printf("n is equal to 0\n");
> else
>   printf("n is greater than 0\n")
> ```
***
> ## `broker.c`
> ```C
> // BROKER COMMISSION CALCULATOR
> // andr-be 06/2023
> 
> #include <stdio.h>
> 
> int main(void)
> {
>     float commission, value;
> 
>     print("Enter value of trade: ");
>     scanf("%f", &value);
> 
>     if (value < 2500.00f)
>       commission = 30.00f + 0.17f * value;
>     else if (value < 6250.00f)
>       commission = 56.00f + 0.66f * value;
>     else if (value < 20000.00f)
>       commission = 76.00f + 0.34f * value;
>     else if (value < 50000.00f)
>       commission = 100.00f + 0.22f * value;
>     else if (value < 500000.00f)
>       commission = 155.00f + 0.11f * value;
>     else
>       commission = 255.00f + 0.09f * value;
> 
>     if (commission < 39.00f)
>       commission = 39.00f;
> 
>     printf("Commission: $%.2f\n", commission);
> 
>     return 0;
> }
> ```