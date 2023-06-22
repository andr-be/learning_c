// VELOCITY / TIME CALCULATOR
// andr-be 06/2023

#include <stdio.h>

int main(void)
{
    double thickness_mm, velocity_ms;
    printf("Please enter a thickness (mm):  ");
    scanf("%lf", &thickness_mm);
    printf("Please enter the material velocity (m/s): ");
    scanf("%lf", &velocity_ms);

    double thickness_meters = thickness_mm / 1000.0;
    double time_of_flight = thickness_meters / velocity_ms;
    printf("This gives a Time of Flight of %.3e seconds!", time_of_flight);

    return 0;
}