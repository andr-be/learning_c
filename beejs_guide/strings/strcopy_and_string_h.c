// string.h and strcpy() -> How to Copy String Properly

#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[] = "Hello, world!";
    char t[100];    // each char is 1 byte, so this is blenty of room

    // this makes a copy of the string
    strcpy(t, s);
    // string copy TO: t 
    //           FROM: s

    // we modify t
    t[0] = 'z';

    // and S remains unaffected because it's a different string
    printf("%s\n", s);  // "hello, world!"

    // the same cannot be said for t
    printf("%s\n", t);  // "zello, world!"
}