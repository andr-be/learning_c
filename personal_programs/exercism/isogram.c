#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_LETTERS 18
#define NUM_LETTERS 26

bool is_isogram(const char phrase[])
{
    int letters[NUM_LETTERS] = {0};
    if (phrase == NULL) return false;

    // populate letter count array
    for (int i = 0; i < MAX_LETTERS; i++) {
        if (phrase[i] == '\0') break;
        char next = (char) toupper(phrase[i]);
        if (isalpha(next)) letters[next - 'A']++;
    }
    // check all letters are below 2
    for (int i = 0; i < NUM_LETTERS; i++)
        if (letters[i] > 1) return false;

    return true;
}

int main(void) {
    bool hello = is_isogram("HELLO");
    bool isogram = is_isogram("isogram");
    bool blank = is_isogram("");
    bool _null = is_isogram(NULL);

    printf("hello: %d\n", hello);
    printf("isogram: %d\n", isogram);
    printf(" : %d\n", blank);
    printf("NULL: %d\n", _null);
}