# Chapter 12: Pointers and Arrays

> *Optimisation hinders evolution.*

When pointers point to array elements, C allows us to perform arithmetic on the pointers, which leads to an alternative way of precessing arrays where pointers take the place of array subscripts.

One thing to be aware of is that one of the primary reasons people used array arithmetic was that it was more efficient; however now (in 2008) compilers have improved to the extent that this is less of a factor, and so pointer arithmetic is relatively less important for efficiency.

## 12.1 Pointer Arithmetic

Suppose that `a` and `p` have been declared: `int a[10], *p;` we can make `p` point to `a[0]` by writing `p = &a[0];` which means We can now access `a[0]` through `p`. 

e.g. we can store the value 5 in `a[0]` by writing: `*p = 5`.

Making a pointer `p` point to an element of an array isn't particular groundbreaking. By performing ***pointer arithmetic*** (address arithmetic) on `p`, we can access the other elements of `a`. C supports 3 forms of pointer arithmetic:

- Adding an integer to a pointer
- Subtracting an integer from a pointer
- Subtracting one pointer from another

The following examples assume:

```C
int a[10], *p, *q, i;
```

### Adding an Integer to a Pointer

Adding an integer `j` to a pointer `p` yields a pointer to the element `j` places after the one that `p` points to. If `p` points to the array element `a[i]` then `p+j` points to `a[i+j]` if it exists.

```C
int *p, a[10] = {0};

p = &a[2];      /*          [p]
                             v 
                     a[0][1][2][3][4][5][6][7][8][9]
                */  
q = p + 3;      /*          [p]      [q]
                             v        v
                     a[0][1][2][3][4][5][6][7][8][9]
                */  
p += 6;         /*                   [q]      [p]
                                      v        v
                     a[0][1][2][3][4][5][6][7][8][9]         
                */  
```

### Subtracting an Integer from a Pointer

If `p` points to the array element `a[i]`, then `p-j` points to `a[i-j]`.

```C
int *p, a[10] = {0};

p = &a[8];      /*                            [p]
                                               v 
                     a[0][1][2][3][4][5][6][7][8][9]
                */  
q = p - 3;      /*                   [q]      [p]
                                      v        v
                     a[0][1][2][3][4][5][6][7][8][9]
                */  
p -= 6;         /*          [p]      [q]
                             v        v
                     a[0][1][2][3][4][5][6][7][8][9]         
                */  
```

### Subtracting One Pointer from Another

When one pointer is subtracted from another, the result is the distance (measured in array elements) between the pointers. Thus, if `p` points to `a[i]` and `q` points to `a[j]`, then `p-q` is equal to `i-j`.

```C
int *p, *q, a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

p = &a[5];      //      [q]         [p]
q = &a[1];      //       v           v
                //  a[0][1][2][3][4][5][6][7][8][9]

i = p - q;      //  i is 4
i = q - p;      //  i is -4
```

> Performing arithmetic on a pointer that doesn't point to an array element causes undefined behaviour. Furthermore, the effect of subtracting one pointer from another is undefined unless both point to elements of the *same* array.

### Comparing Pointers

We can compare pointers using the relational (<, <=, >, >=) and equality (==, !=) operators. These are only meaningful when both point to elements of the same array. The outcome depends on their relative positions within the array.

```C
p = &a[5];      // p <= q == 0
q = &a[1];      // p >= q == 1
```
 
### Pointers to Compound Literals

It's legal for a pointer to point to an element within an array created by a compound literal. A compound literal is a C99 feature that can be used to create an array with no name.

```C
int *p = (int []){3, 0, 3, 4, 1};
```

`p` points to the first element of a five-element array containing the integers 3, 0, 3, 4 and 1. Using a compound literal saves us the trouble of first declaring an array variable and then making `p` point to the first element of that array.

```C
int a[] = {3, 0, 3, 4, 1};
int *p = &a[0];
```

## 12.2 Using Pointers for Array Processing

Pointer arithmetic allows us to visit the elements of an array by repeatedly incrementing a pointer variable. 

In the following example, `p` initially points to `a[0]`, and is incremented every loop. The loop terminates when `p` steps past the last element of `a`.

```C
#define N 10
...
int a[N], sum, *p;
...
sum = 0;
for (p = &a[0]; p < &a[N]; p++)
    sum += *p;
```

The condition `p < &a[N]` in the `for` statement deserves special attention, as it may seem very strange to apply the address operator to `a[N]`, which actually can't exist.

Using `&a[N]` in this fashion is perfectly safe, since the loop doesn't actually ever attempt to read its value. The body of the loop will be executed with `p` equal to `&a[0]`, ... , `&a[N-1]`, but when `p` is equal to `&a[N]` the loop terminates.

> *We could just as easily have written this without pointers, using subscripting instead. The argument most often cited in support of pointer arithmetic is that it can save execution time, but that actually depends on the implementation. Some C compilers actually produce better code for loops that rely on subscripting.*

### Combining the `*` and `++` Operators



## 12.3 Using an Array Name as a Pointer

### Program: Reversing a Series of Numbers (Revisited)

### Array Arguments (Revisited)

### Using a Pointer as an Array Name

## 12.4 Pointers and Multidimensional Arrays

### Processing the Elements of a Multidimensional Array

### Processing the Rows of a Multidimensional Array

### Processing the Columns of a Multidimensional Array

### Using the Name of a Multidimensional Array as a Pointer

## 12.5 Pointers and Variable-Length Arrays (C99)

## Q&A: Pointers & Arrays

## Written Exercises: Pointers & Arrays
