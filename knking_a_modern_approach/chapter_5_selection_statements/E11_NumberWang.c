// NUMBERWANG
// andr-be 06/2023
/*
    I had planned this program to have some sort of string 
    composition element, but honestly I have absolutely
    no idea how to achieve that without getting horrible
    errors.

    Instead, I just calculate and print in place. No returning
    of data, pure side effect programming >:)
*/

#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 128

int get_input(void);
int print_to_word(int);

int main(void) {
    while(1){
        int input = get_input();
        printf("You entered the number:  ");
        print_to_word(input);
        putchar('\n');
    }
    return 0;
}

int get_input(void){
    int input;
    printf("Enter a two digit number: ");
    scanf("%2d", &input);
    return input;
}
int print_to_word(int input){
    char* tens[BUFF_SIZE/2];
    char* ones[BUFF_SIZE/2];
    // early return the special cases
    switch (input)
    {
    case 10: printf("ten");       return 0;
    case 11: printf("eleven");    return 0;
    case 12: printf("twelve");    return 0;
    case 13: printf("thirteen");  return 0;
    case 14: printf("fourteen");  return 0;
    case 15: printf("fifteen");   return 0;
    case 16: printf("sixteen");   return 0;
    case 17: printf("seventeen"); return 0;
    case 18: printf("eighteen");  return 0;
    case 19: printf("nineteen");  return 0;
    default: break;
    }
    // find the 10s column, add it to a string
    switch (input / 10)
    {
    case 2: *tens = "twenty";  break;
    case 3: *tens = "thirty";  break;
    case 4: *tens = "fourty";  break;
    case 5: *tens = "fifty";   break;
    case 6: *tens = "sixty";   break;
    case 7: *tens = "seventy"; break;
    case 8: *tens = "eighty";  break;
    case 9: *tens = "ninety";  break;
    }
    // copy that string to a holding variable
    printf("%s", *tens);
    // find the 1s column, add it to a string
    switch (input % 10)
    {
    case 0:  return 0;
    case 1:  *ones = "-one";   break;
    case 2:  *ones = "-two";   break;
    case 3:  *ones = "-three"; break;
    case 4:  *ones = "-four";  break;
    case 5:  *ones = "-five";  break;
    case 6:  *ones = "-six";   break;
    case 7:  *ones = "-seven"; break;
    case 8:  *ones = "-eight"; break;
    case 9:  *ones = "-nine";  break;
    }
    // concatenate the ones onto the tens in composite_word
    printf("%s", *ones);
    return 0;
}