// EARLIEST DATE FINDER
// andr-be 06/2023
/*
    I think I'm getting a lot better at all the basic aspects
    of struct use. Even though I haven't made it to the struct
    section of the book yet!
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define DAYS_IN_MONTH 30

typedef struct Date {
    int dd;
    int mm;
    int yyyy;
} Date;

Date get_date(void);
Date earliest(Date, Date);
char* date_string(Date);

int main(void) {
    Date all_inputs[1024] = {0},
         user_date        = {.dd= 1, .mm= 1, .yyyy=1900},
         earliest_date    = {.dd=31, .mm=12, .yyyy=2023};

    int i = 0;
    for (; i < 1024; i++) {
        user_date = get_date();
        if (user_date.dd == 0 && user_date.mm == 0 && user_date.yyyy == 0)
            break;
        all_inputs[i] = user_date;
    }
    for (int j = 0; j < i; j++)
        earliest_date = earliest(earliest_date, all_inputs[j]);

    printf("The earliest date entered is: %s\n", date_string(earliest_date));
    return 0;
}

Date get_date(void) {
    Date input = {.dd=1, .mm=1, .yyyy=1900};
    printf("Enter a date (dd/mm/yyyy): ");
    scanf("%d / %d / %d", &input.dd, &input.mm, &input.yyyy);
    return input;
}

Date earliest(Date a, Date b) {
    return ((a.dd + a.mm * DAYS_IN_MONTH) < (b.dd + b.mm * DAYS_IN_MONTH)) ? a : b;
}

char* date_string(Date input) {
    char *result = malloc(16 * sizeof(char));
    sprintf(result, "%02d/%02d/%4d", input.dd, input.mm, input.yyyy);
    return result;
}
