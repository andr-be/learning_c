# Chapter 15: Writing Large Programs

> Around computers it is difficult to find the correct unit of time to measure progress. Some cathedrals took a century to complete. Can you imagine the grandeur and scope of a program that would take as long?

Most C programs are not small enough to be put into a single file; multi-file programs are the rule rather than the exception; a typical program consists of several source files and usually some header files as well. Source files contain definitions of functions and external variables; header files contain information to be shared among source files.

## 15.1 Source Files

