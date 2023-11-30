#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define LINE_MAX 64

typedef enum Directions {
    FORWARD,
    UP,
    DOWN
} Directions;

typedef struct SubDirection {
    Directions direction;
    int magnitude;
} SubDirection;

typedef struct SubPosition {
    int horizontal;
    int depth;
    int aim;
} SubPosition;

int solution(FILE *input, int part);
int parse_magnitude(char *direction_str);
SubDirection parse_direction(char *direction_str);
SubPosition modify_position(SubPosition pos, SubDirection dir);
SubPosition modify_position_complex(SubPosition pos, SubDirection dir);