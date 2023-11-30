#include "file_io.h"

#define MAX_LINES 2500

#define WINDOW_SIZE 3

int create_sonar_array(FILE *file_pointer, int array_buffer[]);
int calculate_depth_increases(int sonar_array[], int length);
int calculate_depth_increase_window(int sonar_array[], int length, int window);