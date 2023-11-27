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

