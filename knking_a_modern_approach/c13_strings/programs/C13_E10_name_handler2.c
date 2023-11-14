// NAME HANDLER
// andr-be 07/2023
/*
    Reformats an entered name to the old `Surname -> F Initial` standard
    e.g. Lloyd Fosdick -> Fosdick, L.
*/

#include <stdio.h>
#include <stdlib.h>

#define STR_LEN 20

void reverse_name(char *name);

int main(void)
{
    // I wish I knew how better to initialise strings than as arrays!
    char name[STR_LEN * 2];
    printf("Enter a first and last name: ");

    fgets(name, STR_LEN * 2, stdin);

    reverse_name(name);

    return 0;
}

void reverse_name(char *name)
{
    char *first = name,
         *last;

    while (*name++) {
        if (*name == ' ') {
            last = name + 1;
        } else if (*name == '\n') {
            *name = '\0';
        }
    }

    if (*last) { 
        printf("%s, %c\n", last, first[0]); 
    }
}