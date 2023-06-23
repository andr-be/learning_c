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
|`short int         ` |              -32,768  |          32,767  |
|`unsigned short int` |                    0  |          65,535  |
|`int               ` |              -32,768  |          32,767  |
|`unsigned int      ` |                    0  |          65,535  |
|`long int          ` |       -2,147,483,648  |   2,147,483,647  |
|`unsigned long int ` |                    0  |   4,294,967,295  | 
### 32 BIT MACHINES
| Type                |        Smallest Value |    Largest Value |
| ------------------- | --------------------: | ----------------:|
|`short int         ` |              -32,768  |          32,767  |
|`unsigned short int` |                    0  |          65,535  |
|`int               ` |       -2,147,483,648  |   2,147,483,647  |
|`unsigned int      ` |                    0  |   4,294,967,295  |
|`long int          ` |       -2,147,483,648  |   2,147,483,647  |
|`unsigned long int ` |                    0  |   4,294,967,295  | 
### 64 BIT MACHINES
|Type                |            Smallest Value|            Largest Value |
|--------------------|-------------------------:|-------------------------:|
|`short int         `|                   -32,768|                    32,767|
|`unsigned short int`|                         0|                    65,535|
|`int               `|            -2,147,483,648|             2,147,483,647|
|`unsigned int      `|                         0|             4,294,967,295|
|`long int          `|-9,223,372,036,854,775,808| 9,223,372,036,854,775,807|
|`unsigned long int `|                         0|18,446,744,073,709,551,615| 
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