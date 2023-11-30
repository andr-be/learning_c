// Advent of Code 2021 - Day 2 - Dive!
// andr-be 11/2023
/*
    Help pilot a submarine according to provided directions
    P1:     1,947,824
    P2: 1,813,062,561
*/

#include "dive.h"

int main(int argc, char const *argv[])
{
    char *filename;
    if (argc > 1 && strcmp(argv[1], "-test") == 0) 
    {
        filename = "../test_input.txt";
        printf("RUNNING IN TEST MODE\n");
    }
    else
        filename = "../input.txt";

    FILE *input = fopen(filename, "r");
    printf("Part 1: %d\n", solution(input, 1));
    printf("Part 2: %d\n", solution(input, 2));

    return 0;
}

int solution(FILE *input, int part)
{
    if (part != 1 && part != 2) 
        return EXIT_FAILURE;

    SubPosition position = {
        .horizontal = 0,
        .depth = 0,
        .aim = 0
    };

    for (int i = 0; !feof(input); i++)
    {
        char line_buffer[LINE_MAX] = {0};
        fgets(line_buffer, LINE_MAX - 1, input);

        SubDirection direction = parse_direction(line_buffer);

        if (part == 1)
            position = modify_position(position, direction);
        else if (part == 2)
            position = modify_position_complex(position, direction);
    }
    fseek(input, 0, SEEK_SET);

    return position.depth * position.horizontal;
}

SubPosition modify_position(SubPosition pos, SubDirection dir) 
{
    switch (dir.direction)
    {
    case FORWARD:  pos.horizontal += dir.magnitude;
                   break;
    case UP:       pos.depth -= dir.magnitude;
                   break;
    case DOWN:     pos.depth += dir.magnitude;
                   break;
    }

    return pos;
}

SubPosition modify_position_complex(SubPosition pos, SubDirection dir)
{
    switch (dir.direction)
    {
    case FORWARD:   pos.horizontal += dir.magnitude;
                    pos.depth += pos.aim * dir.magnitude;
                    break;
    case UP:        pos.aim -= dir.magnitude;
                    break;
    case DOWN:      pos.aim += dir.magnitude;
                    break;
    }

    return pos;
}

SubDirection parse_direction(char *direction_str)
{
    Directions direction;
    int magnitude; 
    
    switch (direction_str[0])
    {
    case 'f':  direction = FORWARD;  
               break;
    case 'd':  direction = DOWN;     
               break;
    case 'u':  direction = UP;       
               break;
    }

    magnitude = parse_magnitude(direction_str);
    
    SubDirection parsed = {
        .direction = direction,
        .magnitude = magnitude
    };

    return parsed;
}

int parse_magnitude(char *direction_str)
{
    char number_buffer[8] = {0};
    int buffer_index = 0;

    for (char *d = direction_str; *d; d++)
        if (isdigit(*d)) number_buffer[buffer_index++] = *d;

    return atoi(number_buffer);
}