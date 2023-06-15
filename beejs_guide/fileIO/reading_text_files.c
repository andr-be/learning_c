#include <stdio.h>

int main(void)
{
    FILE *fp;                       // variable to represent open file

    fp = fopen("hello.txt", "r");   // Open file for reading

    int c = fgetc(fp);              // read a single character
    printf("%c\n", c);              // print char to stdout

    fclose(fp);                     // close the file when done
}

