// BAD STRINGS
// andr-be 08/2023

#include <stdio.h>

#define EXIT_LOOP 0
#define CONTINUE_LOOP 1

#define POSITIVE 1
#define NEGATIVE -1

int bad_string_generator(void);

int main(void)
{
    while (bad_string_generator());
    return 0;
}

int bad_string_generator(void)
{
    printf("\nEnter a number to generate undefined text (0 to exit):  ");   
    int qty = 0;
    scanf("%d", &qty);
    int dir = POSITIVE;
   
    if (!qty || qty == 0) 
        return EXIT_LOOP;
    
    else if (qty < 0) { 
        dir = NEGATIVE; 
        qty *= -1;
    }
    
    char blank[1] = "", *p = blank;
    for (; p - blank < qty && blank - p < qty; p += dir)
        printf("%c ", *p);

    return CONTINUE_LOOP;
}