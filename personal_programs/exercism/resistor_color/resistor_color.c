#include "resistor_color.h"

// returns the corresponding number value when given a color
int color_code(resistor_band_t color)
{
    return (int) color;
}

// returns an array of all the color codes in order
resistor_band_t *colors(void)
{
    resistor_band_t *colors = malloc(sizeof(resistor_band_t) * NUM_COLORS);
    for (int i = 0; i < NUM_COLORS; i++)
        colors[i] = get_color(i);
    return colors;
}

// returns the corresponding color when given a number
resistor_band_t get_color(int value)
{
    return (resistor_band_t) value;
}
