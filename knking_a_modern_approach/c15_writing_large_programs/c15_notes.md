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



