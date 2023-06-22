// MEASUREMENT STRUCT PROTOTYPE
// andr-be 06/2023
/*
    This program allows you to calculate what reading you'll get if you change
    the gauge velocity to a different value. Can be useful for working out
    what the zero offset should read at in Flaw Mode on the DFX-7+ & 8+.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Reading
{
    double time_of_flight_s;
    double velocity_m_s;
    double thickness_m;
} Reading;


Reading new_reading(double, double);
Reading change_velocity(Reading, double);
char* to_string(Reading);


int main(void)
{
    double t_mm = 0, v_m_s = 0;
    printf("Please enter the thickness in mm and your material velocity: (e.g. 10.49 @ 5918.2): ");
    scanf("%lf @ %lf", &t_mm, &v_m_s);
    Reading new = new_reading(t_mm, v_m_s);
    printf("%s", to_string(new));


    printf("Enter a new velocity to find what the equivalent thickness would be for that TOF: ");
    scanf("%lf", &v_m_s);
    Reading adjusted = change_velocity(new, v_m_s);
    printf("%s", to_string(adjusted));


    return 0;
}

double convert_mm_to_m(double mm) {
    return mm / 1e3;
}

Reading new_reading(double thickness_mm, double velocity_m_s) {
    // accepts thickness values in mm, produces reading in metres
    double time_of_flight_s = convert_mm_to_m(thickness_mm) / velocity_m_s;
    Reading new = {
        .time_of_flight_s = time_of_flight_s,
        .velocity_m_s = velocity_m_s,
        .thickness_m = convert_mm_to_m(thickness_mm), 
    };
    return new;
}

char* to_string(Reading r) {
    char *result = malloc(100 * sizeof(char));
    double mm_thick = r.thickness_m * 1e3, us_time = r.time_of_flight_s * 1e6;
    sprintf(result, "THICK: %.2fmm\tVELOC: %.2fm/s\tTOF: %.3fus\n", mm_thick, r.velocity_m_s, us_time);
    return result;
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