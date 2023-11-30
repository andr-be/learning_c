// Advent of Code 2021 - Day 3 - Binary Diagnostic
// andr-be 11/2023
/*
    Perform some interesting binary analysis operations to work
    out what might be wrong with the submarine.

    P1: 4006064
    P2: 
*/

#include "binary.h"

int main(int argc, char const *argv[])
{
    char *filename;
    if (argc > 1 && strcmp(argv[1], "-test") == 0) 
    {
        filename = "../test_input.txt";
        printf("RUNNING IN TEST MODE\n");
    }
    else 
    {
        filename = "../input.txt";
    }

    FILE *input = fopen(filename, "r");
    printf("SOLUTIONS:\nPart 1: %d\nPart 2: %d\n", p1_solution(input), p2_solution(input));

    return 0;
}

int p1_solution(FILE *input)
{
    int total_lines = 0;
    char lines[MAX_LINES][MAX_LENGTH] = {0};
 
    while (!feof(input))
        fgets(lines[total_lines++], MAX_LENGTH, input);

    int gamma_array[MAX_LENGTH] = {0},
        gamma_rate_totals[MAX_LENGTH] = {0},
        epsilon_array[MAX_LENGTH] = {0},
        array_length = (int) strlen(lines[0]) - 1;

    for (int i = 0; i < total_lines; i++)
        for (int j = 0; j < MAX_LENGTH; j++)
            gamma_rate_totals[j] += (lines[i][j] == '1') ? 1 : 0; 

    for (int i = 0; i < array_length; i++) 
    {
        gamma_array[i] = (gamma_rate_totals[i] > total_lines / 2) ? 1 : 0;
        epsilon_array[i] = (gamma_array[i] == 1) ? 0 : 1;
    }

    int gamma = from_binary_array(gamma_array, array_length);
    int epsilon = from_binary_array(epsilon_array, array_length);

    return epsilon * gamma;
}

int p2_solution(FILE *input)
{
    int solution = 0;


    return solution;
}

int from_binary_array(int *array, int length)
{
    int result = 0;
    for (int i = 0; i < length; i++)
    {
        result <<= 1;
        result += array[i];
    }

    return result;
}

