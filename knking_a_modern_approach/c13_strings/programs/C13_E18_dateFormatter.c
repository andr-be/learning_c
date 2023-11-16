// Chapter 13 - Exercise 18 - dateFormatter.c
// andr-be 11/2023
/*
    accepts a date from the user in dd/mm/yyyy
    displays date in form month dd, yyyy where month is a word
    stores the month names in an array that contains pointers to strings
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 96

const char *MONTHS[] = {
    "January", "February", "March", "April", "May", "June", 
    "July", "August", "September", "October", "November", "December"
};

const int DAYS_IN_MONTH[12] = {
    31, 28, 31, 30, 31, 30, 
    31, 31, 30, 31, 30, 31
};

const char *ERROR[] = {
    "ERROR 01: NOT ENOUGH ARGUMENTS",
    "ERROR 02: INVALID DATE"
};

int format_date(const char *date, char *dest);

int main(int argc, char const *argv[])
{
    char *formatted = calloc(MAX_CHARS, sizeof(char));

    if (argc < 2) {
        fprintf(stderr, ERROR[0]);
        free(formatted);
        return EXIT_FAILURE;
    }

    else if (format_date(argv[1], formatted) == EXIT_FAILURE) {
        free(formatted);
        return EXIT_FAILURE;
    }

    else {
        fprintf(stdout, "%s\n", formatted);
        free(formatted);
        return EXIT_SUCCESS;
    }
}

int format_date(const char *date, char *dest)
{   
    int dd = 0, mm = 0, yyyy = 0;
    
    sscanf(date, "%2d/%2d/%4d", &dd, &mm, &yyyy);

    // validations
    if (mm < 1 || mm > 12 || dd < 1 || dd > DAYS_IN_MONTH[mm - 1]) {
        fprintf(stderr, ERROR[1]);
        return EXIT_FAILURE;
    }

    sprintf(dest, "%s %d, %d", MONTHS[mm - 1], dd, yyyy);

    return EXIT_SUCCESS;
}