# Chapter 5 - Written Exercises
`// andr-be 06/2023`
***
## 1. The following program fragments illustrate the relational and equality operators. Show the output produced by each, assuming that `i`, `j` and `k` are int `values`.
```C
/*A*/   i = 2; j = 3; 
        k = i * j == 6;
        printf("%d", k);
        - - --
        k = (2 * 3) == 6
        k = (6) == 6
        k = 1
        // TRUE

/*B*/   i = 5; j = 10; k = 1;
        printf("%d", k > i < j);
        - - -
        (1 > 5) < 10
        (0) < 10
        1
        // TRUE

/*C*/   i = 3; j = 2; k = 1; 
        printf("%d", i < j == j < k);
        - - -
        (((3 < 2) == 2) < 1)
        (((0) == 2) < 1)
        ((0) < 1)
        1
        // TRUE

/*D*/   i = 3; j = 4; k = 5;
        printf("%d", i % j + i < k);
        - - -
        ((3 % 4) + 3) < 5
        ((3) + 3) < 5
        (6) < 5
        0
        // FALSE

```
***
## 2. The following program fragments illustrate the logical operators. Show the output produced by each, assuming that `i`, `j`, and `k` are `int` variables.
```C
/*A*/   i = 10; j = 5;
        printf("%d", !i < j);
        - - -
        0 < 5
        1
        // TRUE

/*B*/   i = 2; j = 1; 
        printf("%d", !!i + !j);
        - - -
        !!(2) + !(1)
        !(0) + 0
        1 + 0
        // TRUE

/*C*/   i = 5; j = 0; k = -5; 
        printf("%d", i && j || k);
        - - -
        (5 && 0) || -5
        0 || -5     // -5 is technical a truthy value!
        1
        // TRUE

/*D*/   i = 1; j = 2; k = 3;
        printf("%d", i < j || k);
        - - -
        (1 < 2) || 3
        1 || 3
        1
        // TRUE

```
***
## 3. The following program fragments illustrate the short-circuit behaviour of logical expressions. Show the output produced by each, assuming that `i`, `j` and `k` are `int` variables.
```C
/*A*/   i = 3; j = 4; k = 5;
        printf("%d ", i < j || ++j < k);
        printf("%d %d %d", i, j, k);
        - - -
        (3 < 4) || -> SHORT CIRCUIT!
        // 1 3 4 5

/*B*/   i = 7; j = 8; k = 9; 
        printf("%d ", i - 7 && j++ < k);
        printf("%d %d %d", i, j, k);
        - - -
        (7 - 7) && -> SHORT CIRCUIT!
        // 0 7 8 9

/*C*/   i = 7; j = 8; k = 9; 
        printf("%d ", (i = j) || (j = k));
        printf("%d %d %d", i, j, k);
        - - -
        (8) || -> SHORT CIRCUIT!
        // 1 8 8 9

/*D*/   i = 1; j = 1; k = 1;
        printf("%d ", ++i || ++j && ++k);
        printf("%d %d %d", i, j, k);
        - - -
        (2 || 2) && ++k
        1 && 2
        // 1 2 2 2
```
***
## *4. Write a single expression whose value is either `-1`, `0` or `+1`, depending on whether `i` is less than, equal to, or greater than `j`, respectively.
```C
if (i <  j) x = -1
if (i == j) x =  0
if (i >  j) x =  1
```
```C
// CHATGPT
int chat_gpt_cheat(int i, int j){
    return (i > j) - (i < j);
}
```
***
## *5. Is the following `if` statement legal?
```C
if (n >= 1 <= 10)
    printf("n is between 1 and 10\n");
```
If so, what does it do when `n` is equal to `0`?

    I don't think it works like it should;
    - - -
    n = 0;
    (n >= 1) <= 10
    (0) <= 10
    1
    - - -
    It should evaluate to FALSE!
***
## *6. Is the following `if` statement legal?
```C
if (n == 1 - 10)
    printf("n is between 1 and 10\n");
```
If so, what does it do when `n` is equal to `5`?

    I think it's legal, but it doesn't achieve the intent of the statement.
    - - -
    n = 5;
    n == (1 - 10)
    n == 9
    0
    - - -
    It should evaluate to TRUE!
***
## 7. What does the following statement print of `i` has the value `17`? What does it print if `i` has the value `-17`?
```C
printf("%d\n", i >= 0 ? i : -i);

// i ==  17; 17
// i == -17; 17
```
    It essentially just reverses the input if its negative.
    "if i is greater than or equal to 0, print i, otherwise print -i."
***
## 8. The following `if` statement is unnecessarily complicated. Simplify it as much as possible. (Hint: The entire statement can be replaced by a single assignment)
```C
if (age >= 13)
    if (age <= 19)
        teenager = true;
    else
        teenager = false;
else if (age < 13)
    teenager = false;
```

```C
teenager = (age >= 13 && age <= 19);
```
***
## 9. Are the following `if` statements equivalent? If not, why not?
```C
char score_to_grade_1(int score) {
    if      (score >= 90) return 'A';

    else if (score >= 80) return 'B';

    else if (score >= 70) return 'C';

    else if (score >= 60) return 'D';

    else                  return 'F';
}
char score_to_grade_2(int score) {
    if      (score < 60) return 'F';

    else if (score < 70) return 'D';

    else if (score < 80) return 'C';

    else if (score < 90) return 'B';

    else                 return 'A';
}
```
    I think they are equivalent, having typed them all up. All the grade boundaries are the same, all of the results will get the same grade regardless of the input score. 
    
    The only difference is the order of evaluation of cases; if you were expecting more Fs than As it might make sense to go with function 2 instead of 1?
***
## *10. What output does the following program fragment produce? (Assume that `i` is an `int` variable.)
```C
i = 1;
switch (i % 3) {
    case 0: printf("zero");
    case 1: printf("one");
    case 2: printf("two");
}
```
    Modulo refers to the remainder of the LHS operand, not the RHS.
    1 % 3 == 1
    There's also a fallthrough that happens after Case 1; no `break'` statement!
    "onetwo"
***
## 11. The following tables shows telephone area codes in the state of Georgia along with the largest city in each area;

| Area Code | Major City |
| --------- | ---------- |
| 229       | Albany     |
| 404       | Atlanta    |
| 470       | Atlanta    |
| 478       | Macon      |   
| 678       | Atlanta    |
| 706       | Columbus   |
| 762       | Columbus   |
| 770       | Atlanta    |
| 612       | Savannah   |

Write a `switch` statement whose controlling expression is the variable `area_code`. If the value of `area_code` is in the table, the `switch` statement will print the corresponding city name. Otherwise, the `switch` statement will display the message `"Area code not recognized"` Use the techniques discussed in Section 5.3 to make the `switch` statement as simple as possible.
```C
void print_largest_city(int area_code) {
    switch (area_code) {
        case 229: printf("Albany");   break;
        case 478: printf("Macon");    break; 
        case 612: printf("Savannah"); break;
        case 706: /* COLUMBUS */
        case 762: printf("Columbus"); break;
        case 404: /* ATLANTA */
        case 470: /* ATLANTA */
        case 678: /* ATLANTA */
        case 770: printf("Atlanta");  break;
        default:  printf("Area code not recognized.");
    }
}
```