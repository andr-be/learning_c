// Reading a Line at a Time with fgets()

#include <stdio.h>

int main(void)
{
    FILE *fp;
    char s[1024]; // big enough for any line this program will encounter
    int linecount = 0;

    fp = fopen("quote.txt", "r");

    // fgets()
    /*
        takes a pointer to a char buffer to hold bytes
        a maximum number of bytes to read
        a FILE* to read from
        it returns NULL on end-of-file or error.
    */
    while (fgets(s, sizeof s, fp) != NULL)
        printf("%d: %s", ++linecount, s);

    fclose(fp);
}