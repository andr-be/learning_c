// Chapter 13 - Exercise 2 - remind2
// andr-be 11/2023
/*
    improve the remind.c program of section 13.5 in the following ways:
    a)  Have the program print an error message and ignore a reminder if the
        corresponding day is negative or larger than 31 
        HINT: Use the continue statement

    b)  Allow the user to enter a day, a 24-hour time, and a reminder. The 
        printed reminder list should be sorted first by day, then by time
        The original program allows the user to enter a time, but it's
        treated as part of the reminder. 

    c)  Have the program print a one-year reminder list. Require the user
        to enter days in the form month/day. 
*/

#include <stdio.h>
#include <string.h>

#define MAX_REMIND 50   // maximum number of reminders
#define MSG_LEN 60      // max length of reminder messages

int read_line(char str[], int n);
void clear_input_buffer(void);

int main(void)
{
    int month, day, hour, min, 
        i, j, 
        num_remind = 0;

    char reminders[MAX_REMIND][MSG_LEN+3],
         date_str[8], time_str[8], msg_str[MSG_LEN+1];

    for (;;) {
        // print the loop if you've hit the max number of reminders
        if (num_remind == MAX_REMIND) {
          printf("-- No space left --\n");
          break;
        }
        // opening prompt & date parse
        printf("Enter date and time (mm/dd hh:mm) and a reminder: ");
        scanf("%2d/%2d", &month, &day);

        // date validation
        if (day == 0) {
            printf("Printing list:\n");
            break;
        }
        if (day < 0 || day > 31) {
            printf("ERROR: Day must be between 1 & 31!\n");
            clear_input_buffer();
            continue;
        }
        if (month < 0 || month > 12) {
            printf("ERROR: Month must be between 1 & 12!\n");
            clear_input_buffer();
            continue;
        }

        // time parse
        scanf(" %2d:%2d", &hour, &min);
        // I would put time validation here if I cared enough

        // format the reminder string
        sprintf(date_str, "%02d/%02d ", day, month);
        sprintf(time_str, "%02d:%02d ", hour, min);
        read_line(msg_str, MSG_LEN);

        // look for the first message later than the current one
        for (i = 0; i < num_remind; i++)
          if (strcmp(date_str, reminders[i]) < 0)
            break;

        // move all later reminders back by one
        for (j = num_remind; j > i; j--)
          strcpy(reminders[j], reminders[j-1]);

        // copy the date to the right location, add the time and the reminder
        strcpy(reminders[i], date_str);
        strcat(reminders[i], time_str);
        strcat(reminders[i], msg_str);
        num_remind++;
    }

    printf("\n Date  Time   Reminder\n");
    for (i = 0; i < num_remind; i++)
        printf(" %s\n", reminders[i]);

    return 0;
}

int read_line(char str[], int n)
{
    int ch, i = 0;

    while ((ch = getchar()) != '\n')
        if (i < n) str[i++] = (char) ch;

    str[i] = '\0';
    return i;
}

/// @brief non-UB way to flush the standard input buffer
void clear_input_buffer(void)
{
    int buf;
    while ( ( buf = getchar() ) != EOF && buf != '\n' )
        ;
}