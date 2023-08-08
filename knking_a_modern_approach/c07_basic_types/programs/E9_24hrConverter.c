// 12-to-24hr CLOCK CONVERTER
// andr-be 07/2023 
/*
    Short simple way to work out a 24hr time from a 12hr time
    does some mild error handling
*/

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

Time24 sanitise_time(Time24);
Time24 get_user_time(void);

typedef struct Time24 {
    int hr;
    int min;
} Time24;

int main(void) {
    Time24 time = get_user_time();
    printf("Equivalent 24-hr time: %02d:%02d\n", time.hr, time.min);
    return 0;
}

/// @brief  get a 12hr time input from a user and produce a Time24 struct
/// @return 24hr Time24 struct
Time24 get_user_time(void) {
    int hr = 0, min = 0;
    char meridian;

    printf("Enter a 12-hour time: ");
    scanf("%2d:%2d %c", &hr, &min, &meridian);
    hr = (toupper(meridian) == 'P') ? hr + 12 : hr;

    Time24 result = { .hr = hr, .min = min };
    return sanitise_time(result);
}

/// @brief When given a 24hr time, will adjust the numbers to correct wrong values
/// @param input raw time from user input
/// @return sanitised time input
Time24 sanitise_time(Time24 input) {
    if (input.min >= 60 || input.min < 0) { 
        input.hr += input.min / 60; 
        input.min %= 60; 
    }

    if (input.hr >= 24 || input.hr < 0) 
        input.hr %= 24;

    return input;
}
