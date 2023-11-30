// Advent of Code 2021 - Day 1 - Sonar Sweep
// andr-be 11/2023
/*
    Generates a set of local depth increases for a given sonar sweep
    P1: 1529
    P2: 1567
*/

#include "sonar.h"

int main(int argc, char const *argv[])
{
    int sonar_array[MAX_LINES], 
        array_length,
        p1_solution,
        p2_solution;

    char *filename;

    if (argc > 1 && strcmp(argv[1], "-test") == 0)
        filename = "../day_1_test.txt";
    else 
        filename = "../day_1.txt";

    FILE *puzzle_input = open_file(filename);

    array_length = create_sonar_array(puzzle_input, sonar_array);
    printf("%d lines processed...\n", array_length);
    printf(
        "SOLUTIONS:\nPart 1: %4d\tPart 2: %4d", 
        calculate_depth_increases(sonar_array, array_length), 
        calculate_depth_increase_window(sonar_array, array_length, WINDOW_SIZE)
    );

    return 0;
}

int create_sonar_array(FILE *file_pointer, int array_buffer[])
{
    int i;
    char line_buffer[LINE_MAX] = {0};
    for (i = 0; !feof(file_pointer); i++)
    {
        int range;
        fgets(line_buffer, MAX_LINES, file_pointer);
        range = atoi(line_buffer);
        array_buffer[i] = range;
    }
    return i;
}

int calculate_depth_increases(int sonar_array[], int length)
{
    int increases = 0;

    for (int i = 1; i < length; i++)
        if (sonar_array[i] > sonar_array[i - 1])
            increases++;

    return increases;
}

int calculate_depth_increase_window(int sonar_array[], int length, int window_size)
{
    int increases = 0,
        previous_sum = 0,
        current_sum;

    for (int i = window_size; i < length; i++) 
    {
        current_sum = 0;
    
        for (int j = 1; j <= window_size; j++)
            current_sum += sonar_array[i - j];

        if (current_sum > previous_sum && i != window_size)
            increases++; 
        
        previous_sum = current_sum;
    }

    return increases;
}