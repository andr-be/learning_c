# Chapter 4 Written Exercises
`// andr-be 06/2023`

## **1. Show the output produced by each of the following program fragments. Assume that i, j, and k are int variables.**

```C
/*A*/   i = 5; j = 3; 
        printf("%d %d", i / j, i % j);

/*B*/   i = 2; j = 3; 
        printf("%d", (i + 10) % j);

/*C*/   i = 7; j = 8; k = 9; 
        printf("%d", (i + 10) % k / j);

/*D*/   i = 1; j = 2; k = 3;
        printf("%d", (i + 5) % (j + 2) / k);
```
    A:  5 / 3, 5 % 3
        1 2

    B:  12 % 3
        0
    
    C:  (17) % 9 / 7
        8 / 7
        1

    D:  (6) % (4) / 3
        2 / 3
        0


## ***2. If `i` and `j` are positive integers, will the expression `(-i)/j` always have the same value as `-(i/j)`? Justify your answer.**
    I think they will, honestly. Unary Minus happens before division!
    
    If i = 10 & j = 2; in the instance of -(i/j) you're going to get -5, and for (-i)/j you still get -5.

    I'm not of the opinion that division of a negative number is undefined in C!

## **3. What is the value of each of the following expressions in C89? (Give all possible values if an expression may have more than one value.)**
```C
/*A*/    8 /  5

/*B*/   -8 /  5

/*C*/    8 / -5

/*D*/   -8 / -5
```
    A:    1
    B:   -1
    C:   -1
    D:    1

## **4. Repeat Exercise 3 for C99**
    A:   1
    B:  -1
    C:  -1
    D:   1

## **7. The algorithm for computing the UPC check digit ends with the following steps:**
```txt
1) Subtract 1 from the Total
2) Compute the remainder when the adjusted total is divided by 10
3) Subtract the remainder from 9
```
It's tempting to try and simplify the algorithm by using these steps instead;
```txt
1) Compute the remainder when the total is divided by 10.
2) Subtract the remainder from 10.
```
Why doesn't this technique work?

    Let's work it through!
    1)  total     == 100
        total - 1 == 99
        99 % 10   == 9
        9 - 9     == 0

    2)  total      == 100
        100 % 10   == 0
        10 - 0     == 10

    uh because you're doing a different mathematical operation?

## **8. Would the upc.c program still work if the expression `9 - ((total - 1) % 10)` were replaced by `(10 - (total % 10)) % 10`?**

    No, because you're doing a completely different operation lmao

## **9. Show the output produced by each of the following program fragments. Assume that `i`, `j` and `k` are `int` variables.**

```C
        int i, j, k;

/*A*/   i = 7; j = 8;
        i *= j + 1;
        printf("%d %d", i, j);
    
        7 *= (8 + 1)
        7 *= 9
        i == 63; j == 8
        // 63 8

/*B*/   i = j = k = 1
        i += j += k;
        printf("%d %d %d", i, j, k);

        i = j = k = 1;  k == 1;
        i += j += 1;    j == 2;
        i += 2;         i == 3;
        // 3 2 1

/*C*/   i = 1; j = 2; k = 3;
        i -= j -= k;
        printf("%d %d %d", i, j, k);
        
        i -= (j -= 3);
        i -= (-1);      
        k == 3; j == -1; i == 2;
        // 2 -1 3

/*D*/   i = 2; j = 1; k = 0;
        i *= j *= k;
        printf("%d %d %d", i, j, k);

        i *= (j *= 0); j == 0;
        i *= 0;        i == 0;
        // 0 0 0
```

## **10. Show the ouput produced by each of the following program fragments. Assume that `i` and `j` are `int` variables.**

```C
/*A*/   i = 6;
        j = i += 1;
        printf("%d %d", i, j);
        // 6 7

/*B*/   i = 5;
        j = (i -= 2) + 1;
        printf("%d %d", i, j);
        // 3 4

/*C*/   i = 7;
        j = 6 + (i = 2.5);
        printf("%d %d", i, j);
        // 2 8

/*D*/   i = 2; j = 8;
        j = (i = 6) + (j = 3);
        printf("%d %d", i, j);
        // 6 9
```

## ***11. Show the output produced by each of the following program fragments. Assume `i`, `j`, and `k` are `int` variables.**

```C
/*A*/   i = 1;
        printf("%d ", i++ - 1);
        printf("%d", i);
        // 0 2

/*B*/   i = 10; j = 5;
        printf("%d ", i++ - ++j);
        printf("%d %d", i, j);
        // 4 11 6

/*C*/   i = 7; j = 8;
        printf("%d ", i++ - --j); // i == 8; j == 7
        printf("%d %d", i, j);
        // -1 8 7

/*D*/   i = 3; j = 4; k = 5;
        printf("%d ", i++ - j++ + --k);
        // (3) - (4) + (4); i == 4; j == 5;
        printf("%d %d %d", i, j, k);
        // 3 4 5 4
```

## **12. Show the output produced by each of the following program fragments. Assume that `i` and `j` are `int` variables.**

```C
/*A*/   i = 5;
        j = ++i * 3 - 2;
        // (6) * 3 - 2
        // 18 - 2
        // j == 16; i == 6
        printf("%d %d", i, j);
        // 6 16

/*B*/   i = 5; 
        j = 3 - 2 * i++;
        // 3 - 2 * (5); i == 6;
        // j == -7
        printf("%d %d", i, j);
        // 6 -7

/*C*/   i = 7; 
        j = 3 * i-- + 2;
        // 3 * (7) + 2; i == 6;
        // j == 23;
        printf("%d %d", i, j);
        // 6 23

/*D*/   i = 7;
        j = 3 + --i * 2;
        // 3 + (6) * 2; i == 6;
        // j == 15;
        printf("%d %d", i, j);
        // 6 15
```

## **13. Only one of the expressions `++i` and `i++` is exactly the same as `(i += 1)`; which is it? Justify your answer.**
    I think it's ++i, because it evaluates to 6 at runtime for maths ordering purposes, whereas i++ evaluates to 5 and increments after that point.

## **14. Supply parentheses to show how a C compiler would interpret each of the following expressions.**

```C
/*A*/   a * b - c * d + e
        // (a * b) - ((c * d) + e)

/*B*/   a / b % c / d
        // ((a / b) % c) / d)

/*C*/   - a - b + c - + d
        // (((-a) - b) + c) - d

/*D*/   a * - b / c - d
        // ((a * (-b)) / c) - d
```

## **15. Give the values of `i` and `j` after each of the following expression statementes has been executed. Assume that `i` has the value `1` initially and j has the value `2`.**

```C
        int i = 1, j = 2;

/*A*/   i += j;
        // i == 3; j == 2

/*B*/   i--;
        // i == 0; j == 2

/*C*/   i * j / i;
        // i == 1; j == 2

/*D*/   i % ++j;
        // i == 1; j == 3
```