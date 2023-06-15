// LOAN REPAYMENT CALCULATOR
// andr-be 06/2023
/*
    This is probably the most elegant way I've retrieved user values.
    A single function, with the ability to display multiple prompts
    depending on a string input. Lovely.

    The entire program operation is dependent on user input!
*/

#include <stdio.h>

float get_float(char*);
float payment(float, float, float, int);


int main(void)
{
    float balance = get_float("TOTAL LOAN BALANCE");
    float interest = get_float("ANNUAL INTEREST RATE");
    float monthly_payment = get_float("MONTHLY PAYMENT AMOUNT");
    float simulation_time = get_float("MONTHS TO SIMULATE");

    for (int month = 1; month < simulation_time + 1; month++)
        balance = payment(balance, interest, monthly_payment, month);
}

float get_float(char* prompt){
    float input;
    printf("%s:\t", prompt);
    scanf("%g", &input);
    return input;
}

float payment(float loan, float rate, float payment, int p_no){
    float monthly_rate_pct = (rate / 12) / 100;
    float interest = loan * monthly_rate_pct;
    float balance = loan - payment + interest;

    printf("BALANCE AFTER PAYMENT %d:\t$%9.2f\n", p_no, balance);
    return balance;
}