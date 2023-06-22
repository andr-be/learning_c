// VELOCITY / TIME CALCULATOR
// andr-be 06/2023

#include <stdio.h>

int main(void)
{
    double time_of_flight_µs, velocity_ms;
    printf("Please enter a ToF: (µs):  ");
    scanf("%lf", &time_of_flight_µs);
    printf("Please enter the material velocity (m/s): ");
    scanf("%lf", &velocity_ms);

    double tof_secs = time_of_flight_µs / 1e6;
    double thickness = tof_secs * velocity_ms;

    printf("This is equivalent to a thickness of %.3e m", thickness);

    return 0;
}