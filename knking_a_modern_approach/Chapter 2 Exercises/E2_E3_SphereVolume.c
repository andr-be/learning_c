// SPHERE VOLUME CALCULATOR
// andr-be 2023

#include <stdio.h>

#define PI 3.1416
int main(){
  float radius;
  printf("Please enter a radius.\n");
  scanf("%f", &radius);

  float volume = (4.0f / 3.0f) * PI * radius * radius;

  printf("\nRadius: %3.2f mm\nVolume: %5.2f mm^2", radius, volume);

  return 0;
}