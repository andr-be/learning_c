#include <stdio.h>

int main(int argc, char const *argv[])
{
    char *p = "abc";

    putchar(p);
    putchar(*p);
    puts(p);
    puts(*p);
    return 0;
}
