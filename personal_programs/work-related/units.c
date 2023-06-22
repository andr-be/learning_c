// UNIT MEASUREMENT PROGRAM
// andr-be 06/2023
#include <stdio.h>
#include <stdlib.h>

typedef enum Unit
{
    MM,     // millimetres
    M,      // metres
    IN,     // inches
    THOU,   // thousandths of an inch
    M_S,    // meters per second
    SEC,    // seconds
    USEC,   // microseconds
} Unit;

typedef struct Measurement {
    double Quantity;
    Unit Unit;
} Measurement;

char* unit_string(Unit input) {
    char* result = malloc(16 * sizeof(char));
    switch (input)
    {
    case MM:    sprintf(result, "mm");      break;
    case M:     sprintf(result, "m");       break;
    case IN:    sprintf(result, "inches");  break;
    case THOU:  sprintf(result, "thou");    break;
    case M_S:   sprintf(result, "m/s");     break;
    case SEC:   sprintf(result, "s");       break;
    case USEC:  sprintf(result, "us");      break;
    }
    return result;
}

Measurement convert_mm_in(Measurement input) {
    Measurement output = {0};
    if      (input.Unit == MM)    { output.Unit = IN; output.Quantity = input.Quantity / 25.4; }
    else if (input.Unit == IN)    { output.Unit = MM; output.Quantity = input.Quantity * 25.4; }
    else if (input.Unit == M)     { output.Unit = IN; output.Quantity = (input.Quantity * 1e3) / 25.4; }
    else if (input.Unit == THOU)  { output.Unit = MM; output.Quantity = (input.Quantity / 1e3) * 25.4; }
    else printf("IMPROPER CONVERSION!");
    return output;
}

int main(void)
{
    Measurement m = {
        .Unit=MM,
        .Quantity=25.4
    };

    Measurement n = convert_mm_in(m);
    printf("%.3lf %s", n.Quantity, unit_string(n.Unit));
}