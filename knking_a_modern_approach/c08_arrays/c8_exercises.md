# Chapter 8: Arrays - Written Exercises

andr-be 07/2023

***

## 1. We discussed using the expression `sizeof(a) / sizeof(a[0])` to calculate the number of elements in an array. The expression `sizeof(a) / sizeof(t)`, where `t` is the type of `a`'s elements, would also work, but it's considered an inferior technique. Why?

    I genuinely have no idea why it would be considered bad practice. Is it because you can misidentify what's in the array? Is it because you can change what the array contains elsewhere and not break the code if you use sizeof(a[0])? Who can say.

***

## 2. The Q&A Section shows how to use a letter as an array subscript. Describe how to use a digit (in character form) as a subscript.

```C
// lowercase character array script
char ch;
lettercount[ch-'a'] = 0;

// digit character subscript?
char dg;
numbercount[dg-'0'] = 0;
```

***

## 3. Write a declaration of an array named `weekend` containing seven `bool` values. Include an initialiser that makes the first and last values `true`; all other values should be `false`.

```C
#include <stdbool.h>

int main(void) {
    bool weekend[7] = {true, false, false, false, false, false, true};
    return 0;
}
```

***

## 4. Repeat exercise 3, but this time use a designated initialiser. Make the initialiser as short as possible.

```C
#include <stdbool.h>

int main(void) {
    bool weekend[7] = {true, [6] = true};
    return 0;
}
```

***

## 5. The Fibonacci numbers are 0, 1, 1, 2, 3, 5, 8, 13, ..., where each number is the sum of the two preceding numbers. Write a program fragment that declares an array named `fib_numbers` of length 40 and fills the array with the first 40 Fibonacci numbers. 

> Hint: Fill in the first two numbers individually, then use a loop to compute the remaining numbers.

```C
int main(void) {
    int fib_numbers[40] = {0, 1};
    
    for (int i = 2; i < 40; i++) 
        fib_numbers[i] = fib_numbers[i-1] + fib_numbers[i-2];

    return 0;
}
```

***

## 6. Calculators, watches, and other electronic devices ofdten rely on seven-segment displays for numerical output. To form a digit, such devices "turn on" some of the segments while leaving others "off".

Suppose we want to set up an array that remembers which segments should be "on" for each digit. Let's number the segments as follows:

```txt
     0
    --- 
5  | 6 |  1
    ---
4  | 3 |  2
    ---
```

If we were to represent this array in C, with each row representing one digit: (first line given by problem)

```C
const int segments[10][7] = {
    {1, 1, 1, 1, 1, 1, 0},     // 0
    {0, 1, 1, 0, 0, 0, 0},     // 1
    {1, 1, 0, 1, 1, 0, 1},     // 2
    {1, 1, 1, 1, 0, 0, 1},     // 3
    {1, 1, 0, 0, 0, 1, 1},     // 4
    {1, 0, 1, 1, 0, 1, 1},     // 5
    {1, 0, 1, 1, 1, 1, 1},     // 6
    {1, 1, 1, 0, 0, 0, 0},     // 7
    {1, 1, 1, 1, 1, 1, 1},     // 8
    {1, 1, 1, 1, 0, 1, 1}      // 9
}    
```

***

## 7. Using the shortcuts described in Section 8.2, shrink the initialiser for the segments array as much as you can.

```C
const int segments[10][7] = {{1, 1, 1, 1, 1, 1},        // 0
                             {0, 1, 1},                 // 1
                             {1, 1, 0, 1, 1, 0, 1},     // 2
                             {1, 1, 1, 1, [6] = 1},     // 3
                             {1, 1, [5] = 1, 1},        // 4
                             {1, 0, 1, 1, 0, 1, 1},     // 5
                             {1, 0, 1, 1, 1, 1, 1},     // 6
                             {1, 1, 1},                 // 7
                             {1, 1, 1, 1, 1, 1, 1},     // 8
                             {1, 1, 1, 1, 0, 1, 1}}     // 9
```

This is deeply ugly.

***

## 8. Write a declaration for a two-dimensional array named `temperature_readings` that stores one month of hourly temperature readings.

> For simplicity, assume that a month has 30 days. The rows of the array should represent days of the month, the columns should represent hours of the day.

```C
float temperature_readings = [30][24];
```

***

## 9. Using the array of Exercise 8, write a program fragment that computes the average temperature for a month (averaged over all days of the month and all hours of the day)

```C
float get_average_temp(float input_temps[30][24]) {
    float sum = 0.0f, 
          total = 30.0f * 24.0f;

    for (int i = 0; i < 30; i++)
        for (int j = 0; j < 24; j++)
            sum += input_temps[i][j];

    return sum / total;
}
```

***

## 10. Write a declaration for an `8 x 8 char` array named `chess_board`. Include an initialser that puts the following data in the array (one `char` per array element).

    r n b q k b n r
    p p p p p p p p
      .   .   .   .
    .   .   .   .
      .   .   .   .
    .   .   .   .
    P P P P P P P P
    R N B Q K B N R

```C
char chess_board[8][8] = {
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {' ', '.', ' ', '.', ' ', '.', ' ', '.'},
    {'.', ' ', '.', ' ', '.', ' ', '.', ' '},
    {' ', '.', ' ', '.', ' ', '.', ' ', '.'},
    {'.', ' ', '.', ' ', '.', ' ', '.', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
}
```

***

## 11. Write a program fragment that declares an `8x8 char` array named `checker_board` and then uses a loop to store the following data into the array. (one character per array element.)

    B R B R B R B R
    R B R B R B R B
    B R B R B R B R
    R B R B R B R B
    B R B R B R B R
    R B R B R B R B
    B R B R B R B R
    R B R B R B R B

```C
char checker_board[8][8] = {0};

for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
        checker_board[i][j] = ((i + j) % 2 == 0) ? 'B' : 'R'
```

***
