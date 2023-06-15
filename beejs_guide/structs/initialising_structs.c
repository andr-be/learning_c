// Simple Structs & Instantiation
/*
    There are different ways to initialise structs in C.
    1) blank initialise at compile time, dynamically assign data at runtime
    2) implicitly initialise at compile time based on order
    3) explicitly initialise at compile time with field names
*/
#include <stdio.h>

struct car
{
    char *name;
    float price;
    int speed;
};

// Method 1
struct car saturn; 

// Method 2
struct car golf = {"Golf Mk1 GTI", 9500.59, 190};

// Method 3
// (missing field designators are initialised to zero)
struct car viper = {
    .name="Dodge Viper SRT2", 
    .speed=300
};

int main (void)
{
    saturn.name = "Saturn SL/2";
    saturn.price = 15999.99;
    saturn.speed = 175;

    printf("Name:           %s\n", saturn.name);
    printf("Price (USD):    %.2f\n", saturn.price);
    printf("Top Speed (km): %d\n", saturn.speed);
    printf("\n");

    printf("Name:           %s\n", golf.name);
    printf("Price (USD):    %.2f\n", golf.price);
    printf("Top Speed (km): %d\n", golf.speed);
    printf("\n");

    printf("Name:           %s\n", viper.name);
    printf("Price (USD):    %.2f\n", viper.price);
    printf("Top Speed (km): %d\n", viper.speed);
}
