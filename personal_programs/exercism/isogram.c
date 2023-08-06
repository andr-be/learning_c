#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_LETTERS 18
#define NUM_LETTERS 26

bool is_isogram(const char phrase[])
{
    if (!phrase) return false;
    for (int i = 0, letters[NUM_LETTERS] = {0}; i < MAX_LETTERS; i++) 
    {
      if (!phrase[i]) break;
      char next = (char) toupper(phrase[i]);
      if (isalpha(next))
        if (++letters[next - 'A'] > 1)
          return false;
    }
    return true;
}

int main(void) 
{
  printf("hello: %s\n", is_isogram("HELLO") ? "true" : "false");
  printf("isogram: %s\n", is_isogram("isogram") ? "true" : "false");
  printf(" : %s\n", is_isogram("") ? "true" : "false");
  printf("NULL: %s\n", is_isogram(NULL) ? "true" : "false");
}