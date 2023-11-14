// NUMBERWANG2
// andr-be 11/2023
/*
    Replaced the insane switch-maze with a slightly less insane string collection.
    This is sort of hacky, but it functions just as effectively as the previous version.
*/

#include <stdio.h>
#include <string.h>

int get_input(void);
void print_to_word_s(int input);

int main(void)
{
    for(;;)
    {
        int input = get_input();
        if (input == 0) break;
        printf("You entered the number:  ");
        print_to_word_s(input);
        putchar('\n');
    }
    return 0;
}

/// @brief Asks the user for a two digit number
/// @return a number entered by the user, modded to between 0 and 100
int get_input(void)
{
    int input;
    printf("Enter a two digit number: ");
    scanf("%d", &input);
    return input % 100;
}

/// @brief prints out the input 2 digit number in word form (can handle 1 digit but badly)
/// @param input a number between 1 and 99 (inclusive)
void print_to_word_s(int input) 
{
    const char *EARLY_S[] = { 
        "ten", "eleven", "twelve", 
        "thirteen", "fourteen", "fifteen", 
        "sixteen", "seventeen", "eighteen", 
        "nineteen", 
    };

    const char *TENS_S[] = {
        "", "twenty", "thirty", 
        "fourty", "fifty", "sixty", 
        "seventy", "eighty", "ninety" 
    };

    const char *ONES_S[] = {
        "", "-one", "-two", 
        "-three", "-four", "-five", 
        "-six", "-seven", "-eight", 
        "-nine" 
    };

    if (input < 10) {
        printf("%s", ONES_S[input]);
    } 
    else if (input >= 10 && input < 20) {
        printf("%s", EARLY_S[input - 10]);
    } 
    else {
        printf("%s", TENS_S[(input / 10) - 1]);
        printf("%s", ONES_S[(input % 10)]);
    }
}

