#include <stdio.h>

int main(void) {
    char *tester = "123456789";

    for(char *t = tester; *t; t++)
        printf("%c ", *t);
}