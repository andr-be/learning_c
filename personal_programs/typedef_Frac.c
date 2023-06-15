// FRACTION CALCULATOR V2
// andr-be 06/2023
/*
    This program will perform basic arithmetic operations on fractions through
    use of an interactive shell.

    It can also simplify most fractions given to it.

    NOTES:  - all fractions given must be in the form `int/int`
            - not all functionality has been tested extensively
            - if you forget the comma in between fractions it doesn't work

    TODO:   - function to simplify improper fractions
            - revamp menu to simply accept parsed operations
                i.e. (`ENTER QUERY: 1/6 + 1/6 [..] RESULT: 1/3`)
*/

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#define DELAY_1S     Sleep(1000)
#define DELAY_10MS   Sleep(10)

typedef struct {
    int numerator;
    int denominator;
} Fraction;

typedef enum {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
} Operation;

int main_menu(void);
void print_frac(Fraction);

Fraction simplify_frac(Fraction);
Fraction do_operation(Operation);
Fraction get_fraction(void);
Fraction* get_two_fractions(Fraction*);

int main(void)
{
    bool loop = true;
    Operation operation;
    Fraction result;
    printf("\nFRACTION CALCULATOR\n// andr-be 2023");
    DELAY_1S;
    while (loop == true)
    {
        fflush(stdin);
        switch (main_menu()) {
            case 1: operation = ADDITION; break;
            
            case 2: operation = SUBTRACTION; break;
            
            case 3: operation = MULTIPLICATION; break;
            
            case 4: operation = DIVISION; break;
           
            case 5:
                result = simplify_frac(get_fraction());
                print_frac(result);
                fflush(stdin);
                continue;

            case -1:
                loop = false;
                printf("EXITING PROGRAM\n");
                DELAY_1S;
                continue;

            default:
                break;
        }
        result = do_operation(operation);
        print_frac(result);
    }
    return 0;
}

int main_menu(void){
    int choice; 
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

void print_frac(Fraction input){
    printf("\nRESULT: %d/%d\n", input.numerator, input.denominator);
}

Fraction simplify_frac(Fraction input){
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
    Fraction result = {temp_num, temp_dom};
    return result;
}

Fraction do_operation(Operation operation)
{
    // initialise a blank fraction array, then mutate it with user input
    Fraction inputs[2];
    get_two_fractions(inputs);
    // the first and second fractions are destructured
    Fraction input_lhs = inputs[0], input_rhs = inputs[1];

    // initialise the result fraction elements, and a scaling m_factor
    int r_numerator = 0, r_denominator = 1, m_factor = 1;
    switch (operation)
    {
    case ADDITION:
        // add the m_products of the lhs top and rhs bottom, and the rhs top and the lhs bottom
        r_numerator = input_lhs.numerator * input_rhs.denominator 
                    + input_rhs.numerator * input_lhs.denominator;
        // multiply the two bottoms together
        r_denominator = input_lhs.denominator * input_rhs.denominator;
        break;

    case MULTIPLICATION:
        // multiply the tops by tops
        r_numerator = input_lhs.numerator * input_rhs.numerator;
        // and the bottoms by the bottoms
        r_denominator = input_lhs.denominator * input_rhs.denominator;
        break;
    
    case SUBTRACTION:
        // select the biggest denominator to multiply the other factors by
        if (input_lhs.denominator > input_rhs.denominator)
            m_factor = input_lhs.denominator;
        else
            m_factor = input_rhs.denominator;

        // scale the top plus the top and the bottom multiplied by the bottom
        r_numerator = m_factor * (input_lhs.numerator + input_rhs.numerator);
        r_denominator = m_factor * (input_rhs.denominator * input_rhs.denominator);
        break;

    case DIVISION:
        // flips the right hand side fraction upside down and then multiplies normally
        Fraction temporary = {input_rhs.denominator, input_rhs.numerator};
        // top by top, bottom by bottom
        r_numerator = input_lhs.numerator * temporary.numerator;
        r_denominator = input_lhs.denominator * temporary.denominator;
        break;
    
    default:
        break;
    }
    Fraction result =  {r_numerator, r_denominator};
    return simplify_frac(result);
}

Fraction get_fraction(void){
    int numerator, denominator;

    printf("ENTER FRACTION: ");
    scanf("%d/%d", &numerator, &denominator);

    Fraction result = {numerator, denominator};
    return result;
}

Fraction* get_two_fractions(Fraction* array){
    Fraction f1 = {0}, f2 = {0}; 

    printf("ENTER TWO FRACTIONS (x/y, a/b): ");
    scanf("%d/%d , %d/%d", 
        &f1.numerator, &f1.denominator, 
        &f2.numerator, &f2.denominator
    );

    array[0] = f1; 
    array[1] = f2;
    return array;
}