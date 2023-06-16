// SIMPLIFIED BEAUFORT SCALE
// andr-be 06/2023

#include <stdio.h>

int get_speed(void);
char* get_beaufort(int);

int main(void)
{
    while(1) {
        int wind_speed = get_speed();
        char* beaufort = get_beaufort(wind_speed);
        printf("Beaufort Score: %s\n\n", beaufort);
    }
}

int get_speed(void){
    int wind_speed = 0;
    printf("Enter a windpseed in knots:  ");
    scanf("%d", &wind_speed);
    fflush(stdin);
    return wind_speed;
}

char* get_beaufort(int wind_speed)
{
    char* beaufort;

    if      (wind_speed <  1) beaufort = "Calm";
    else if (wind_speed <  4) beaufort = "Light air";
    else if (wind_speed < 28) beaufort = "Breeze";
    else if (wind_speed < 48) beaufort = "Gale";
    else if (wind_speed < 64) beaufort = "Storm";
    else                      beaufort = "Hurricane!";

    return beaufort;
}
