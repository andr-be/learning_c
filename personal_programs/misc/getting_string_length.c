// CALCULATING THE LENGTH OF A STRING
// andr-be 06/2023
/*
    There are two options for storing a string in memory:
    1)  store the bytes of the string along with a number indicating
        the length of the string.
    
    2)  store the bytes of the string and mark the end of the string
        with a special byte called the _terminator_

    Most modern programming languages take option 1
    C took approach 2, its string terminator is `\0`
*/

#include <stdio.h>
#include <string.h>

int my_strlen(char *s);

int main(void)
{
    char *s = "Hello, world!";  // Actually "Hello!\0" behind the scenes
    char *t = "Second string tester string!";

    printf("1)\t%s\n", s);
    printf("2)\t%s\n\n", t);

    printf("The 1st string is %zu bytes long.\n", strlen(s));
    printf("The 2nd string is %zu bytes long.\n", my_strlen(t));
}

int my_strlen(char *s)
{
    int count = 0;

    while (s[count] != '\0')    // single quotes for single char
        count++;

    return count;
}
