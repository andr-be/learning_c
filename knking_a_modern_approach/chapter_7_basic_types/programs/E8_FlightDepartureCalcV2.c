// FLIGHT DEPARTURE CALCULATOR
// andr-be 06/2023
/*
    Now the clock takes input in the form of XX:YY ZM

*/

#include <stdio.h>
#include <stdlib.h>

#define TOTAL_FLIGHTS   8
#define MINS_IN_HR      60
#define MINS_IN_DAY     60 * 24
#define CLOCK_SIZE      6

typedef struct {
    int mins;      // minutes past midnight
} Time;

typedef struct {
    Time departure;
    Time arrival;
} Flight;

Time to_time(int, int);
Time get_user_time(void);
Time get_12hr_time(void);
char* to_string(Time);
int minutes_apart(Time, Time);

void update(Flight*);
void get_best_flight(Flight*, Time);

int main (void)
{
    Flight available_flights[TOTAL_FLIGHTS];
    update(available_flights);
    
    Time input = get_12hr_time();
    get_best_flight(available_flights, input);
}

/// @brief converts two integers into a Time
/// @param hrs a 24 hour time's HH component
/// @param mins a 24 hour time's MM component
/// @return minute-formatted time struct 
Time to_time(int hrs, int mins) {
    int mins_since_0 = hrs * MINS_IN_HR + mins;
    Time new = {mins_since_0};
    return new;
}

/// @brief calculate a duration in minutes between two times
/// @param t1 the first time point
/// @param t2 the second time point
/// @return time difference in minutes between t1 and t2
int minutes_apart(Time t1, Time t2) {
    int result = 0;
    result = (t1.mins > t2.mins) 
        ? t1.mins - t2.mins : t2.mins - t1.mins;
    return result;
}

/// @brief generates a pretty formatted string for printing
/// @param input the time to be stringified
/// @return a string of formatted input
char* to_string(Time input) {
    int hrs  = input.mins / MINS_IN_HR, 
        mins = input.mins % MINS_IN_HR;

    char* output = (char*)malloc(CLOCK_SIZE * sizeof(char));
    snprintf(output, CLOCK_SIZE, "%02d:%02d", hrs, mins);
    return output;
}

/// @brief hacky mutation way to get the data into the program...
/// @param blank blank array of flights that will be loaded with the problem set
void update(Flight blank[TOTAL_FLIGHTS]) {
    Flight f1 = {to_time( 8,  0), to_time(10, 16)},
           f2 = {to_time( 9, 43), to_time(11, 52)}, 
           f3 = {to_time(11, 19), to_time(13, 31)}, 
           f4 = {to_time(12, 47), to_time(15,  0)}, 
           f5 = {to_time(14,  0), to_time(16,  8)}, 
           f6 = {to_time(15, 45), to_time(17, 55)}, 
           f7 = {to_time(19,  0), to_time(21, 20)}, 
           f8 = {to_time(21, 45), to_time(23, 58)};

    Flight list[TOTAL_FLIGHTS] = {f1, f2, f3, f4, f5, f6, f7, f8};

    for (int i = 0; i < TOTAL_FLIGHTS; i++)
        blank[i] = list[i];
}

/// @brief check every flight on the flightlist and find the closest one to input
/// @param available the flight list of every flight that day
/// @param input the time the search will try to get closer to
void get_best_flight(Flight available[TOTAL_FLIGHTS], Time input) {
    int closest_flight = MINS_IN_DAY,
        best_flight = 0;

    for (int i = 0; i < TOTAL_FLIGHTS; i++)
    {
        Time depart = available[i].departure, 
             arrive = available[i].arrival;

        char *st_depart = to_string(depart),
             *st_arrive = to_string(arrive);

        printf("Flight: %d\tDeparture: %s\tArrival: %s\n", 
                i, st_depart, st_arrive);

        if (minutes_apart(input, depart) < closest_flight) {
            closest_flight = minutes_apart(input, depart);
            best_flight = i;
        }
        free(st_arrive); free(st_depart);
    }
    printf("\nBEST FLIGHT: %d", best_flight);
    printf("\tDEPARTS: %s", to_string(available[best_flight].departure));
    printf("\tARRIVES: %s\n", to_string(available[best_flight].arrival));
}

/// @brief deprecated function that gets the user to enter a time in 24hr notation
/// @return an input checked Time structure
Time get_user_time(void){
    int hrs = 0, mins = 0;
    printf("Enter a 24-hour time: ");
    scanf("%2d/%2d", &hrs, &mins);
    return to_time(hrs, mins);
}

/// @brief gets the time from the user in a 12-hr + meridian notation
/// @return an input checked Time structure
Time get_12hr_time(void){
    int hrs = 0, mins = 0;
    char meridian;

    printf("Enter a 12-hour time (e.g. 10:12 PM): ");
    scanf("%2d:%2d %c", &hrs, &mins, &meridian);
    printf("MER: %c\n", meridian);
    if (meridian == 'P' || meridian == 'p') {
        hrs += 12;
    }
    return to_time(hrs, mins);
}