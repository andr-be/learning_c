# Chapter 14: The Preprocessor

> There will always be things we say in our programs that in all known languages can only be said poorly.

In previous chapters, we covered `#define` and `#include` directives without going into detail; these instructions are handled by the **preprocessor** which is a piece of software unique to C/C++ that edits programs just prior to compilation.

The preprocessor is a powerful tool, but is often the cause of very difficult to find bugs and can be misued to create programs that are almost impossible to understand; it should always be used carefully and with moderation.

## 14.1 How the Preprocessor Works

The preprocessor is controlled by ***preprocessing directives:*** commands that begin with a `#` character. `#define` defines a ***macro**, a name that represents things like constants or frequently used expressions.

The preprocessor responds to a `#define` directive by storing the name of the macro together with its definition. When the macro is later used, the preprocessor 'expands' the macro, replacing it with the defined value.

The `#include` directive tells the preprocessor to open a particular file and "include" its contents as part of the file being compiled. The line `#include <stdio.h>` tells the preprocessor to open the file named `stdio.h` and brings its contents into the program.

```C
   C Program
       |
       V
 [PREPROCESSOR]
       |
       V
Modified C Program
       |
       v
  [COMPILER]
       |
       v
  Object code
```

The input to the preprocessor is a C program, possibly containing directives. The preprocessor executes these directives, removing them in the process. The output of the preprocessor is another C program -> an edited version of the original program, containing no directives.

The preprocessor's output goes directly into the compiler.

```C
// Converts a Fahrenheit temperature to Celsius

#include <stdio.h>

#define FREEZING_PT 32.0f
#define SCALE_FACTOR (5.0f / 9.0f)

int main(void)
{
    float fahrenheit, celsius;

    printf("Enter Fahrenheit temperature: ");
    scanf("%f", &fahrenheit);

    celsius = (fahrenheit - FREEZING_PT) * SCALE_FACTOR;

    printf("Celsius equivalent is: %.lf\n", celcius);

    return 0;
}
```

After preprocessing, the program will have the following apperance:

```C
 
 
[Lines brought in from stdio.h]
 
 
 
 
int main(void)
{
    float fahrenheit, celsius;

    printf("Enter Fahrenheit temperature: ");
    scanf("%f", &fahrenheit);

    celsius = (fahrenheit - 32.0f) * (5.0f / 9.0f);

    printf("Celsius equivalent is: %.lf\n", celcius);

    return 0;
}
```

The preprocessor responded to the `#include` directive by bringing in the contents of `stdio.h`, it also removed the `#define` directives and replaced `FREEZING_PT` and `SCALE_FACTOR` wherever they appeared later in the file. The preprocessor doesn't remove lines containing directives, it simply makes them empty. The preprocessor also replaces every comment with a single space character and some even remove unneccary white-spave including spaces and tabs at the beginning of indented lines.

While modern compilers often integrate the preprocessor natively, it's still useful to think about it as separate from the compiler. Most compilers actually provide a way to view the output of the preprocessor when a certain option is specified. (for GCC, use the `-E` flag).

WARNING: The preprocessor has only a limited knowledge of C, it's quite capable of creating illegal programs as it executes directives. Often, the original program looks fine, which makes errors harder to find. Therefore, in complex programs, sometimes it makes sense to debug the preprocessor output.

## 14.2 Preprocesing Directives

Most preprocessing directives fall into one of three categories:

- **Macro Definition** - The `#define` directive defines a macro: the `#undef` directive removes a macro definition. 

- **File Inclusion** - The `#include` directive causes the contents of a specified file to be included in a program.

- **Conditional Compilation** - The `#if`, `#ifdef`, `#ifndef`, `#elif`, `#else`, and `#endif` directives allow blocks of text to be either included in or excluded from a program, depending on conditions that can be tested by the preprocessor.

The remaining directives - `#error`, `#line`, and `#pragma` - are more specialised and therefore used less often. The only directive we won't discuss in this chapter is `#include`, because we'll be covering it in 15.2.

There are a few rules that apply to all directives:

- ***Directives always begin with the # symbol.**

- ***Any number of spaces and horizontal tab characters may separate the tokens in a directive.*** For example, `#    define     N     100` is legal.

- ***Directives always end at the first new-line character, unless explicitly continued.*** To continue a directive to the next line, we must end the current line with a \ character. For example, the following directive defines a macro that represents the capacity of a hard disk:

```C
#define DISK_CAPACITY (SIDES *              \
                       TRACKS_PER_SIDE *    \
                       SECTORS_PER_TRACK *  \
                       BYTES_PER_SECTOR)
```

- ***Directives can appear anywhere in a program.*** Although we usually put `#define` and `#include` directives at the beginning of a file, other directives are more likely to show up later, even in the middle of function definitions.
- ***Commends may appear on the same line as a directive.*** In fact, it's good practice to put a commend at the end of a macro definition to explain the meaning of the macro:

```C
#define FREEZING_PT 32.0f   /* freezing point of water */
```

## 14.3 Macro Definitions

The macros we've been using since Chapter 2 are known as *simple* macros, because they have no parameters. The preprocessor also supports *parameterised* macros. We'll look first at simple macros, then at parameterised macros.

### Simple Macros

```C
#define  identifier  replacement-list
```

*replacement-list* is any sequence of ***preprocessing tokens***, which are similar to the tokens discussed in Section 2.8. A macros replacement list may include ifentifiers, keywords, numerical constants, character constants, string literals, operators, and punctuation.

When it encounters a macro definition, the preprocessor makes a note that *identifier* represents *replacement-list*; wherever *identifier* appears later in the file, the preprocessor substitutes *replacement-list*.

> WARNING:
> Don't put any extra symbols in a macro definition - they'll become part of the replacement list. Putting the = symbol in a macro definition is a common error:
>
> ```C
> #define N = 100   // WRONG!
> ...
> int a[N];         // becomes int a[= 100];
> ```
>
> In this example, we've (incorrectly) defined N to be a pair of tokens (= and 100). Ending a macro definition with a semicolon is another popular mistake:
>
> ```C
> #define N 100;    // WRONG!
> ...
> int a[N];         // becomes int a[100;];
> ```
>
> Here N is defined to be tokens 100 and ;.
> The compiler will detect most errors caused by extra symbols in a macro definition. Unfortunately, it will flag each use of the macro as incorrect, rather than identifying the actual culprit: the macro's definition.

Simple macros are primarily used for defining what Kernighan and Ritchie call "manifest constants". Using macros, we can give names to numeric, character and string values:

```C
#define STR_LEN 80
#define TRUE    1
#define FALSE   0
#define PI      3.14159
#define CR      '\r'
#define EOS     '\0'
#define MEM_ERR "Error: not enough memory"
```

Using `#define` to create names for constants has several significant advantages:

- ***It makes programs easier to read.*** The name of the macro, if well chosen, helps the reader understand the meaning of the constant. The alternative is a program full of "magic numbers" that can easily mystify the reader.

- ***It makes programs easier to modify.*** We can change the value of a constant throughout a program by modifying a single macro definition. "Hard-coded" constants are more difficult to change, especially since they sometimes appear in a slightly altered form. (e.g. a program with an array of length `100` may have a loop that goes from `0` to `99`. If we merely try to locate occurences of `100` in the program, we'll miss the `99`.)

- ***It helps avoid inconsistencies and typographical errors.*** If a numerical constant like `3.14159` appears many times in a program, chances are it will occasionally be written `3.1416` or `3.14195` by accident.

Although simple macros are most often used to define names for constants, they do have other applications.

- ***Making minor changes to the syntax of C.*** We can, in effect, alter the syntax of C by defining macros that serve as alternate names for C's symbols. e.g. programmers who prefer Pascal's `begin` and `end` to C's `{` and `}` can define the following macros: `#define BEGIN   {` and 
`#define END     }`. We could go so far as to invent our own language. For example, we might create a `LOOP` statement that establishes an infinite loop: `#define LOOP for (;;)` Changing the syntax of C usually isn't a good idea, since it can make programs harder for others to understand.

- ***Renaming types.*** In section 5.2, we created a Boolean type by renaming `int`: `#define BOOL int`. Although some programmers use macros for this purpose, type definitions are a superior way to define type names.

- ***Controlling conditional compilation.*** Macros play an important tole in controlling conditional compilation, as we'll see in Section 14.4. For example, the presence of the following line in a program might indicate that it's about to be compiled in "debugging mode" with extra statements included to produce debug output. `#define DEBUG`. Incidentally, it's legal for a macro's replacement list to be empty, as this example shows.

When macros are used a constants, C programmers customarily capitalise all letters in their names. However, there's no consensus as to how to capitalise macros used for other purposes. Since macros (especially parameterised macros) can be a source of bugs, some programmers like to draw attention to them by using all upper-case letters in their names. Others prefer lower-case names, following K&R style.

### Parameterised Macros

The definition of a ***parameterised macro*** (also known as a function-like macro) has the form:

```C
#define  identifier( x1 , x2 , ... , xn )  replacement-list
```

where `x1, x2, ..., xn` are identifiers (the macro's parameters). The parameters may appear as many times as desired in the replacement list.

> There must be no space between the macro name and the left parenthesis. If space is left, the preprocessor will assume that we're defining a simple macro, it will treat `(x1, x2, ..., x3)` as part of the replacement list.

When the preprocessor encounters the definition of a parameterised macro, it stores the definition away for later use. Wherever a macro invocation of the form `identifier(y1, y2, ..., y3)` appears later in the program, the preprocessor replaces it with a replacement-list, substituting `y1` for `x1`, `y2` for `x2` and so forth.

```C
define MAX(x,y)     ((x)>(y)?(x):(y))
#define IS_EVEN(n)  ((n)%2==0)
```

There may appear to be too many parentheses, but there's a reason for this we'll expand on later. Suppose we invoke these macros in the following way:

```C
i = MAX(j+k, m-n);
if (IS_EVEN(i)) i++;
```

The processor will replace these lines with:

```C
i = ((j+k)>(m-n)?(j+k):(m-n));
if (((i)%2==0)) i++;
```

As this example shows, parameterised macros often serve as simple functions. MAX behaves like a function that computes the larger of two values. IS_EVEN behaves like a function that returns 1 if its argument is an even number and 0 otherwise. 


```C
#define TOUPPER(c) ('a'<=(c)&&(C)<='z'?(c)-'a'+'A':(c))
```

This macro tests whether the character c is between 'a' and 'z'. If so, it produces the upper-case version of c by subtracting 'a' and adding 'A'. If not, it leaves c unchanged. (`ctype.h` provides a similar function named `toupper` that's more portable).

A parameterised macro may have an empty parameter list:

```C
#define getchar() getc(stdin)
```

The empty parameter list isn't really needed, but it makes `getchar` resemble a function; using a parameterised macro instead of a true function has a couple of advantages:

- ***The program may be slightly faster.*** A function call usually requires some overhead during program execution - context information must be saved, arguments copied, etc. A macro invocation requires no runtime overhead. However, C99's inline functions provide a way to avoid this overhead without the use of macros.

- ***Macros are "generic".*** Macro parameters, unlike function parameters, have no particular types. As a result, a macro can accept arguments of any type, provided that the resulting program - after preprocessing - is valid. e.g. we could use the MAX macro to find the larger of two values of type `int`, `long`, `float`, `double` and so forth.

There are also some disadvantages:

- ***The compiled code will often be larger***. Each macro invocation causes the insertion of the macro's replacement list, increasing the size of the souce program. This effect is compounded when macro invocations are nested:

```C
// original source code:
n = MAX(i, MAX(j, k));

// after pre-processing:
n = ((i)>(((j)>(k)?(j):(k)))?(i):(((j)>(k)?(j):(k))));
```

- ***Arguments aren't type-checked.*** When a function is called, the compiler checks each argument to see if it has the appropriate type. If not, either the argument is converted to the proper type or the compiler produces an error message. Macro arguments aren't checked by the preprocessor, nor are they converted.

- ***It's not possible to have a pointer to a macro.*** C allows pointers to functions, a concept that's quite useful in certain situations. Macros are removed during preprocessing, so there's no corresponding notion of "pointer to a macro".

- ***A macro may evaluate its arguments more than once.*** A function evaluates its arguments only once; a macro may evaluate its arguments two or more times. Consider the unexpected behaviour that can result from an argument with side effects:

```C
// original source code:
n = MAX(i++, j);

// after pre-processing
n = ((i++)>(j)?(i++):(j));
```

In this example, if `i` is larger than `j`, `i` will be incorrectly incremented twice and `n` will be assigned an unexpected value. These bugs are difficult to identify, so care should always be taken not to supply macros arguments that have side effects.

Parameterised macros are good for more than just simulating functions; they're often used as patterns for segments of code that we find ourselves repeating. Suppose we grow tired of writing `printf("%d\n", n)` every time we want to print an integer. We could instead define a macro:

```C
#define PRINT_INT(n) printf("%d\n", n)
```

### The # Operator

Macro definitions may contain two special operators, `#`and `##`; neither is recognised by the compiler and is instead handled by the preprocessor.

The `#` operator converts a macro argument into a string literal; it can appear only int he replacement list of a parameterised macro. (The operation performed by `#` is known as "stringization").

Suppose that we decide to use the `PRINT_INT` macro during debugging as a convenient way of printing the values of integer variables and expressions. The `#` operator makes it possible for `PRINT_INT` to label each value that it prints:

```C
#define PRINT_INT(n) printf(#n " = %d\n", n)
```

The `#` operator in front of `n` instructs the preprocessor to create a string literal from `PRINT_INT`s argument. Therefore `PRINT_INT(i/j);` will become `printf("i/j = %d\n", i/j);`. When the program is executed, `printf` will display both the expression `i/j` and its value. If `i` is 11 and `j` is 2, the output will be `i/j = 5`.

### The ## Operator

The ## operator can "paste" two tokens (identifers, for example) together to form a single token. There aren't many good ways to use this operator, but one example is in the form of generic functions.

Suppose we wanted to write a `MAX` function for different types of integers and floats, but we didn't want to write multiple identical functions. We could instead write a macro that expands into the definition of a max function.

Unfortunately, if we tried to naively create one, we would have an issue that both functions would be called the same thing, which isn't allowed in C. Instead, we'll use the ## operator to crate a different name for each version of max:

```C
#define GENERIC_MAX(type)       \
type type##_max(type x, type y) \
{                               \
    return x > y ? x : y;       \
}
```

Notice how `type` is joined with `_max` to form the name of the function. Suppose that we hapen to need a max function that works with `float` values;

```C
GENERIC_MAX(float)

// the preprocessor expands this line into the following

float float_max(float x, float y) { return x > y ? x : y; }
```

### General Properties of Macros

- ***A macro's replacement list may contain invocations of other macros.*** For example, we could define the macro `TWO_PI` in terms of another macro called `PI`:

```C
#define PI          3.14159
#define TWO_PI      (2 * PI)
#define PI_OVER_2   (PI / 2)
```

When it encounters `TWO_PI` later in the program, the preprocessor replaces it by `(2 * PI)`. It then rescans the replacement list to see if it contains invocations of other macros, and will rescan the replacement list as many time as necessary to eliminate all macro names.

- ***The preprocessor replaces only entire tokens, not portions of tokens.*** As a result, the preprocessor ignores macro names that are embedded in identifiers, character constants and string literals:

```C
#define SIZE 256

int BUFFER_SIZE;

if (BUFFER_SIZE > SIZE)
    puts("Error: SIZE exceeded!");

// after preprocessing, this will look like:

int BUFFER_SIZE;

if (BUFFER_SIZE > 256)
    puts("Error: SIZE exceeded!");
```

The identifier `BUFFER_SIZE` and the string `"Error: SIZE exceeded"` weren't affected by preprocessing, even though both contain the word SIZE.

- ***A macro definition normally remains in effect until the end of the file in which it appears.*** Since macros are handled by the preprocessor, they don't obey normal scope rules. A macro defined inside the body of a function isn't local to that function' it remains defined until the end of the file.

- ***A macro may not be defined twice unless the new definition is identical to the old one.*** Differences in spacing are allowed, but the tokens in the macro's replacement list (and the parameters) must be the same.

- ***Macros may be "undefined" by the `#undef` directive.*** It is used in the form:

```C
#define N 50
#undef N        // removes the current definition of the macro N.
```

One use of `#undef` is to remove the existing definition of a macro so that it can be given a new definition.

### Parentheses in Macro Definitions

Is it necessary to have so many parentheses in our macro definitions? The answer is an emphatic **"YES"**; if we use fewer brackets the macros will sometimes give unexpected and undesirable results. There are two rules to follow when deciding:

1. If the macro's replacement list contains an operator, always enclose the replacement list in parentheses.

2. If the macro has parameters, put parentheses around each parameter every time it appears in the replacement list.

```C
#define TWO_PI 2 * 3.14159
// needs parentheses around the replacement list!

conversion_factor = 360 / TWO_PI;
// becomes
conversion_factor = 360 / 2 * 3.14159;
// == 180 * 3.14159 (565.49) and not 360 / 6.28318 (57.30)
```

Failing to adhere to these rules can lead to situations like the above, where the order of operations C adheres to means that the division will happen before the multiplication, causing us to calculate the wrong value for the conversion factor.

Putting parentheses around the replacement list isn't enough if the macro has parameters: each occurrence of a parameter needs parentheses as well. For example:

```C
#define SCALE(x) (x * 10)   
// needs parens around x!
j = SCALE(i + 1);
// becomes
j = (i + 1 * 10)
// multiplication takes precedence over addition:
j = i + 10
// this should be (i + 1) * 10!
```

> A shortage of parentheses in a macro definition can cause some of C's most frustrating errors. The program will usually compile and the macro will appear to work, failing only at the least convenient times.

### Creating Longer Macros

The comma operator can allow us to create moresophisticated macros by allowing us to make the replacement list a series of expressions:

```C
#define ECHO(s) (gets(s), puts(s))

ECHO(str); // becomes: (gets(str), puts(str));
```

Instead of using the comma operator, we could have enclosed the calls in braces to form a compound statement; unfortunately this method doesn't work as well.

```C
#define ECHO(s) { gets(s); puts(s); }

if (echo_flag)
    ECHO(str);
else
    gets(str);

// replacing ECHO gets us the following:
if (echo_flag)
    { gets(str); puts(str); };
else
    gets(str);
```

The compiler treats the first two lines as a complete `if` statement. It treats the semicolon that follows as a null statement and produces an error message for the `else` clause, since it doesn't belong to any `if`.

The comma operator solves this problem for `ECHO`, but not for all macros. Suppose that a macro needs to contain a number of *statements*, not just a series of *expressions*. The comma operator is of no help; it can glue together expressions but not statements. The solution is to wrap the statements in a `do` loop whose condition is false:

```C
do { ... } while (0)
// will only execute once!

#define ECHO(s)         \
        do {            \
            gets(s);    \
            puts(s);    \
        } while (0) 
```

When `ECHO` is used, it must be followed by a semicolon, which completes the `do` statement.

```C
ECHO(str);
// becomes: do { gets(str); puts(str); } while (0);
```

### Predefined Macros

