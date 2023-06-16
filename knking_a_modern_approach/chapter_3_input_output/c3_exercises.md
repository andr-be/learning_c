# Chapter 3: Input/Output - Written Exercises
```C
// andr-be 06/2023
```

### 1. What output do the following calls of `printf` produce?
**a)**  `printf("%6d,%4d", 86, 1040);`
    
```C
|    86,1040|
```

**b)**  `printf("%12.5e", 30.253);`
```C
|     30.25300|
```

**c)**  `printf("%.4f", 83.162);`
```C
|83.1620|
```

**d)**  `printf("%-6.2g", .0000009979);`
```C
|    0.00|     
```

### 2. Write calls of `printf` that display a `float` variable `x` in the following formats:
**a)** Exponential notation; left-justified in a field of size 8, one digit after the decimal point.
```C
printf("%-8.1e", x);
```

**b)** Exponential notation; right-justified in a field of size 10; six digits after the decimal point.
```C
printf("%10.6e", x);
```

**c)** Fixed decimal notation: left-justified in a field of size 8; three digits after the decimal point.
```C
printf("%-8.3f", x);
```

**d)** Fixed decimal notation; right-justified in a field of size 6; no digits after the decimal point.
```C
printf("%6.0f", x);
```

### 3. For each of the following pairs of `scanf` format strings, indicate whether or not the two strings are equivalent. 
If they're not, show how they can be distinguished. 

**a)** `"%d"` | `" %d"`

    I think these aren't equivalent; if the space means it'll ignore whitespace then I think the first example would fail to parse anything that started with whitespace?

**b)** `"%d-%d-%d"` | `"%d - %d - %d"`

    These aren't equivalent. If the first example hits a whitespace character it will immediately halt. The second example can deal with whitespace.

**c)** `"%f"` | `"%f "`

    These are equivalent. If it scans a float and *then* whitespace it's irrelevant because it will have already returned.

**d)** `"%f,%f"` | `"%f, %f"`

    Not equivalent; first can't handle whitespace but the second example can.

### *4. Suppose that we call scanf as follows:
```C
scanf("%d%f%d", &i, &x, &j);
```
If the user enters `10.3 5 6`; what will be the values of `x`, `i`, and `y` after the call? (Assume that `i` and `j` are `int` variables and `x` is a `float` variable.)
    
    i = 10
    x = 0.300000
    j = 5 

### *5. Suppose that we call scanf as follows:
```C
scanf("%f%d%f", &x, &i, &y);
```
If the user enters `12.3 45.6 789` what will be the values of `x`, `i` and `y` after the call? (Assume that `x` and `y` are `float` variables and `i` is an `int` variable.)

    x = 12.300000
    i = 45
    j = 0.600000

### 6. Show how to modify the addfrac.c program from section 3.2 so that the user is allowed to enter fractions that contain spaces before and after each / character.

    I actually ended up modifying the entire program to give it the capability to do all sorts of fraction maths. 
    
    It's in `/learning_c/personal_programs/fraction_calculator.c`

