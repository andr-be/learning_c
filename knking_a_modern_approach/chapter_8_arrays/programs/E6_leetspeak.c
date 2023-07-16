// LEETSPEAK CONVERTER
// andr-be 07/2023
/*
    converts a typed message into what I understand
    1337 
*/

#include <stdio.h>
#include <ctype.h>

char leet_switch(char);

int main(void)
{
    char buff[96];
    printf("Enter message: ");
    fgets(buff, 95, stdin);
    for (int i = 0; i < 95; i++) {
        if (buff[i] == '\0') break;
        buff[i] = leet_switch(buff[i]);
    }    

    printf("In 1337-speak: %s!!!!1!!", buff);
    return 0;
}

char leet_switch(char input) {
    switch (toupper(input))
    {
    case  'A': return '4';
    case  'B': return '8';
    case  'E': return '3';
    case  'I': return '!';
    case  'L': return '1';
    case  'O': return '0';
    case  'S': return '5';
    case  'T': return '7';
    case '\n': return '!';

    default: 
        return (char) toupper(input);
    }
}
