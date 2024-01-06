# Chapter 15: Writing Large Programs

> Around computers it is difficult to find the correct unit of time to measure progress. Some cathedrals took a century to complete. Can you imagine the grandeur and scope of a program that would take as long?

Most C programs are not small enough to be put into a single file; multi-file programs are the rule rather than the exception; a typical program consists of several source files and usually some header files as well. Source files contain definitions of functions and external variables; header files contain information to be shared among source files.

## 15.1 Source Files

A program may be divided among any number of **source files**. By convention, source files have the extension `.c`. Each source file contains part of the program, primarily definitions of functions and variables. One source file must contain a function named `main`, which serves as the starting point for execution.

Suppose that we want to write a simple calculator program that evaluates integer expressions entered in Reverse Polish notation (RPN), and want the program to print the value.

To evaluate an RPN expression, we read the operands and operators one by one, using a stack to keep track of intermediate results. If the program reads a number, we'll have itpush the number onto the stack. If it reads and operator, we'll have it pop two numbers from the stack, perform the operation, and then push the result back onto the stack.

`30 5 - 7 *`

1. Push 30 onto the stack.
2. Push 5 onto the stack.
3. Pop the top two numbers from the stack, subtract 5 from 30, giving 25, and then push the result back onto the stack.
4. Push 7 onto the stack.
5. Pop the top two numbers from the stack, multiply them, and then push the result back onto the stack.

After these steps, the stack will contain the value of the expression, 175.

Turning this strategy into a program isn't hard; the main function will contain a loop that performs the following actions:

- Read a "token" (a number or an operator)
- If the token is a number, push it onto the stack
- If the token is an operator, pop its operands from the stack, perform the operation and then push the result back onto the stack

When dividing a program like this into files, it makes sense to put related functions and variables into the same file. 

The function that reads tokens could go into one source file - `token.c`, along with any functions that have to do with tokens. Stack related functions such as `push`, `pop`, `make_empty`, `is_empty` and `is_full` could go into a different file, `stack.c`. The variables that represent the stack would also go into `stack.c`. The main function would go into yet another file, `calc.c`.

Splitting a program into multiple source files has significant advantages:

- Grouping related functions and variables into a single file helps clarify the structure of the program.
- Each source file can be compiled separately - a great time saver if the program is large and must be changed frequently.
- Functions are more easily reused in other programs when grouped in separate source files. In our example, splutting off `stack.c` and `token.c` from the `main` function makes it simple to reuse the stack functions and token functions in the future.

## 15.2 Header Files

How can a function in one file call a function that's defined in another file? How can a function access an external variable in another file? How can two files share the same macro definition or type definition? The answer lies in the `#include` directive, which makes it possible to share information; function prototypes, macro definitions, type definitions, etc. among any number of source files.

The `#include` directive tells the preprocessor to open a specified file and insert its contents into the current file. Therefore, if we want serveral source files to have access to the same information, we'll put it in a file and use `#include` to bring the file's contents into each of the source files.

Files that are included in this fashion are called ***header files*** (or sometimes 'include files'). By convention, header files have the extension `.h`. The C standard uses the term "source file" to refer to files written by the programmer, including both `.c` and `.h` files, but this book will use "source file" to refer to `.c` files only.

### The `#include` Directive

`#include` has two primary forms; 

- `#include <filename>` used for header files that belong to C's own library. Search the firectory in which system header files reside. (On UNIX, this is usually in `/usr/include`)

- `#include "filename"` used for all other header files, including any we write. Searches the current directory, and then searches the directories in which  system header files reside.

> Don't use brackets when including header files that you have written:
>
> ```C
> #include <myheader.h>     // wrong!
> ```
>
> The preprocessor will probably look for `myheader.h` where the system header files are kept (and of course,  won't find it).

The file name in an `#include` directive may include information that helps locate the file, such as a directory path or drive specifier:

```C
#include "c:\cprogs\utils.h"    // Windows path
#include "/cprogs/utils.h"      // UNIX path
```

Although the quotation marks in the `#include` directive make file names look like string literals, the preprocessor doesn't treat them that way. This is useful, because `\c` and `\u` appear in the windows file, which would be treated as escape sequences in a string literal. 

*For portability reasons, it's often best not to include path or drive information in `#include` directives, because it makes it difficult to compile a program when it's transported to another machine or OS.*

The following Windows `#include` directives specify drive and/or path information that may not always be valid:

```C
#include "d:utils.h"
#include "\cprogs\include\utils.h"
#include "d:\cprogs\include\utils.h"
```

Instead, we should use relative, rather than absolute `#include` referencing.

```C
#include "utils.h"
#include "..\include\utils.h"
```

`#include` has a third form that's used less often than the other two; `#include  tokens` where tokens is any sequence of preprocessing tokens. The preprocessor will scan the tokens and replace any macros that it finds. The advantage of the third kind of `#include` is that the file name can be defined by a macro rather than being "hard-coded" into the directive itself:

```C
#if defined(IA32)
    #define CPU_FILE "ia32.h"
#elif defined(IA64)
    #define CPU_FILE "ia64.h"
#elif defined(AMD64)
    #define CPU_FILE "amd64.h"
#endif

#include CPU_FILE
```

### Sharing Macro Definitions and Type Definitions

Most large programs contain macro definitions and type definitions that need to be shared by several source files. These definitions should go into header files.

Suppose that we're writing a program that uses macros named `BOOL`, `TRUE` and `FALSE`. (We shouldn't need to, because we have the `<stdbool.h>` header in C99.) Instead of repeating the definitions of these macros in each source file that needs them, it makes more sense to put the definition in a header file with a name like `boolean.h`.

```C
// boolean.h
#define BOOL int
#define TRUE 1
#define FALSE 0
```

Any source file that requires these macros will simply contain the line `#include "boolean.h`.

Type definitions are also common in header files; instead of defining a `BOOL` macro, we might use `typedef` to create a `Bool` type. If we do, the `boolean.h` file will look different:

```C
#define TRUE 1
#define FALSE 0
typedef int Bool;
```

Defining macros and types in header files has some clear advantages:

- First, we save time by not having to copy the definitions into the source files where they're needed.
- Secondly, the program becomes much easier to modify; changing the definition of a macro or type requires a that we edit only a single header file - we won't have to modify the many source files in which the macro or type is used.
- Thirdly, we don't have to worry about inconsistencies caused by source files containing different definitions of the same macro or type.

### Sharing Function Prototypes

If we have a source file that contains a call of function `f()` that's defined in another file, `foo.c`, calling it without declaring it first is risky. Without a prototype to rely on, the compiler is forced to assume that `f`s return type is `int` and that the number of parameters matches the number of arguments in the call to `f`. The compiler's assumptions may well be wrong, but it has no way to check them, since it compiles only one file at a time.

The inherent problems meant that C99 probibits calling a function for which the compiler has not yet seen a declaration or definition.

> When calling a function `f` that's defined in another file, always make sure that the compiler has seen a prototype for `f` prior to the call.

Suppose that a function is called in fifty different source files. How can we ensure that `f`s prototypes are the same in all the files? How can we guarantee that they match the definition of `f` in `foo.c`? If `f` should change later, how can we find all the files where it's used?

The solution? Put `f`'s prototypes in a header file, and then include the header file in all the places that `f` is called. Since `f` is defined in `foo.c`, we should call the header file `foo.h`. In addition to including `foo.h` in the source files where `f` is called, we'll also need to include it in `foo.c`.

> Always includethe header file declaring a function `f` in the source file that contains `f`'s definition. Failure to do so can cause hard-to-find bugs, since calls of `f` elsewhere in the program may not match `f`'s definition.

If `foo.c` contains other functions, most of them should be declared in the same header file as `f`. Functions that are intended for use only within `foo.c` shouldn't be declared in a header file as to do so would be misleading.

For the RPN calculator we looked at in Section 15.1, the `stack.c` file will contain definitions of the `make_empty`, `is_empty`, `is_full`, `push` and `pop` functions. The following prototypes for these functions should go in the `stack.h` header file:

```C
// stack.h

void make_empty(void);
int is_empty(void);
int is_full(void);
void push(int i);
int pop(void);
```

```C
// calc.c

#include "stack.h"
int main(void)
{
    make_empty();
    ...
}
```

```C
// stack.c

#include "stack.h"

int contents[100];
int top = 0;

void make_empty(void)
{...}
int is_empty(void)
{...}
int is_full(void)
{...}
void push(int i)
{...}
int pop(void)
{...}
```

### Sharing Variable Declarations

External variables can be shared among files in the same way functions are. TO share a function, we put its definition in one source file, then put declarations in other files that need to call the function, and sharing an external variable is done in much the same way.

First, we need to distinguish between a variable's declaration and its definition. 

```C
int i;            // declares i and defines it as well

extern int i;     // declares i without defining it

extern int a[];   // declares array a without a specified length
```

In the first example, `i` is considered 'defined' because the compiler has set aside some space for it. To declare `i` without doing this, we need to use the `extern` keyword at the start of the declaration; `extern` informs the compiler that `i` is defined elsewhere in the program (most likely in a different source file), so there's no need to allocate space for it.

`extern` works with variables of all types and when we use it in the declaration of an array, we can omit the length of the array because there's no need to know the array's length if you're not allocating it any memory.

To share a variable `i` among several source files, we fist put a definition of `i` in one file. If `i` needs to be initialised, the initialiser will also go here. When the file is compiled, the compiler will allocate storage for `i`. The other files will contain declarations of `i`.

By declaring `i` in each file, it becomes possible to access and/or modify `i` within those files and because we've used `extern`, the compiler doesn't allocate additional storage for `i` each time one of the files is compiled.

When a variable is shared across files, we'll face a challenge ensuring that all declarations of the variable agree with the definition of the variable. For example, one file may contain the definition `int variable;` while another file contains the declaration `extern long variable;`, which can cause the program to behave very unpredictably. 

Although sharing variables among files is a long-standing practice in C, it has significant disadvantages; we'll cover these in Section 19.2 and learn how to design programs that don't require shared variables.

### Nested Includes

A header file may also contain `#include` directives. Consider `stack.h` again:

```C
int is_empty(void);
int is_full(void);
```

As these functions can only return 1 or 0, it's a good idea to declare their return type to be `bool` instead of `int`, by including `stdbool.h`:


```C
#include <stdbool.h>

bool is_empty(void);
bool is_full(void);
```

Traditionally, C programmers used to shun nested include statements (as early versions of C didn't support them) but with their relative popularity in C++ there is a gradual decline in this convention. 

### Protecting Header Files
If a source file includesa the same header twice, compilation errors may result. This is common when header files include other header files. 
Suppose that `file1.h` includes `file3.h`. `file2.h` also includes `file3.h` and `prog.c` includes both `file1.h` and `file2.h`. When `prog.c` is compiled, `file3.h` will be compiled twice.

Including the same header file twice doesn't always cause a compilation error; if the file contains only macro definitions, function prototypes and/or variable declarations, there won't be any difficulty. If the file contains a type defintiion, that will throw an error.

Just to be safe, it's a good idea to protect all header files against multiple inclusion; this might also save us some time by avoiding unnecessary recompilation of the same header file.

```C
#ifndef BOOLEAN_H
#define BOOLEAN_H

#define TRUE 1
#define FALSE 0
typedef int Bool;

#endif
```

When this file is included the first time, the BOOLEAN_H macro won't be defined, so the preprocessor will allow the lines between `#ifndef` and `#endif`. The name of the macro doesn't matter, but making it resemble the name of the header file is good practice.

### `#error`Directives in Header Files

`#error` directives are often put in header files to check for conditions under which the header shouldn't be included e.g. it uses features that didn't exist prior to C89. To prevent this header being used with older, nonstandard compilers, we could write:

```C
#ifndef __STDC__
#error This header requires a Standard C compiler!
#endif
```

## Dividing a Program into Files

We'll now use what we know about header files and source files to develop a simple technique for dividing a program into files. Initially we'll concentrate on functions, but the same principles apply to external variables as well. We're going to be assuming the program has already been designed i.e. we've decided what functions we need and how to arrange them into groups.

Each set of functions will go into a separate source file (e.g. `foo.c`). We'll also create a header file with the same name as the source file, but with a `.h` extension. Inside `foo.h` we'll place prototypes for all functions defined in `foo.c`. 

NB: Functions that are designed for use only within `foo.c` need not and should not be declared in `foo.h`. We'll include `foo.h` in every source file that needs to call a function defined in `foo.c`. Also, we'll include `foo.h` in `foo.c` so the compiler can check that the function prototypes are consistent with their definitions. 

The `main` function will go into its own file whose name matches the name of the program. If we wanted the program to be known as `bar`, main should be in the file `bar.c`. It's possible that there are other functions in the same file as `main`, so long as they're not called from other files in the program.

### Text Formatting

To illustrate the principles outlined above, let's apply it to a small text formatting program named `justify`. As input, we'll use a file named `quote` that contains the following (poorly formatted) quotation from a book by Dennis Ritchie:

```quote.txt
  C     is quirky,  flawed,   and  an 
enormous   success.       Although accidents of    history
surely  helped,   it evidently      satisfied   a   need
    for  a   system   implementation   language     efficient
enough   to displace                assembly    language,
  yet sufficiently   abstract    and fluent   to describe
 algorithms   and      interactions      in a    wide   variety
of    environments.
          --     Dennis     M.        Ritchie
```

To run the program from a UNIX or Windows prompt, we'd enter the command 

```shell
justify <quote
```

(The < unary symbol tells the OS to read input from the file quote and not the keyboard.) When iven the `quote` file as input, the `justify` program will produce the following output:

```output
C is quirky, flawed, and an enormous success. Although accidents of history
surely helped, it evidently satisfied a need for a system implementation language 
efficient enough to displace assembly language, yet sufficiently abstract and 
fluent to describe algorithms and interactions in a wide variety of environments.
  -- Dennis M. Ritchie
```

The output of `justify` will normally just appear on the screen, but we can save it in a file using *output redirection*. 

```shell
justify <quote >newquote
```

The output of `justify` will go to the file `newquote`. 

In general, `justify`'s output should be identical to its input, except that extra spaces and blank lines are deleted and the lines are filled and justified. "Filling" a line just means adding words until one more word would cause the line to overflow. "Justifying" a line means adding extra spaces between words so that each line has exactly the same length (60 characters). Justification mustbe done so that the space between words in a line is as equal as possible. The last line of the output won't be justified. 

We'll assume that no word is longer than 20 characters, and that a punctuation mark counts as part of the word to which it is adjacent. If the program encounters a longer word, it must ifnore all charactes after thew first 20, replacing them with a single asterisk. e.g:

```
antidisestablishmentarianism
```

would become

```
antidisestablishment*
```

With that in mind, it's time to start thinking about the design of the program. We'll start by observing that the program can't write the words one by one as they're read, it will instead have to store them in a line buffer until there are enough to fill a line. 

```C
for (;;) 
{
    read word;
    if (can't read word) 
    {
        write contents of line buffer without justification;
        terminate program;
    }
    if (word doesn't fit in line buffer)
    {
        write contents of line buffer with justification;
        clear line buffer;
    }
    add word to line buffer;
    }
```

Since we'll need functions that deal with words and functions that deal with the line buffer, we should split the program into three source files, putting all functions related to words in one file (word.c) and all functions related to the line buffer in another file (line.c). A third file (justify.c) will contain the `main` functions.

In addition to these files, we'll need two header files, word.h and line.g. The word.h file will contain prortypes for the functions in word.c: line.h will play a similar role for line.c.

By examining the main loop, we see that the only word-related function that we'll need is a `read_word` function. If `read_word` can't read a word because it's reached the end of the input file, we'll have it signal the main loop by pretending to read an "empty" word. Consequently, `word.h` is a small file.

```C
// word.h
#ifndef WORD_H
#define WORD_H

// read_word
// reads the next word from the input and stores it in word.
// makes word empty if no word could be read because of end-of-file
// truncates the word if its length exceeds len.

void read_word(char *word, int len);

#endif
```

Notice how the `WORD_H` macro protects `word.h` from being included more than once. Although `word.h` doesn't really need it, it's good practice to protect all header files like this.

The `line.h` file will be longer than `word.h`. Our outline of the main loop reveals the need for functions that perform the following operations. 

- write contents of line buffer without justification
- determine how many characters are left in line buffer
- write contents of line buffer with justification
- clear line buffer
- add word to line buffer

We'll call these functions `flush_line`, `space_remaining`, `write_line`, `clear_line`, and `add_word`. Here's what the `line.h` header file will look like:

```C
// line.h
#ifndef LINE_H
#define LINE_H

// clear line
// clears the current line
void clear_line(void);

// add_word
// adds word to the end of the current line. 
// if this is not the first word on the line, puts one space before word.
void add_word(const char *word); 

// space_remaining
// returns the current number of characters left in the current line
int space_remaining(void);

// write_line
// writes the current line with justification
void write_line(void);

// flush_line
// writes the current line without justification; does nothing if line is empty
void flush_line(void);

#endif
```

Before we write the `word.c` and `line.c` files, we can use the functions declared in `word.h` and `line.h` to write `justify.c`, the main program. Writing this file is mostly a matter of translating our original loop design into C.

```C
// justify.c
/*
    formats a file of text
*/

#include <string.h>
#include "line.h"
#include "word.h"

#define MAX_WORD_LEN 20

int main(void)
{
    char word[MAX_WORD_LEN + 1];
    int word_len;

    clear_line();

    for (;;)
    {
        read_word(word, MAX_WORD_LEN + 1);
        word_len = strlen(word);
        
        if (word_len == 0)
        {
            flush_line();
            return 0;
        }
        
        if (word_len > MAX_WORD_LEN)
        {
            word[MAX_WORD_LEN] = '*';
        }
        
        if (word_len + 1 > space_remaining())
        {
            write_line();
            clear_line();
        }
        
        add_word(word);
    }
}
```

Including both `line.h` and `word.h` gives the compiler access to the function prototypes in both files as it compiles `justify.c`.

`main` uses a trick to handle words that exceed 20 characters. When it calls `read_word`, `main` telsl it to truncate any word that exeeds 21 characters. After `read_word` returns, `main` checks whether word contains a string that's longer than 20 characters. If so, the word that was read must have been at least 21 characters long, so main replaces the word's 21st character with an asterisk.

Now it's time to write `word.c`. Although the `word.h` header file has a prototype for only one function; `read_word`, this gives us space to put additional functions into `word.c` if we need to. As it turns out, `read_word` is much easier to write if we add a small "helper" function, `read_char`, which we'll assign the task of reading a single character and if its a newline or tab, converting it into a space. Having `read_word` will call `read_char` instead of `getchar` solves the problem of treating new_line characters and tabs as spaces.

```C
// word.c

#include <stdio.h>
#include "word.h"

int read_char(void)
{
    int ch = getchar();

    if (ch == '\n' || ch == '\t')
    {
        return ' ';
    }

    return ch;
}

void read_word(char *word, in len)
{
    int ch, pos = 0;

    while ((ch = read_char()) == ' ')
        ;

    while (ch != ' ' && ch != EOF)
    {
        if (pos < len)
        {
            word[pos++] = ch;
        }

        ch = read_char();
    }
    word[pos] = '\0';
}
```

A couple of comments are in order regarding the use of `getchar` in the `read_char` function. First, `getchar` returns an `int` value instead of a `char` value: that's why the variable `ch` in `read_char` is declared to have type `int` and why the return value of `read_char` is `int`. Also `getchar` returns the value EOF when its unable to continue reading (usually because it has reached the end of the input file).

`read_word` consists of two loops. The first loop skips over spaces, stopping at the first nonblank character. (EOF isn't a blank, so the loop stops if it reaches the end of the input file.) The second loop lreads characters until encountering a space or EOF. The body of the loop stores the cahracters in `word` until reaching the `len` limit. After that, the loop continues reading characters but doesn't store them. The final statement in `read_word` ends the word with a null character, thereby making it a string. If `read_word` encounters `EOF` before finding a nonblank character, `pos` will be 0 at the end, making `word` an empty line.

The only file left to create is `line.c` which supplies definitions of the functions declared in the `line.h` file. `line.c` will also need variables to keep track of the state of the line buffer. One vatriable, `line`, will store the characters in the current line. Strictly speaking `line` is the only variable we need. For speed and convenience, we'll also use `line_len` and `num_word`.

```C
// line.c

#include <stdio.h>
#include <string.h>
#include "line.h"

#define MAX_LINE_LEN 60

char line[MAX_LINE_LEN + 1];
int line_len = 0;
int num_words = 0;

void clear_line(void)
{
    line[0] = '\0';
    line_len = 0;
    num_words = 0;
}

void add_word(const char *word)
{
    if (num_words > 0)
    {
        line[line_len] = ' ';
        line[line_len + 1] = '\0';
        line_len++;
    }
    strcat(line, word);
    line_len += strlen(word);
    num_words++;
}

int space_remaining(void)
{
    return MAX_LINE_LEN - line_len;
}

void write_line(void)
{
    int extra_spaces, spaces_to_insert, i, j;

    extra_spaces = MAX_LINE_LEN - line_len;
    for (i = 0; i < line_len; i++)
    {
        if (line[i] != ' ')
        {
            putchar(line[i]);
        }
        else 
        {
            spaces_to_insert = extra_spaces / (num_words - 1);
            for (j = 1; j <= spaces_to_insert + 1; j++)
            {
                putchar(' ');
            }
            extra_spaces -= spaces_to_insert;
            num_words--;
        }
    }
    putchar('\n');
}

void flush_line(void)
{
    if (line_len > 0)
    {
        puts(line);
    }
}
```

Most of the functions in `line.c` are easy to write. The only tricky one is `write_line`, which writes a line with justification. `write_line` writes the characters in `line` one by one, pausing at the space between each pair of words to write additional spaces if needed. 

The number of additional spaces is stored in `spaces_to_insert`, which has the value `extra_spaces / (num_words - 1)`, where `extra_spaces` is initially the difference between the maximum line length and the actual line length. 

Since `extra_spaces` and `num_words` change after each word is printed, `spaces_to_insert` will change as well. If `extra_spaces` is 10 initially and `num_words` is 5, then the first word will be followed by 2 extra spaces, the second by 2, the third by 3 and the fourth by 3. 

## 15.4 Building a Multiple-File Program

Building a large program requires the same basic steps as building a small one:

- Compiling. Each source file in the program must be compiled separately. Header files don't need to be compiled as they do so automatically whenever they're included.

- Linking. The linker combines the object files created in the previous step along with code for library functions to produce an executable file. Among other duties, the linker is responsible for resolving external references left behind by the compiler.

Most compilers all us to build a program in a single step; with GCC we'd use the following command to build `justify`:

```shell
gcc -o justify justify.c line.c word.c
```

The three source files are first compiled into object code, and then the object files are passed to the linker to be combined into a single file. `-o` specifies that we want the executable file's name to be `justify`. 

### Makefiles

Putting the names of all relevant source files on the command line quickly gets tedious. We can also waste a lot of time rebuilding a program if we recompile all source files, not just the ones that were changed.

To make it easier to build large programs, UNIX created the concept of the makefile, a file containing the information necessary to build a program. 

Makefiles list the files that are part of the program, but also describe dependencies among the files. Suppose that `foo.c` includes the file `bar.h`, we say that `foo.c` "depends" on `bar.h`, because a change to it will require us to recompile `foo.c`. 

Here's a UNIX makefile for the `justify` program:

```Makefile
justify:  justify.o word.o line.o 
    gcc -o justify justify.o word.o line.o

justify.o: justify.c word.h line.h
    gcc -c justify.c

word.o: word.c word.h
    gcc -c word.c

line.o: line.c line.h
    gcc -c line.c
```

There are four groups of lines, each group is known as a rule. The first line in each rule gives a ***target*** file, followed by the file on which it depends. 

The second line is a command to be executed if the target should need to be rebuilt because of a change to its dependent files. 

In the second rule, `justify.o` is the target:

```Makefile
justify.o: justify.c word.h line.h
    gcc -c justify.c
```

Once we've created a makefile for a program, we can use the `make` utility to build (or rebuild) the program. By checking the time and date associated with each file in the program, `make` can determine which files are out of date.

- Each command in a makefile must be preceded by a tab character and not a series of spaces.

- a makefile is normally stored in a file named `Makefile` or `makefile`. When the make utility is used, it automatically checks the current directory for a file with one of these names.

- To invoke `make`, use the command `make target` where target is one of the targets listed in the makefile. 

- If no target is specified when make is invoked, it will build the target of the first rule. Except for this special property of the first rule, the order of rules in a makefile is arbitrary.

Make is complicated enough that entire books have been written about it, so we won't attempt to delve deeper in this book.

### Errors During Linking

Some errors that can't be detected during compilation will be found during linking. These errors are usually quite easy to fix:

- Misspellings. If the name of a variable or function is misspelled, the linker will report it as missing. e.g. if we've misspelled `read_char` as `read_cahr` the linker will report that `read_cahr` is missing.

- Missing Files. If the linker can't find the functions that are in `foo.c`, it may not know about the file. Check the makefile or project file to make sure that `foo.c` is listed there.

- Missing Libraries. The linker may not be able to find all the library functions used in the program. Some libraries, such as `<math.h` require you to use the flag `-lm` option when the program is linked to work correctly.

### Rebuilding a Program

During the development of a program, it's rare that we'll need to compile all of its files at the same time. Typically, we'll test the program, make a change and then build it again. To save time, the rebuilding process should recompile only those files that might have changed.

***The first possibility*** is that the change affects a single source file. In that case, only that file must be recompiled, and the entire program will need to be relinked. In the `justify` program, suppose we decide to condense the `read_char` function in `word.c`.

```C
int read_char(void)
{
    int ch = getchar();

    return (ch == '\n' || ch == '\t') ? ' ' : ch;
}
```

This modification doesn't affect `word.h`, so we need only recompile `word.c` and relink the program. 

***The second possibility*** is that the change affects a header file. In that case, we should recompile all files that include the header file, since they could potentially be affected by the change.

In the event that we want to change the `read_word` function to cut out the requirement for calling `strlen` on it (as it already tracks the length of the string). 

First, we change the prototype of `read_word` in `word.h`:

```C
// read_word:
/*
 *  Reads the next word from the input and stores it in word
 *  Makes word empty if no word can be read due to EOF
 *  Truncates the word if its length exceeds len
 *  Returns the number of characters stored.
 */
int read_word(char *word, int len);
```

We also need to change it `word.c`. 

```C
int read_word(char *word, int len)
{
    int ch, pos = 0;

    while ((ch = read_char()) == ' ')
        ;
    while (ch != ' ' && ch != EOF)
    {
        if (pos < len)
        {
            word[pos++] = ch;
        }
        ch = read_char();
    }
    word[pos] = '\0';
    return pos;
}
```

Finally we modify `justify.c` by removing the include of `<string.h>` and changing `main` as follows:

```C
int main(void)
{
    char word[MAX_WORD_LEN+2];
    int word_len;

    clear_line();

    for (;;)
    {
        word_len = read_word(word, MAX_WORD_LEN + 1);
        if (word_len == 0)
        {
            flush_line();
            return 0;
        }
        if (word_len + 1 > space_remaining())
        {
            write_line();
            clear_line();
        }
        add_word(word);
    }
}
```

Once we've made these changes, we'll rebuild the `justify` program by recompiling `word.c` and `justify.c` and then relinking. There's no need to recompile `line.c`, which doesn't include`word.h` and won't be affected by any changes to it. 

With GCC, we could rebuild it by entering the following command; note the mention of `line.o` instead of `line.c`:

```bash
gcc -o justify justify.c word.c line.o
```

One of the main advantages of using makefiles is that rebuilding is handled automatically. By examining the date of each file, the `make` utility can determined which files have changed since the program was last built. It then recompiles these files and all files that depend on them.

### Defining Macros Outside a Program

C Compilers usually provide some method of specifying the value of a macro at the time a program is compiled. This ability makes it easy to change the value of a macro without editing any of the program's files. 

GCC supports the `-D` option, which allows the value of a macro to be specified on the command line:

```bash
gcc -DDEBUG=1 foo.c
```

is equivalent to putting the line 

```C
#define DEBUG 1
```

At the beginning of `foo.c`. If the `-D` flag names a macro without specifying its value, it's defined as having a value of 1. 

Many compilers also support the `-U` option, which "undefines" a macro as if you'd just used `#undef` in the source file. We can use `-U` to undefine a predefined macro or one that was defined earlier in the command line using `-D`. 

## Chapter 15 Q&A

Q: There are no examples of using the `#include` directive to include a source file; what would happen if we were to do this?

A: It's not good practice. Suppose that we have a function that we'll need in two files, so in both of those files we put `#include foo.c` into both of their files. Each will compile without issue.

However, the linker will later throw an error when it finds two different copies of the function we wanted in the two different files, and throws an error.

Q: I don't understand why each source file needs its own header file; why not just have one big header file containing macros, `typedef`s and function prototypes? By including this file, each source file would have access to all the shared information it needs.

A: The "one big header file" approach certainly works, and finds use in C programming all over the place. However, for larger programs, the disadvantages of this approach tend to outweigh its advantages.

Using a single header provides no useful information to someone reading the program later. With multiple header files, the reader can quickly see that other parts of the program are used by a particular source file.


