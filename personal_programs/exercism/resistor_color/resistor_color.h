#ifndef RESISTOR_COLOR_H
#define RESISTOR_COLOR_H

#include <stdlib.h>
#define NUM_COLORS 10

typedef enum {
    BLACK,
    BROWN,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    VIOLET,
    GREY,
    WHITE
} resistor_band_t;

// returns the corresponding number value when given a color
int color_code(resistor_band_t color);

// returns an array of all the color codes in order
resistor_band_t *colors(void);

// returns the corresponding color when given a number
resistor_band_t get_color(int value);

#endif
