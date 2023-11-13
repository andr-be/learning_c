// Chapter 13 - Exercise 6 - planets2.c
// andr-be 11/2023
/*
    Improve the planet.c program of Section 13.7 by having it  ignore case 
    when comparing command-line arguments with strings in the planets array
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_PLANETS 9

int caseless_compare(char *f, char *s);

int main(int argc, char *argv[])
{
  int i, j;
  char *planets[] = { "Mercury", "Venus", "Earth",
                      "Mars", "Jupiter", "Saturn",
                      "Uranus", "Neptune", "Pluto" };

  for (i = 1; i < argc; i++) {
    for (j = 0; j < NUM_PLANETS; j++)
      if (caseless_compare(argv[i], planets[j]) == 0) {
        printf("%s is planet %d\n", argv[i], j + 1);
        break;
      }
    if (j == NUM_PLANETS)
      printf("%s is not a planet\n", argv[i]);
  }

  getchar();
  return 0;
}

/// @brief compares two strings, f & s for alphabetical order
/// @param f first string
/// @param s second string
/// @return <0 if f comes before s, >0 if f comes after s, 0 if equal
int caseless_compare(char *f, char *s)
{
    while (toupper(*f) == toupper(*s)) {
        if (*f == 0 && *s == 0)
            return 0;

        else if (toupper(*f) != toupper(*s))
            break;

        f++, s++;
    }
    return *f - *s;
}
