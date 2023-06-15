// String Initialisers

#include <stdio.h>

int main(void)
{
    // pointer to a string literal
    // IMMUTABLE
    char *s = "Hello, world!";

    // array copy of the string we can change at will
    // MUTABLE
    char t[] = "Hello, again!";

    // It's fine to modify an array string.
    t[0] = 'Z';
    printf("%s\n", t); // Zello, again!

    // modifying a string literal is UNDEFINDED BEHAVIOUR 
    // this will crash the program
    s[0] = 'W';
}