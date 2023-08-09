// POKER POINTER
// andr-be 08/2023
/*
    Redesigned poker.c to no longer rely on external variables
    now it works by shuffling pointers to the same variables but
    this time they're instead contained within main()
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

// prototypes
void read_cards(int *, int *);
void analyse_hand(int *, int *, bool *, bool *, bool *, bool *, int *);
void print_result(bool *, bool *, bool *, bool *, int *);

// calls the three main functions in a loop
int main(void)
{
    int num_in_rank[NUM_RANKS];
    int num_in_suit[NUM_SUITS];
    bool straight, flush, four, three;
    int pairs;

    for (;;) {
        read_cards(num_in_rank, num_in_suit);
        analyse_hand(num_in_rank, num_in_suit, &straight, &flush, &four, &three, &pairs);
        print_result(&straight, &flush, &four, &three, &pairs);
    }
}

// reads the cards into ext. vars, checks for and rejects bad/duplicate cards
void read_cards(int* num_in_rank, int* num_in_suit)
{
    bool card_exists[NUM_RANKS][NUM_SUITS];
    char ch, rank_ch, suit_ch;
    int rank, suit;
    bool bad_card;
    int cards_read = 0;

    for (rank = 0; rank < NUM_RANKS; rank++) {
        num_in_rank[rank] = 0;
        for (suit = 0; suit < NUM_SUITS; suit++)
            card_exists[rank][suit] = false;
    }

    for (suit = 0; suit < NUM_SUITS; suit++)
        num_in_suit[suit] = 0;

    while (cards_read < NUM_CARDS) {
        bad_card = false;

        printf("Enter a card: ");

        rank_ch = (char) getchar();
        switch (rank_ch) {
            case '0':           exit(EXIT_SUCCESS);
            case '2':           rank =  0; break;
            case '3':           rank =  1; break;
            case '4':           rank =  2; break;
            case '5':           rank =  3; break;
            case '6':           rank =  4; break;
            case '7':           rank =  5; break;
            case '8':           rank =  6; break;
            case '9':           rank =  7; break;
            case 't': case 'T': rank =  8; break;
            case 'j': case 'J': rank =  9; break;
            case 'q': case 'Q': rank = 10; break;
            case 'k': case 'K': rank = 11; break;
            case 'a': case 'A': rank = 12; break;
            default:            bad_card = true;
        }

        suit_ch = (char) getchar();
        switch (suit_ch) {
            case 'c': case 'C': suit = 0; break;
            case 'd': case 'D': suit = 1; break;
            case 'h': case 'H': suit = 2; break;
            case 's': case 'S': suit = 3; break;
            default:            bad_card = true;
        }

        while ((ch = (char) getchar()) != '\n')
            if (ch != ' ') bad_card = true;

        if (bad_card)
            printf("Bad card; ignored.\n");
        else if (card_exists[rank][suit])
            printf("Duplicate card; ignored.\n");
        else {
            num_in_rank[rank]++;
            num_in_suit[suit]++;
            card_exists[rank][suit] = true;
            cards_read++;
        }
    }
}

// determines whether the hand contains a valuable result, stores into ext. vars
void analyse_hand(int* num_in_rank, int* num_in_suit, bool *straight, bool *flush, bool *four, bool *three, int* pairs)
{
    int num_consec = 0;
    int rank, suit;
    *straight = false;
    *flush = false;
    *four = false;
    *three = false;
    *pairs = 0;

    // check for flush
    for (suit = 0; suit < NUM_SUITS; suit++)
        if (num_in_suit[suit] == NUM_CARDS)
            *flush = true;

    // check for straight
    rank = 0;
    while (num_in_rank[rank] == 0) rank++;
    for (; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
        num_consec++;
    if (num_consec == NUM_CARDS) {
        *straight = true;
        return;
    }

    // check for 4-of-a-kind, 3-of-a-kind and pairs
    for (rank = 0; rank < NUM_RANKS; rank++) {
        if (num_in_rank[rank] == 4) *four = true;
        if (num_in_rank[rank] == 3) *three = true;
        if (num_in_rank[rank] == 2) *pairs += 1;
    }
}

// notifies the user of the result, using the ext. vars set by analyse_hand
void print_result(bool *straight, bool *flush, bool *four, bool *three, int* pairs)
{
    if (*straight && *flush) printf("Straight Flush!");
    else if (*four)          printf("Four of a Kind!");
    else if (*three && 
             *pairs == 1)    printf("Full house!");
    else if (*flush)         printf("Flush!");
    else if (*straight)      printf("Straight!");
    else if (*pairs == 2)    printf("Two Pairs!");
    else if (*pairs == 1)    printf("Pair.");
    else                     printf("High card...");

    printf("\n\n");
}