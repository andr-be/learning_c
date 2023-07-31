// SEVEN SEGMENT ASCII
// andr-be 07/2023
/*
    Enter a number: 491-9014
         _       _   _      
    |_| |_|   | |_| | |   | |_|    
      |  _|   |  _| |_|   |   |   
    
*/

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_DIGITS 10

int get_input_and_total(int a[]);
void display_number(int total, int numbers[total]);

const char segments[10][3][3] = {
   {{' ', '_', ' '}, {'|', ' ', '|'}, {'|', '_', '|'}},  // 0: segments[0][0][0] -> [0][2][2]
   {{' ', ' ', ' '}, {' ', ' ', '|'}, {' ', ' ', '|'}},  // 1
   {{' ', '_', ' '}, {' ', '_', '|'}, {'|', '_', ' '}},  // 2
   {{' ', '_', ' '}, {' ', '_', '|'}, {' ', '_', '|'}},  // 3
   {{' ', ' ', ' '}, {'|', '_', '|'}, {' ', ' ', '|'}},  // 4
   {{' ', '_', ' '}, {'|', '_', ' '}, {' ', '_', '|'}},  // 5
   {{' ', '_', ' '}, {'|', '_', ' '}, {'|', '_', '|'}},  // 6
   {{' ', '_', ' '}, {' ', ' ', '|'}, {' ', ' ', '|'}},  // 7
   {{' ', '_', ' '}, {'|', '_', '|'}, {'|', '_', '|'}},  // 8
   {{' ', '_', ' '}, {'|', '_', '|'}, {' ', ' ', '|'}}   // 9: segments[9][0][0] -> [9][2][2]
};

int main(void)
{
    int  numbers[MAX_DIGITS],
         total = get_input(numbers);

    display_number(total, numbers);
    return 0;
}

int get_input_and_total(int a[])
{
    char input[MAX_DIGITS + 1],
         prompt[17] = "Enter a number: ";

    int total = 0;

    printf("%s", prompt);
    fgets(input, MAX_DIGITS, stdin);

    for (int i = 0; i < MAX_DIGITS && input[i] != 'n'; i++)
        if (isdigit(input[i])) {
            a[total] = input[i] - '0';
            total++;
        } 
    
    return total;
}

void display_number(int total, int numbers[total])
{
    for (int row = 0; row < 3; row++) {
        for (int num = 0; num <= total; num++) {
            for (int segment = 0; segment < 3; segment++) {
                printf("%c", segments[numbers[num]][row][segment]);
            }
            putchar(' ');
        }
        putchar('\n');
    }
}