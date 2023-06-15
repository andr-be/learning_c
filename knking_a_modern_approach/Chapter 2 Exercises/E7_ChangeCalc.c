// DOLLAR BILL CHANGE CALCULATOR
// andr-be 2023

#include <stdio.h>

struct change {
    int twenties;
    int tens;
    int fives;
    int ones;
};

struct change calculate(int input) {
    struct change x = {0};

    while (input >= 20) { 
        x.twenties++; 
        input -= 20;
    }
    while (input >= 10) { 
        x.tens++;     
        input -= 10; 
    }
    while (input >= 5)  { 
        x.fives++;    
        input -= 5; 
    }
    while (input >= 1)  { 
        x.ones++;     
        input -= 1; 
    }

    return x;
}

void print_change(struct change input) {
    printf("\n%d x $20s\n%d x $10s\n%d x $5s\n%d x $1s\n",
        input.twenties, input.tens, input.fives, input.ones);
}

int main(void){
    int input;
    printf("Enter a Dollar amount to work out change:  ");
    scanf("%d", &input);

    struct change c = calculate(input);
    print_change(c);
}