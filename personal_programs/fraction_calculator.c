// FRACTION CALCULATOR
// andr-be 06/2023
/*
    This program will perform basic arithmetic operations on fractions through
    use of an interactive shell.
    It can also simplify any fraction given to it.

    CAVEATS:    - all fractions given must be in the form `int/int`
                - not all functionality has been tested extensively
*/

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#define DELAY_1S     Sleep(1000)
#define DELAY_100MS  Sleep(100)
#define DELAY_10MS   Sleep(10)

struct Frac {
    int numerator;
    int denominator;
};
enum Op {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
};

int main_menu(void);
void print_frac(struct Frac);
struct Frac get_fraction(void);
struct Frac simplify_frac(struct Frac);
struct Frac do_operation(struct Frac, struct Frac, enum Op);

int main(void)
{
    bool loop = true;
    enum Op operation;
    struct Frac fraction_1, fraction_2, result;
    printf("\nFRACTION CALCULATOR");
    DELAY_1S;
    while (loop == true)
    {
        fflush(stdin);
        switch (main_menu()) {
            case 1:
                operation = ADDITION;   
                break;
            case 2:
                operation = SUBTRACTION;
                break;
            case 3:
                operation = MULTIPLICATION;
                break;
            case 4:
                operation = DIVISION;
                break;
            case 5:
                result = simplify_frac(get_fraction());
                print_frac(result);
                fflush(stdin);
                continue;
            case -1:
                loop = false;
                printf("EXITING PROGRAM\n");
                continue;
            default:
                break;
        }
        fraction_1 = get_fraction();
        fraction_2 = get_fraction();
        result = do_operation(fraction_1, fraction_2, operation);
        print_frac(result);
    }
    return 0;
}

int main_menu(void){
    int choice; 
    DELAY_100MS;
    printf("\n 1: ADD");        DELAY_10MS;
    printf("\n 2: SUBTRACT");   DELAY_10MS;
    printf("\n 3: MULTIPLY");   DELAY_10MS;
    printf("\n 4: DIVIDE");     DELAY_10MS;
    printf("\n 5: SIMPLIFY");   DELAY_10MS;
    printf("\n-1: EXIT\n");     DELAY_10MS;
    printf("ENTER A CHOICE:  ");
    scanf("%d", &choice);
    return choice;
}

struct Frac simplify_frac(struct Frac input){
    int temp_num = input.numerator, temp_dom = input.denominator;

    // test every number lower than the denominator
    for (int test_div = input.denominator; test_div > 1; test_div--)
    {
        // if both numbers divide equally into the test divisor, update temps
        if ((input.numerator % test_div == 0)
        &&  (input.denominator % test_div == 0))
        {
            temp_num = input.numerator / test_div;
            temp_dom = input.denominator / test_div;
            break;
        }
    }
    struct Frac result = {temp_num, temp_dom};
    return result;
}

struct Frac do_operation(struct Frac input1, struct Frac input2, enum Op operation)
{
    int r_numerator = 0, r_denominator = 1, factor;
    switch (operation)
    {
    case ADDITION:
        DELAY_10MS;
        r_numerator = input1.numerator * input2.denominator + input2.numerator * input1.denominator;
        r_denominator = input1.denominator * input2.denominator;
        break;

    case MULTIPLICATION:
        DELAY_10MS;
        r_numerator = input1.numerator * input2.numerator;
        r_denominator = input1.denominator * input2.denominator;
        break;
    
    case SUBTRACTION:
        DELAY_10MS;
        if (input1.denominator > input2.denominator)
            factor = input1.denominator;
        else
            factor = input2.denominator;
        r_numerator = factor * (input1.numerator + input2.numerator);
        r_denominator = factor * (input2.denominator * input2.denominator);
        break;

    case DIVISION:
        DELAY_10MS;
        struct Frac temporary = {input2.denominator, input2.numerator};
        r_numerator = input1.numerator * temporary.numerator;
        r_denominator = input1.denominator * temporary.denominator;
        break;
    
    default:
        break;
    }
    struct Frac result =  {r_numerator, r_denominator};
    return simplify_frac(result);
}

struct Frac get_fraction(void){
    int numerator, denominator;

    printf("ENTER FRACTION: ");
    scanf("%d/%d", &numerator, &denominator);

    struct Frac result = {numerator, denominator};
    return result;
}

void print_frac(struct Frac input){
    printf("\nRESULT: %d/%d\n", input.numerator, input.denominator);
}
