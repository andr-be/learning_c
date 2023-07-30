// CRAPS SIMULATOR
// andr-be 07/2023
/*
    Simulates the dice game 'Craps', which is played with two dice.

    On the first roll, the player wins if the sum of the dice is 7 or 11.
    The player loses if the sum is 2, 3, or 12.
    Any other roll is called the "point" and the game continues.

    On each subsequent roll, the player wins if he or she rolls the "point" again.
    The player loses by rolling 7. Any other roll is ignored and the game continues.

    When the game ends, the program will ask the user if they want to play again
    if user enters a response other than Y, number of wins and losses is displayed
*/
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

int roll_dice(void);
bool play_game(void);

int main(void)
{
    srand((unsigned) time(NULL));
    int wins = 0, losses = 0;
    double ratio = 0;
    char response;

    for(;;){
        if (play_game()) wins++;
        else losses++;

        printf("\nPlay again? ");
        scanf("%c", &response);
        if (toupper(response) != 'Y') break;
        fflush(stdin);
    }
    printf("\nWINS: %d\tLOSSES: %d\n", wins, losses);
    ratio = (double) wins / (double) losses;
    printf("W/L RATIO: %lf\n", ratio);
}

int roll_dice(void) {
    return rand() % 5 + 1;
}

bool play_game(void)
{
    int dice_1 = roll_dice(),
        dice_2 = roll_dice(),
        total = dice_1 + dice_2,
        point;

    printf("You rolled: %d & %d\n", dice_1, dice_2);

    switch (total)
    {
    case  7: 
    case 11: printf("You win!\n");
             return true;

    case  2: 
    case  3: 
    case 12: printf("You lose!\n");
             return false;

    default: printf("Your point is %d\n", total);
             point = total;
    }

    for(;;){
        dice_1 = roll_dice();
        dice_2 = roll_dice();
        total = dice_1 + dice_2;
        printf("You rolled: %d & %d\n", dice_1, dice_2);

        if (total == point) { printf("You win!\n"); return true; }
        if (total == 7)     { printf("You lose!\n"); return false; }
        
        printf("No dice.\n");
    }
}