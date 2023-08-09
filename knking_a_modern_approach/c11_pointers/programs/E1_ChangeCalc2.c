// DOLLAR BILL CHANGE CALCULATOR V2
// andr-be 2023
/*
    This version uses pointers!
*/

#include <stdio.h>

typedef struct {
    int twenties;
    int tens;
    int fives;
    int ones;
} change;

void print_change(change input);
void pay_amount(int dollars, int *twenties, int *tens, int *fives, int* ones);

int main(void){
    int input,
        twenties = 0, tens = 0, fives = 0, ones = 0;

    printf("Enter a Dollar amount to work out change:  ");
    scanf("%d", &input);

    pay_amount(input, &twenties, &tens, &fives, &ones);
    change c = {twenties, tens, fives, ones};
    print_change(c);
}

void print_change(change input) {
    printf("\n%d x $20s\n%d x $10s\n%d x $5s\n%d x $1s\n",
        input.twenties, input.tens, input.fives, input.ones);
}

void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *ones)
{
    for (; dollars >= 20; dollars -= 20) *twenties += 1;
    for (; dollars >= 10; dollars -= 10) *tens     += 1;
    for (; dollars >=  5; dollars -=  5) *fives    += 1;
    for (; dollars >=  1; dollars -=  1) *ones     += 1;
}
