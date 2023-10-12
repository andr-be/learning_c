#include "clock.h"

clock_t clock_create(int hour, int minute)
{
    while (minute < 0) { 
        hour -= 1; 
        minute = 60 + minute; 
    }
    while (hour < 0) hour = 24 + hour;

    int new_hour = (hour + minute / 60) % 24,
        new_minute = minute % 60;

    clock_t result = {0};
    snprintf(result.text, sizeof(result.text), "%02d:%02d", new_hour, new_minute);

    return result;
}

clock_t clock_add(clock_t clock, int minute_add)
{
    int hour, minute;
    sscanf(clock.text, "%2d:%2d", &hour, &minute);
    minute += minute_add;
    return clock_create(hour, minute);
}

clock_t clock_subtract(clock_t clock, int minute_subtract)
{
    int hour, minute;
    sscanf(clock.text, "%2d:%2d", &hour, &minute);
    minute -= minute_subtract;
    return clock_create(hour, minute);
}

bool clock_is_equal(clock_t a, clock_t b)
{
    for (int i = 0; i < MAX_STR_LEN; i++)
        if (a.text[i] != b.text[i]) 
            return false;
    
    return true;
}