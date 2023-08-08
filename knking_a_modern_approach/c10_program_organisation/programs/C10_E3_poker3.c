// NON-EXTERNAL VARIABLE POKER
// andr-be 07/2023
/*
    Remove the num_in_rank, num_in_suit and card_exists arrays from
    the program and replace the card storage with a 5x2 array instead
    each row of the array will represent a card
    e.g. if the array is named hand:
     - hand[0][0] will store the rank of card 1
     - hand[0][1] will store the suit of card 1
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

// external variables
int hand[NUM_CARDS][2];
bool straight, flush, four, three;
int pairs;  // can be 0, 1, or 2

// prototypes
void read_cards(void);
void analyse_hand(void);
void print_result(void);
void selection_sort(int n, int a[n]);
bool has_straight(int ranks[]);
int x_of_a_kind(int n, int a[n]);
int count_pairs(int n, int a[n]);
bool is_consec(int n, int a[n]);

// calls the three main functions in a loop
int main(void)
{
    for (;;) {
        read_cards();
        analyse_hand();
        print_result();
    }
}

// reads the cards into ext. vars, checks for and rejects bad/duplicate cards
void read_cards(void)
{
    char ch, rank_ch, suit_ch;
    int rank, suit;
    bool bad_card;
    int cards_read = 0;

    // converts user input to cards, updates totals
    while (cards_read < NUM_CARDS) {
        bad_card = false;

        printf("Enter a card: ");

        // converts the first char into a rank        
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

        // converts the second char into a suit
        suit_ch = (char) getchar();
        switch (suit_ch) {
            case 'c': case 'C': suit = 0; break;
            case 'd': case 'D': suit = 1; break;
            case 'h': case 'H': suit = 2; break;
            case 's': case 'S': suit = 3; break;
            default:            bad_card = true;
        }

        // checks to the end of the line for validity
        while ((ch = (char) getchar()) != '\n')
            if (ch != ' ') bad_card = true;

        // checks for duplicates
        for (int i = 0; i < cards_read; i++) {
            if (hand[i][0] == rank && hand[i][1] == suit) {
                printf("Duplicate - ");
                bad_card = true;
            }
        }

        // checks the bad_card flag
        if (bad_card) {
            printf("Bad card; ignored.\n");
            continue;
        }

        // if there are no errors, update totals
        hand[cards_read][0] = rank;
        hand[cards_read][1] = suit;
        cards_read++;
    }
}

// determines whether the hand contains a valuable result, stores into ext. vars
void analyse_hand(void)
{
    int ranks[NUM_CARDS] = {0};
    straight = false;
    flush = false;
    four = false;
    three = false;
    pairs = 0;

    // check every card, if it doesn't match the current suit, change suits and start again
    // if you're on the last card and all suits match, you have a flush
    for (int card = 0, suit = 0; card < NUM_CARDS && suit < NUM_SUITS; card++){
        if (hand[card][1] != suit) { 
            suit++; 
            card = 0; 
        }

        if (card == NUM_CARDS - 1) {
            flush = true;
            break;
        }
    }

    // build an array of ranks
    for (int card = 0; card < NUM_CARDS; card++){
        ranks[card] = hand[card][0];
    }

    // finds out if ranks contains a straight
    if (has_straight(ranks)) {
        straight = true;
        return;
    }

    switch (x_of_a_kind(NUM_CARDS, ranks))
    {
    case 4: four = true; break;
    case 3: three = true; break;

    default: break;
    }

    pairs = count_pairs(NUM_CARDS, ranks);
}

// notifies the user of the result, using the ext. vars set by analyse_hand
void print_result(void)
{
    if (straight && flush)  printf("Straight Flush!");
    else if (four)          printf("Four of a Kind!");
    else if (three && 
             pairs > 1)     printf("Full house!");
    else if (flush)         printf("Flush!");
    else if (straight)      printf("Straight!");
    else if (three)         printf("Three of a Kind!");
    else if (pairs == 2)    printf("Two Pairs!");
    else if (pairs == 1)    printf("Pair.");
    else                    printf("High card...");

    printf("\n\n");
}

bool has_straight(int ranks[]) 
{
    // sort into order
    selection_sort(NUM_CARDS, ranks);
    
    // check each element is only 1 away from the next
    return is_consec(NUM_CARDS, ranks);
}

void selection_sort(int n, int a[n])
{
    int b_index = 0, last;

    // if there's only one element or fewer, return
    if (n <= 1) return;

    // find the biggest element, store its index
    for (int i = 0; i < n; i++)
        b_index = a[i] > a[b_index] ? i : b_index;

    // take the last element, swap it with the biggest
    last = a[--n];
    a[n] = a[b_index];
    a[b_index] = last;

    // recurse; sort will end when only one element is unsorted
    selection_sort(n, a);
}

bool is_consec(int n, int a[n])
{
    for (int i = 0; i < n - 1; i++)
        if (a[i + 1] - a[i] != 1) return false; 

    return true;
}

int x_of_a_kind(int n, int a[n]) 
{
    int x = 0, max = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (a[i] == a[j]) 
                x++;
        
        max = (x > max) ? x : max;
        x = 0;
    }
    return max;
}

// counts pairs of posiive numbers in an array of length n
int count_pairs(int n, int a[n])
{
    int found_pairs = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++)
            if (a[i] == a[j] && a[i] > -1 && a[j] > -1) {
                found_pairs++; 
                a[i] = a[j] = -1;
                break;
            }
    }

    return found_pairs;
}