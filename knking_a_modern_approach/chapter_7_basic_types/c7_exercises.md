# Chapter 7: Basic Types - Written Exercises

`// andr-be 07/2023`
***

## 1. Give the decimal value of each of the following integer constants

a) `077`

     0  1  2  3  4  5  6  7   |   0  1  2  3  4  5  6  7
    10 11 12 13 14 15 16 17   |   8  9 10 11 12 13 14 15
    20 21 22 23 24 25 26 27   |  16 17 18 19 20 21 22 23

    077 = (7 * 8) + 7 
    == 63

b) `0x77`

     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15

     0x77 = (7 * 16) + 7 = 112 + 7 
     == 119

c) `0XABC`

    ( A * 16^2) + ( B * 16^1) + ( C * 16^0)
    (10 * 16^2) + (11 * 16^1) + (12 * 16^0)
    (10 * 256)  + (11 *   16) + (12 *    1)
    2560 + 176 + 12
    == 2748

***

## 2. Which of the following are not legal constants in C?  

Classify each legal constant as either integer or floating-point.

a) `010E2`

    LEGAL: FLOATING POINT

b) `32.1E+5`

    LEGAL: FLOATING POINT (DOUBLE)

c) `0790`

    ILLEGAL: Octal digits only go up to 7!

d) `100_000`

    ILLEGAL: C does not let you break up integer values with underscores, unlike rust.

e) `3.978e-2`

    LEGAL: FLOATING POINT (DOUBLE)

***

## 3. Which of the following are not legal types in C?

a) `short unsigned int`

b) `short float`

c) `long double`

d) `unsigned long`

    short float and long double aren't legal types, because you cannot change the size of a floating point number with a modifier. You only have float and double.

## 4. If `c` is a variable of type `char`, which one of the following statements is illegal?

a) `i += c;     // i has type int`

b) `c = 2 * c - 1;`

c) `putchar(c);`

d) `printf(c);`

    Statement d) is illegal, as you haven't chosen a format specifier for the printf statement.

***

## 5. Which one of the following is not a legal way to write the number 65?

Assume that the character set is ASCII.

a) `'A'`

    ASCII 'A' = 65; 'a' = 97;

b) `0b1000001`

     1    0    0    0    0    0    1
    2^6  2^5  2^4  2^3  2^2  2^1  2^0    
     64   32   16    8    4    2    1
    == 65

c) `0101`

     1       0       1
    8^2     8^1     8^0
    == 65


d) `0x41`

      4     1
    16^1  16^0
    == 65

Trick question; they're all valid ways to represent 65!

***

## 6. For each of the following items of data, specify which one of the types `char`, `short`, `int`, or `long` is the smallest one guaranteed to be large enough to store the item.

a) Days in a month

    31
    char

b) Days in a year

    365
    short

c) Minutes in a day  

    (60 * 24) = 1,440
    int

d) Seconds in a day

    (60 * 60 * 24) = 86,400
    long

***

## 7. For each of the following character escapes, give the equivalent octal escape  

(Assume that the character set is ASCII.) You may wish to consult Appendix E. which lists the numerical codes for ASCII characters.

a) `\b` - Backspace

b) `\n` - Newline

c) `\r` - Carriage Return

d) `\t` - Horizontal Tab

***

## 8. Repeat Exercise 7, but give the equivalent hexadecimal escape

a) `\0x62`

b) `\0x6E`

c) `\0x72`

d) `\0x74`

***

## 9. Suppose that `i` and `j` are variables of type `int`. What is the type of the expression `i / j * 'a'`?

    int; the char is implicitly converted to integer type at j * 'a'

***

## 10. Suppose that `i` is a variable oif type `int`, `j` is a variable of type `long` and `k` is a variable of type `unsigned int`. What is the type of the expression `i + (int) j * k`?

    I think it's unsigned int? i is a signed int by default, j is cast as signed int and then k is unsigned int; I believe this forces the signed integers to promote themselves to unsigned. This is considered very bad practice!

***

## 11. Suppose that `i` is a variable of type `int`, `f` is a variable of type `float` and `d` is a variable of type `double`. What is the type of the expression `i * f / d`?

    I believe the resultant type will be an int; when an int is divided by a float, the float gets the fractional part cut off and integer division happens. Then when an integer is divided by a double, the same thing happens.

***

## 12. Suppose that `i` is a variable of type `int`, `f` is a variable of type `float` and `d` is a variable of type `double`. Explain what conversions take place during the execution of the following statement: `d = i + f`

    When you add an int to a float, it converts the float to an integer value by truncating the fractional portion. Then, when that integer is assigned to d, it converts again into a double precision float.

***

## 13. Assume that a program contains the following declarations and give the value and type of each expression

```C
char c = `\1`;
short s = 2;
int i = -3;
long m = 5;
float f = 6.5f;
double d = 7.5;
```

a) `c * i`

    int
    -1

a) `s + m`

    long
    7

a) `f / c`

    char 
    6

a) `d / s`

    int
    3

a) `f - d`

    double
    1.0

a) `(int) f`

    int
    6

***

## 14. Does the following statement always compute the fractional part of `f` correctly, assuming that `f` and `frac_part` are `float` variables? If not, what's the problem?

```C
frac_part = f - (int) f;
```

    As far as I'm aware, this is actually a common C idiom that's designed just for this particular scenario. I don't think there are any real limitations to this, except for instances where f is larger than the maximum int value, because of casting overflow.

***

## 15. Use `typedef` to create types named `Int8`, `Int16` and `Int32`. Design the types so that they represent 8-bit, 16-bit and 32-bit integers on your machine.

```C
typedef char  Int8;
typedef short Int16;
typedef int   Int32;
```

***