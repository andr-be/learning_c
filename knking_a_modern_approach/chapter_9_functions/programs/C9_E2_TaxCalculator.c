// TAX CALCULATOR
// andr-be 06/2023
/*
    The question wanted me to restructure the program such that
    the calculation was performed in a function. Fortunately, I've
    already done that, so this is already finished.
*/

#include <stdio.h>

float get_income(void);
float calculate_tax(float);
void  display_tax(float);

int main(void)
{
    while(1) {
        float income = get_income();
        float tax_due = calculate_tax(income);
        display_tax(tax_due);
    }
    return 0;
}

float get_income(void){
    float income;
    printf("Please enter your taxable income:  ");
    scanf("%f", &income);
    return income;
}

float calculate_tax(float income) {
    float tax_due;
    if      (income <  750.00f)  tax_due =  0.01f *  income;
    else if (income < 2250.00f)  tax_due =  0.02f * (income -  750.00f) +   7.50f;
    else if (income < 3750.00f)  tax_due =  0.03f * (income - 2250.00f) +  37.50f;
    else if (income < 5250.00f)  tax_due =  0.04f * (income - 3750.00f) +  82.50f;
    else if (income < 7000.00f)  tax_due =  0.05f * (income - 5250.00f) + 142.50f;
    else                         tax_due =  0.06f * (income - 7000.00f) + 230.00f;
    return tax_due;
}

void display_tax(float tax_due) {
    printf("Total tax due is %8.2f", tax_due);
}
