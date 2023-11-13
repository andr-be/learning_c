// Chapter 13 - Exercise 3 - deal.c
// andr-be 11/2023
/*
    Changes the original form of the program and replaces the characters
    that originally denoted the cards with strings
*/

#include <stdbool.h>    // C99 only
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SUITS 4
#define NUM_RANKS 13

int main(void)
{
    bool in_hand[NUM_SUITS][NUM_RANKS] = {false};
    int num_cards, rank, suit;

    char *rank_name[] = { 
        "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", 
        "Nine", "Ten", "Jack", "Queen", "King", "Ace" 
    };

    char *suit_name[] = { 
        "Clubs", "Diamonds", "Hearts", "Spades" 
    };

    srand((unsigned) time(NULL));

    printf("Enter number of cards in hand: ");
    scanf("%d", &num_cards);

    printf("Your hand:\n");
    while (num_cards > 0) {
        suit = rand() % NUM_SUITS;  // picks a random suit
        rank = rand() % NUM_RANKS;  // picks a random rank
        if (!in_hand[suit][rank]) {
            in_hand[suit][rank] = true;
            num_cards--;
            printf("  %s of %s\n", rank_name[rank], suit_name[suit]);
        }
    }
    printf("\n");
    return 0;
}