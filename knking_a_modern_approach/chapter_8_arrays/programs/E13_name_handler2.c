// NAME HANDLER
// andr-be 07/2023
/*
    Reformats an entered name to the old `Surname -> F Initial` standard
    e.g. Lloyd Fosdick -> Fosdick, L.
    apparently I was meant to not do this with arrays beforehand lmao
*/

#include <stdio.h>
#define STR_LEN 20

int main(void)
{
    // I wish I knew how better to initialise strings than as arrays!
    char first[STR_LEN], last[STR_LEN];
    printf("Enter a first and last name: ");

    // also would be nice if I could set the scanf field with STR_LEN
    scanf("%19s %19s", first, last);

    // prints the last name and the first letter of the first name
    printf("You entered the name: %s, %c.\n", last, first[0]);
    return 0;
}
