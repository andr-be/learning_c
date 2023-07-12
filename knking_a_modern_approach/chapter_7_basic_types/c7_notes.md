# Chapter 7: Basic Types - Notes

`// andr-be 06/2023`
***

## Integers

```C
The largest 16 bit signed integer has the binary representation:
0111111111111111
which has the value 32,767 (2^15-1)

The largest 32-bit signed integer is: 
01111111111111111111111111111111
which has the value 2,147,483,647 (2^31-1)

In their unsigned form:
16bit -> 1111111111111111 
         65,535 (2^16-1)

32bit -> 11111111111111111111111111111111 
         4,294,967,295 (2^32-1)

The leftmost bit contains the sign information; if we want to declare that it has no sign bit, we declare it to be unsigned.

By default in C, all integers are signed.
```

### 16 BIT MACHINES

| Type                |        Smallest Value |    Largest Value |
| ------------------- | --------------------: | ----------------:|
|`short int` |              -32,768  |          32,767  |
|`unsigned short int` |                    0  |          65,535  |
|`int` |              -32,768  |          32,767  |
|`unsigned int` |                    0  |          65,535  |
|`long int` |       -2,147,483,648  |   2,147,483,647  |
|`unsigned long int` |                    0  |   4,294,967,295  |

### 32 BIT MACHINES

| Type                |        Smallest Value |    Largest Value |
| ------------------- | --------------------: | ----------------:|
|`short int` |              -32,768  |          32,767  |
|`unsigned short int` |                    0  |          65,535  |
|`int` |       -2,147,483,648  |   2,147,483,647  |
|`unsigned int` |                    0  |   4,294,967,295  |
|`long int` |       -2,147,483,648  |   2,147,483,647  |
|`unsigned long int` |                    0  |   4,294,967,295  |

### 64 BIT MACHINES

|Type                |            Smallest Value|            Largest Value |
|--------------------|-------------------------:|-------------------------:|
|`short int`|                   -32,768|                    32,767|
|`unsigned short int`|                         0|                    65,535|
|`int`|            -2,147,483,648|             2,147,483,647|
|`unsigned int`|                         0|             4,294,967,295|
|`long int`|-9,223,372,036,854,775,808| 9,223,372,036,854,775,807|
|`unsigned long int`|                         0|18,446,744,073,709,551,615|
***

### Integer Types in C99

C99 also provides two additional standard integer types, `long long int` and `unsigned long long int`. There types were added to support the need for very large integers and 64 bit arithmetic.

```C
long long int:
min: -9,223,372,036,854,775,808 : -2^63
max:  9,223,372,036,854,775,807 :  2^63 - 1

unsigned long long int:
min:                          0 :  0
max: 18,446,744,073,709,551,615 :  2^64
```

Some advanced compilers may enable you to support signed and unsigned 128-bit integer types.
***

### Integer Constants

Numbers that appear in the text of a program, not numbers that are read, written, or computed. C allows integer constants to be written in decimal (base 10), octal (base 8), or hexadecimal (base 16).

Octal and hex are most convenient for writing low-level programs; we won't use these notations much until Chapter 20.

### Octal Numbers

An Octal number is written using only the digits 0 through 7.
All Octal numbers in C begin with 0
Each position in an Octal number represents a power of 8.

```C
017 0377 077777
0237 = (2 x 8^2) + (3 x 8^1) + (7 * 8^0)
0237 = 128 + 24 + 7
0237 = 159
```

### Hexadecimal Numbers

A Hexadecimal constant contains digits between `0` and `9` and letters between `a` and `f`, and always begin with `0x`

```C
The following are all equivalent:
{ 0xf, 0xff, 0x7fff } { 0XF, 0XFF, 0X7FFF } { 0xF, 0xFF, 0x7FFF }

 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
                               A  B  C  D  E  F
                               a  b  c  d  e  f

0x7fff = (7 x 16^3) + (15 x 16^2) + (15 x 16^1) + (15 x 16^0)
       =  28,672 + 3,840 + 240 + 15 
       =  32,767
```

To force the compiler to treat a constant as a long integer, use the letter `L` or `l`. To indicate to the compiler that the constant is unsigned, but the letter `U` or `u` after it.

```C
 15L   0377L   0x7FFFL
 15U   0377U   0x7FFFU
15LU  0377UL  0x7FFFLU
```

***

### Reading and Writing Integers

```C
unsigned int u;

scanf("%u", &u);    /* reads  u in base 10 */
printf("%u", u);    /* writes u in base 10 */

scanf("%o", &u);    /* reads  u in base  8 */
printf("%o", u);    /* writes u in base  8 */

scanf("%x", &u);    /* reads  u in base 16 */
printf("%x", u);    /* writes u in base 16 */
```

When reading or writing a short integer, put the letter `h` in front of `d`, `o`, `u` or `x`

```C
short s;

scanf("%hd", &s);
printf("%hd", s);
```

When reading or writing a *long* integer, put the letter `l` in front of `d`, `o`, `u`, or `x`

```C
long l;

scanf("%ld", &l);
printf("%ld", l);
```

When reading or writing a *long long* integer (C99 only), put the letters `ll` in front `d`, `o`, `u`, or `x`

```C
long long ll;

scanf("%lld", &11);
printf("%lld", ll);
```

***

### Program: `sum2.c`

```C
// INTEGER SUMMER V2

#include <stdio.h>

int main(void)
{
    long n, sum = 0;

    printf("This program sums a series of integers.\n");
    printf("Enter integers (0 to terminate): ");

    scanf("%ld", &n);
    while (n != 0) {
        sum += n;
        scanf("%ld", &n);
    }
    printf("The sum is: %ld\n", sum);

    return 0;
}
```

By simply changing the type of `n` to be a long instead of an int, we ensure it can go significantly higher.
***

## Floating Types

7.2 page 132

***

## Type Conversion

Implicit conversions are performed by the C compiler in the following situations;

- When the operands in an arithmetic or logical expression don't have the same type. (C performs what are known as the *usual arithmetic conversions.*)
- When the type of the expression on the right side of an assignment doesn't match the type of the variable on the left side.
- When the type of an argument in a function call doesn't match the type of the corresponding parameter.
- When the type of the expression in a `return` statement doesn't match the function's return type.

In all other scenarios, it is required for an explicit cast operation.

***

### Usual Arithmetic Conversions

Let's say that `f` has type `float` and `i` has type `int`. The usual artihmetic conversions will be applied to the operands in the expression `f + i` because their types aren't the same. Clearly, it's safer to convert `i` to floating point as the worst that can happen to `i` is a loss of precision.

On the other hand, trying to convert a `float` to an `int` is problematic, as it costs us the fractional part of the number and in the worst cases can result in a `0` if the float is bigger or smaller than the allowed `int` range of values.

We can divide the rules for performing the usual arithmetic conversions into two cases:

1) **The type of either operand is a floating type**  

Use the following diagram to promote the operand whose type is narrower:  

`float -> double -> long double`  

i.e. if one operand has type `long double`, then convert the other operand to type `long double`. Otherwise, if one operand has type `double`, convert the oper operand to type `double`. Otherwise, if one operand has type float, convert the other operand to type `float`.

2) **Neither operand type is a floating type**

First perform integral promotion on both operands (guaranteeing that neither operand will be a `char` or `short int`) then use the following diagram to promote the operand whose type is narrower;

`int -> unsigned int -> long int -> unsigned long int`

There's one special case that occurs when `long int` and `unsigned int` have the same length (32 bits, for example). Under these circumstances, if one operand has the type `long int` and the other has type `unsigned int`, both are converted to `unsigned long int`.  

***

### Conversions Between Signed & Unsigned Integers

When a signed operand is combined with an unsigned operand, the signed operand is converted to an unsigned value. The conversion involves adding or subtracting a multiple of `n + 1`, where `n` is the largest representable value of the unsigned type.  

Suppose that `int i = -10` and `unsigned int u = 10`; If we compare `i` and `u` using the `<` operator, we might expect to get the result `1` (`true`). However, before the comparion, `i` is converted to `unsigned int`. The value `4294967296` is added (largest `unsigned int` value), which gives a converted value of 4,294,967,286. This means `i < u == false`.  

Because of this, it's best to use unsigned integers as little as possible and to never mix them with signed integers.
***

### Usual Arithmetic Conversions Example

```C
char c;
short int s;
int i;
unsigned int u;
long int l;
unsigned long int ul;
float f;
double d;
long double ld;

i = i + c;      // c is converted to int
i = i + s;      // s is converted to int
u = u + i;      // i is converted to unsigned int
l = l + u;      // u is converted to long int
ul = ul + l;    // l is converted to unsigned long int
f = f + ul;     // ul is converted to float
d = d + f;      // f is converted to double
ld = ld + d;    // d is converted to long double

```

***

### Conversion During Assignment

C follows the simple rule that during assignment, the expression on the right side of the assignment is converted to the type of the variable on the left side.

If the variables type is at least as 'wide' as the expression's, this will work fine;

```C
i = c;      // c is converted to int
f = i;      // i is converted to float
d = f;      // f is converted to double
```

Other cases are more problematic; assigning a floating point number to an integer will drop the fractional part of the number;

```C
i = 842.97;     // i is now 842
i = -842.97;    // i is now -842
```

If you want to declare a float, use an f after the number e.g. `3.14159f`, otherwise you'll end up with a double.

***

### Implicit Conversions in C99

The rules for implicit conversion are slightly different in C99, primarily as a result of C99 having additional types. (`_Bool`, `long long` types, extended integer types and complex types). For the purposes of defining conversion rules, C99 gives each integer type a 'conversion rank':

1) `long long int`, `unsigned long long int`
2) `long int`, `unsigned long int`
3) `int`, `unsigned int`
4) `short int`, `unsigned short int`
5) `char`, `signed char`, `unsigned char`
6) `_Bool`

(This does not include extended integer types or enumerated types)

***

### Signed and Unsigned Characters

Signed characters normally have values between -128 and 127; Unsigned characters have values between 0 and 255.

Most of the time, we don't care if a character is signed or unsigned, but on the odd occasion it's necessary, we can declare which it should be explicitly. Don't assume a char is either signed or unsigned, as this is not specified by the C standard.

```C
signed char sch;
unsigned char uch;
```

C89 uses the terms **integral types** to refer to refer to both integer types and character types, as well as enumerated types.

C99 doesn't use this term, instead expanding the meaning of **integer types** to refer include the character types and the enumerated types. C99's `_Bool` is considered to be an unsigned integer type.

***

### Arithmetic Types in C99

| Type     | Subtype |
| -------- | ------- |
| Integer  | `char`<br>Signed integer types, both standard (`signed char`, `short int`, `int`, `long int`, `long long int`)<br>Unsigned integer types, both standard (`unsigned char`, `unsigned short int`, `unsigned int`, `unsigned long int`, `unsigned long long int`, `_Bool`) and extended<br>Enumerated types
| Floating | Real floating types (`float`, `double`, `long double`)<br>Complex types (`float _Complex`, `double _Complex`, `long double _Complex`) |

***

### Escape Sequences

| Name            | Escape Sequence |
| --------------- | :-------------: |
| Alert(Bell)     | `\a`            |
| Backspace       | `\b`            |
| Form feed       | `\f`            |
| New line        | `\n`            |
| Carriage Return | `\r`            |
| Horizontal Tab  | `\t`            |
| Vertical tab    | `\v`            |
| Backslash       | `\\`            |
| Question Mark   | `\?`            |
| Single quote    | `\'`            |
| Double quote    | `\"`            |

***

### Numeric Escape Sequences

To write a numeric escape for a particular character, look up the character's octal or hexadecimal value. The ASCII escape character (decimal value: 27) has the value 33 in octal and 1B in hex. Either of these codes can be used to write an escape sequence.

- An **octal escape sequence** consists of the `\` character followed by an octal number with at most three digits. The maximum value is normally `377` octal. The escape character could be written as `\33` or `\033`. Octal numbers in escape sequences **do not** have to begin with `0`.
- A **hexadecimal escape sequence** consists of `\x` followed by a hexadecimal number, that can't exceed `FF`. This escape character could be written as `\x1b` or `\x1B`. The `x` **must** be lower case, but the hex digits can be in any case.

As escape sequences can get fairly cryptic, it's common for C programmers to give them names with `#define`:

```C
#define ESC '\33'   // ASCII escape character
```

***

### Character-Handling Functions

One approach to converting lower case letters to upper case letters is as follows:

```C
if ('a' <= ch && ch <= 'z')
    ch = ch - 'a' + 'A'
```

A faster, and more portable, way to convert case is to call C's `toupper` library function:

```C
#include <ctype.h>  // libc header containing toupper

...

ch = toupper(ch);   // converts ch to upper case
```

`toupper` checks whether its argument is a lower-case latter. If so, it returns the corresponding upper-case letter. Otherwise, `toupper` returns the value of the argument.  

***

## Casting

Sometimes we need a greater degree of control over type conversion. For this reason, we can use ***casts***.  

A cast expression has the form: `( type-name ) expression`; `type-name` is the type to which `expression` should be converted.  

```C
float f, frac_part;

frac_part = f - (int) f;
```

Cast expressions enable us to document type conversions that would take place anyway; to make them more explicit in the source. They also allow us to overrule the compiler and force it to do conversions that we want;

```C
i = (int) f;        // f is converted to int
```

Consider the following example;

```C
float quotient;

int divident, divisor;

quotient = divident / divisor;
```

If written like this, the result of the division will be converted to `float` before being stored in quotient. However, we probably want `dividend` and `divisor` converted to `float` *before* the division so we get a more exact answer without losing the fractional portion.

```C
quotient = (float) dividend / divisor;
```

Divisor doesn't need to be cast, since casting `dividend` to `float` forces the compiler to convert `divisor` to `float` also.

Casts are sometimes necessary to avoid overflow:

```C
long i;
int j = 1000;

i = j * j;      // could overflow!
```

This looks unproblematic at first glance, but the problem is that when two `int` values are multiplied, the result will have `int` type. But `j * j` is too large to represent as an `int` on some machines, causing an overflow. Fortunately, we can fix it with a cast.

```C
i = (long) j * j;
```

This statement however, would not work:

```C
i = (long) (j * j);
```

Because the result of `j * j` would still overflow, but then be converted to `long`.

***

## Type Definitions

In a previous example, we used a preprocessor `#define` directive to set up a Boolean type. A more idiomatic way to do this through use of a `typedef`.

```C
#define BOOL int

...

typedef int Bool;
```

Note that the name of the new type being defined comes last in the expression. Capitalising the first letter of a type name isn't required, but it's a common convention employed by C programmers.

Using typedef makes the compiler add `Bool` to the list of type names that it recognises, and can be used the same way as the built in types.

```C
Bool flag;      // same as int flag;
```

***

### Advantages of Type Definitions

Type definitions can make a program more easily understood. For example, suppose that the variables `cash_in` and `cash_out` will be used to store dollar amounts.

```C
typedef float Dollars;

Dollars cash_in, cash_out;
```

is more informative than just using `float`. Similarly, if we later decide that `Dollars` should really be defined as `double`, all we need to do is change the type definition: 

```C
typedef double Dollars;
```

Which means we need not change all of the different `float` variables that store dollar amounts and change their declarations. 

***

### Type Definitions and Portability

Type definitions are very important for ease of portability with the code. One of the problems with moving a program from one PC to another is that the types may have different ranges on different machines. An assignment like `i = 100000;` is fine on a machine with 32-bit integers, but will fail on a machine with 16-bit integers.

***For greater portability, consider using `typedef` to define new names for integer types.***

Suppose we're writing a program that needs variables capable of storing quantities in the range 0-50,000. We could use `long` variables for the purpose, but we'd rather use `int` variables since arithmetic on them may be faster than the same operations on `long`; they may also take up less space.

Instead of using int to declare quantity variables, we can define our own type:

```C
typedef int Quantity;

Quantity q;
```

If we transport the program to a machine with shorter integers, we'll change the definition of `Quantity`. This doesn't actually solve all of our problems, since changing the definition of `Quantity` may affect the way `Quantity` variables are used. 

At the very least, calls of `printf` and `scanf` that use `Quantity` variables will need to be changed, from `%d` to `%ld`.

***

### Integer types in C99 with \<`stdint.h`\> 

In C99, the `<stdint.h>` header uses `typedef` to define names for integer types with a particular number of bits. For example, `int32_t` is a signed integer type with exactly 32 bits. Use of these types is an effective way to make programs more portable.

```C
#include <stdint.h>

// MAX WIDTH
intmax_t        uintmax_t

// Specific width integer types
int8_t          uint8_t
int16_t         uint16_t
int32_t         uint32_t
int64_t         uint64_t

// Minimum size integers / i.e. at least 8/16/32/64 bits
int_least8_t     uint_least8_t
int_least16_t    uint_least16_t
int_least32_t    uint_least32_t
int_least64_t    uint_least64_t

// Fast integers / as fast as any other int type with specified width
int_fast8_t     uint_fast8_t
int_fast16_t    uint_fast16_t
int_fast32_t    uint_fast32_t
int_fast64_t    uint_fast64_t
```

***

## The `sizeof` Operator

The `sizeof` operator allows a program to determine how much memory is required to store values of a particular type. The value of the expression:

```C
sizeof  ( type-name )
```

is an unsigned integer representing the number of bytes required to store a value belonging to *type-name*. `sizeof(char)` is always 1, but the sizes of the other types may vary. On a 32-bit machine, `sizeof(int)` is usually 4.

Printing a `sizeof` value requires care, because the type of a `sizeof` expression is an implementation-defined type named `size_t`. In C89 it's best to convert the value of the expression to a known type before printing it. `size_t` is guaranteed to be an unsigned integer type, so it's safest to cast a `sizeof` to `unsigned long` and then print it with `%lu`.

In C99, the `size_t` type can be larger than `unsigned long`. However, the `printf` function in C99 is capable of displaying `size_t` values directly, without needing a cast. The trick is to use the letter `z` in the conversion specification, followed by one of the integer codes (typically `u`).  

***