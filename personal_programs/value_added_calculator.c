// VALUE ADDED TAX CALCULATOR
// andr-be 06/2023
/*
    This program is an experiment at writing a more efficient style of 
    main function, which I've achieved by encapsulating all functionality
    into functions.

    The best of these is probably the end_loop_prompt() function, and
    I'm quite proud of how well it appears to work. Another noteworthy
    addition is the definition of a NEW_LINE macro.
*/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define VAT_RATE 17.5f
#define NEW_LINE putchar('\n')

float get_input(void);
float calc_tax(float);
float round_to_2dp(float);
void print_totals(float, float, float);
bool end_loop_prompt(void);


int main(void){
    float pretax, tax_total, gross;
    bool loop = true;

    while (loop == true){
        pretax = get_input();
        tax_total = calc_tax(pretax);
        gross = pretax + tax_total;

        print_totals(pretax, tax_total, gross);
        loop = end_loop_prompt();
    }
}


float get_input(void){
    // prompts the user for a float input and 
    // rounds the response to 2 decimal places
    float input;

    printf("ENTER AN AMOUNT:   ");
    scanf("%f", &input);
    NEW_LINE;

    return round_to_2dp(input);
}

float calc_tax(float pretax){
    // works out the VAT based on a defined VAT_RATE
    return pretax * (VAT_RATE / 100);
}

float round_to_2dp(float input){
    // rounds any float to 2dp
    return roundf(input * 100.0f)/100.0f;
}

void print_totals(float pretax, float tax, float gross){
    // properly formats the output of the tax calculations
    printf("TOTAL            $%7.2f\n", pretax);
    printf("VAT (%0.2f %%)    $%7.2f\n", VAT_RATE, tax);
    printf("GROSS            $%7.2f\n", gross);
    NEW_LINE;
}

bool end_loop_prompt(void){
    // retuns false if the user wants to exit
    // returns true if they enter anything else
    char loop_prompt;

    fflush(stdin);
    printf("EXIT PROGRAM? (Y/N)  ");
    scanf("%c", &loop_prompt);
    NEW_LINE;

    if (loop_prompt == 'Y' || loop_prompt == 'y')
        return false;
    else
        return true;
}
