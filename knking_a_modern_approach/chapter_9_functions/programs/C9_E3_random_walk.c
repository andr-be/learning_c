// RANDOM ARRAY WALKER
// andr-be 07/2023
/*
    refactored to structure the program into two main functions,
    generate_random_walk and print_array
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// holds the position of the walker
typedef struct Pos {
    int col;
    int row;
} Pos;

// translates integers to directions
typedef enum Dir
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} Dir;

void generate_random_walk(char walk[10][10]);
void print_array(char walk[10][10]);

int main(void)
{
    char walk[10][10] = {0};
    generate_random_walk(walk);
    print_array(walk);

    return 0;
}

void generate_random_walk(char walk[10][10]){
    Pos w = {0, 0};
    srand((unsigned) time(NULL));

    // construct empty array
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            walk[i][j] = '.';

    // for every character from A to Z
    for (char i = 'A'; i <= 'Z'; i++)
    {
        // record current position
        walk[w.row][w.col] = i;

        // find all remaining valid moves
        int valid_moves = 0;
        bool can_move[4] = { false };
        if (w.row > 0 && walk[w.row-1][w.col] == '.') { can_move[UP]    = true; valid_moves += 1; }  
        if (w.row < 9 && walk[w.row+1][w.col] == '.') { can_move[DOWN]  = true; valid_moves += 1; }
        if (w.col > 0 && walk[w.row][w.col-1] == '.') { can_move[LEFT]  = true; valid_moves += 1; }
        if (w.col < 9 && walk[w.row][w.col+1] == '.') { can_move[RIGHT] = true; valid_moves += 1; }
        
        // exit loop with message if none remaining 
        if (valid_moves == 0) { printf("UNABLE TO FINISH PATH; %c REACHED\n", i); break; }

        // make a random choice
        int choice = rand() % 4;

        // re-roll choice until it's valid
        while (can_move[choice] == false)
            choice = rand() % 4;

        // change position and end loop
        switch (choice)
        {
        case UP:    w.row -= 1; break;
        case DOWN:  w.row += 1; break;
        case LEFT:  w.col -= 1; break;
        case RIGHT: w.col += 1; break;

        default: break;
        }
    }
}

void print_array(char walk[10][10]){
    // print array
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c  ", walk[i][j]);
        }
        putchar('\n');
    }
}