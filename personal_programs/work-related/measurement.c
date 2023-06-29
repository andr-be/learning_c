// MEASUREMENT STRUCT PROTOTYPE
// andr-be 06/2023
/*
    This program allows you to calculate what reading you'll get if you change
    the gauge velocity to a different value. Can be useful for working out
    what the zero offset should read at in Flaw Mode on the DFX-7+ & 8+.
*/

#include <stdio.h>
#include <stdlib.h>

typedef enum Unit
{
    MM,     // millimetres
    M,      // metres
    IN,     // inches
    M_S,    // meters per second
    S,      // seconds
    US,     // microseconds
} Unit;

typedef struct Reading
{
    double time_of_flight_s;
    double velocity_m_s;
    double thickness_m;
} Reading;

typedef struct Measurement {
    double Quantity;
    Unit Unit;
} Measurement;

double convert_mm_to_m(double);
Reading tof_from_thickness_speed(double, double);
Reading change_velocity(Reading, double);
Reading from_time_us(double, double);
char* to_string(Reading);


int main(void)
{
    Reading r = from_time_us(3.378e-6, 5918);
    printf("R: %s", to_string(r));
    r = from_time_us(3.378e-6, 2415);
    printf("R: %s", to_string(r));

    return 0;
}

/**
 * @brief Converts a value in millimetres to metres.
 * 
 * @param mm -> the value in millimetres (1e-3 m)
 * @return double -> the value in metres
 */
double convert_mm_to_m(double mm) {
    return mm / 1e3;
}

Reading tof_from_thickness_speed(double thickness_mm, double velocity_m_s) {
    // accepts thickness values in mm, produces reading in metres
    double time_of_flight_s = convert_mm_to_m(thickness_mm) / velocity_m_s;
    Reading new = {
        .time_of_flight_s = time_of_flight_s,
        .velocity_m_s = velocity_m_s,
        .thickness_m = convert_mm_to_m(thickness_mm), 
    };
    return new;
}

Reading change_velocity(Reading r, double velocity_m_s) {
    double new_thickness = r.time_of_flight_s * velocity_m_s;
    Reading result = {
        .time_of_flight_s = r.time_of_flight_s,
        .velocity_m_s = velocity_m_s,
        .thickness_m = new_thickness
    };
    return result;
}

Reading from_time_us(double seconds, double velocity_m_s)
{
    double time_of_flight = (seconds * velocity_m_s);
    Reading new_reading = {
        .time_of_flight_s = seconds,
        .velocity_m_s = velocity_m_s,
        .thickness_m = time_of_flight / 2,
    };
    return new_reading;
}

char* to_string(Reading r) {
    char *result = malloc(100 * sizeof(char));
    double mm_thick = r.thickness_m * 1e3, us_time = r.time_of_flight_s * 1e6;
    sprintf(result, "THICK: %.2fmm\tVELOC: %.2fm/s\tTOF: %.3fus\n", mm_thick, r.velocity_m_s, us_time);
    return result;
}
