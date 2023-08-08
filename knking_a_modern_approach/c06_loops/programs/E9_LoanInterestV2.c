// LOAN REPAYMENT CALCULATOR V2
// andr-be 06/2023
/*
    Modified this in line with the new requirements when I did the original
    so instead I've just added an additional feature that tells you when 
    you've paid the loan off and stops printing the balance.
*/

#include <stdio.h>
#include <string.h>

float get_float(char*);
float payment(float, float, float, int);


int main(void)
{
    float balance = get_float("TOTAL LOAN BALANCE");
    float interest = get_float("ANNUAL INTEREST RATE");
    float monthly_payment = get_float("MONTHLY PAYMENT AMOUNT");
    float simulation_time = get_float("MONTHS TO SIMULATE");

    for (int month = 1; month < simulation_time + 1; month++) {
        balance = payment(balance, interest, monthly_payment, month);
        if (balance < 0) {
            printf("LOAN CLEARED AFTER %d MONTHS", month);
            break;
        }
    }
}

float get_float(char* prompt){
    float input;
    printf("%s:\t", prompt);
    scanf("%f", &input);
    return input;
}

float payment(float loan, float rate, float payment, int p_no){
    float monthly_rate_pct = (rate / 12) / 100;
    float interest = loan * monthly_rate_pct;
    float balance = loan - payment + interest;

    printf("BALANCE AFTER PAYMENT %d:\t$%.2f\n", p_no, balance);
    return balance;
}