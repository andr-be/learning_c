# Chapter 6: Loops - Written Exercises

`// andr-be 06/2023`
***

## 1. What output does the following program fragment produce?

```C
i = 1;
while (i <= 128) {
    printf("%d ", i);
    i *= 2;
}
```

    1 2 4 8 16 32 64 128
***

## 2. What output does the following program fragment produce?

```C
i = 9384;
do {
    printf("%d ", i);
    i /= 10;
} while (i > 0);
```

    9384 938 93 9
***

## *3. What output does the following `for` statement produce?

```C
for (i = 5, j = i - 1; i > 0, j > 0; --i, j = i - 1)
    printf("%d ", i)
```

    5 4 3 2    
***

## 4. Which one of the following statements is not equivalent to the other two (assuming that the loop bodies are the same)?

```C
/*A*/   for (i = 0; i < 10; i++) ...

/*B*/   for (i = 0; i < 10; ++i) ...

/*C*/   for (i = 0; i++ < 10; )  ...
```

    At the start of the body of loop C; i = 1.
    Also, the end of loop C i == 10.
    This is because i++ is evaluated as i, then increments.
***

## 5. Which one of the following statements is not equivalent to the other two (assuming that the loop bodies are the same)?

```C
/*A*/   while (i < 10) {...}

/*B*/   for (; i < 10;) {...}

/*C*/   do {...} while (i < 10);
```

    C is different, because if `i` is greater than 10 at the start of the loop, it will still run, whereas the other two will fail to run as their conditions will start as false.

    `do while` ensures that the loop body runs at least once.
***

## 6. Translate the program fragment of Exercise 1 into a single `for` statement

```C
i = 1;
while (i <= 128) {
    printf("%d ", i);
    i *= 2;
}
```

```C
for (i = 1; i <= 128; i *= 2)
    printf("%d ", i);
```

***

## 7. Translate the program fragment of Exercise 2 into a single `for` statement

```C
i = 9384;
do {
    printf("%d ", i);
    i /= 10;
} while (i > 0);
```

```C
for (i = 9384; i > 0; i /= 10)
    printf("%d ", i);
```

***

## *8. What output does the following `for` statement produce?

```C
for (i = 10; i >= 1; i /= 2)
    printf("%d ", i++);
```

    10 5 3 2 1 1 1 1 1 ...

    print 10;   i = 11 / 2
    print 5;    i =  6 / 2
    print 3;    i =  4 / 2
    print 2;    i =  3 / 2
    print 1;    i =  2 / 2
    // INFINITE LOOP
    print 1;    i =  2 / 2

***

## 9. Translate the `for` statement of exercise 8 into an equivalent `while` statement. You will need one statement in addition to the while loop itself

```C
for (i = 10; i >= 1; i /= 2)
    printf("%d ", i++);
```

```C
i = 10;
while (i >= 1) {
    printf("%d ", i++);
    i /= 2;
}
```

***

## 11. What output does the following program fragment produce?

```C
sum = 0;
for (i = 0; i < 10; i++) {
    if (i % 2)  
        continue;
    sum += i;
}
printf("%d\n", sum);
```

```C
// if i == x*2, i % 2 == false (0)
0 + 2 + 4 + 6 + 8
20
```

***

## 12. The following "prime-testing" loop appeared in Section 6.4 as an example

```C
for (d = 2; d < n; d++)
    if (n % d == 0)
        break;
```

This loop isn't very efficient. It's not necessary to divice n by all numbers between 2 and n - 1 to determine whether it's prime. In fact, we only need to check divisors up to the square root of n. Modify the loop to take advantage of this fact.

*Hint: Don't try to compute the square root of `n`; instead compare `d * d` with `n`.*

```C
for (d = 2; d * d < n; d++)
    if (n % d == 0)
        break;
```

***

## 13. Rewrite the following loop so that its body is empty

```C
for (n = 0; m > 0; n++)
    m /= 2;
```

```C
for (n = 0; m > 0; n++, m /= 2)
    /*EMPTY*/;
```

***

## 14. Find the error in the following program fragment and fix it

```C
if (n % 2 == 0);
    printf("n is even\n");
```

    There's a rogue semi-colon after the if condition, meaning the printf statement will fire regardless of what n % 2 is.
***
