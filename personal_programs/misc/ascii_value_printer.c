// ASCII VALUE PRINTER
// andr-be 06/2023
/*
    This program will provide you with what I believe to be the ASCII value
    any any character you type into it.
    Once you type '!', the program goes into its shutdown routine and end.
*/

#include <stdio.h>
#include <windows.h>

int intro(void);
int value_gen(void);
int exit_sequence(void);

int main(void)
{
    intro();
    value_gen();
    exit_sequence();
}

int intro(void)
{
    printf("WELCOME TO THE NUMBER TO VALUE MACHINE\n");
    printf("ENTER A CHARACTER TO GET ITS VALUE!\n");
    printf("ENTER ! TO EXIT\n\n");
}

int value_gen(void)
{
    char i; 
    char *p = &i;
    while (i != '!') 
    {
        scanf("%c", p);                   // pretend you typed 12
        printf("you entered: %c\n", i);    // prints "i is 12"
        int j = (int)*p;
        printf
        ("that value in ASCII is: %d!\n", j);
        fflush(stdin);                     // clear stdin after taking 1 char
    }
}

int exit_sequence(void)
{
    printf("\nExiting!\n");
    for (int k = 0; k < 14; k++)
    {
        printf("/ ");
        Sleep(100);
    }
    putchar('\n');
}