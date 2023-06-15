// LOOP TRAVERSAL BENCHMARKER
// andr-be 06/2023
/*
    This program is twinned with a python program I developed
    simultaneously to test the relative performance of the two
    programming langauges with a very simple task.

    Ultimately more of an experiement in looping and time reading;
    I'm fairly happy with the time_as_str() function but in general
    I'm not really sure why it does what it does.
*/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITER 10000000

char* time_as_str(void)
{
    time_t raw_start_time;
    struct tm *rst;
    char start_time_string[80], *string;
    string = malloc(sizeof(char) * 80);

    time ( &raw_start_time );
    rst = localtime( &raw_start_time );
    strftime(string, 80, "%X", rst);

    return string;
}

int main(void)
{
    printf("%s\n", time_as_str());

    clock_t start_time = clock();

    for (int i = 1; i < MAX_ITER; ++i) {
        if (i % 100000 == 0){
            clock_t current_time = clock();
            double elapsed_time = difftime(current_time, start_time) / CLOCKS_PER_SEC;
            double loops_per_second = i / elapsed_time;
            printf("%7d: %s LPS: %.2f\n", i, time_as_str(), loops_per_second);
        }
    }

    clock_t end_time = clock();
    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    double avg_lps = MAX_ITER / total_time;

    printf ("%d loops run in %fs\n", MAX_ITER, total_time);
    printf("avg = %.2f loops per second\n", avg_lps);

    return 0;
}