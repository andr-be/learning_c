#include <stdio.h>
#include <string.h>

int censor(char str[])
{
  int edits = 0;

  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == 'f' && str[i + 1] == 'o' && str[i + 2] == 'o') {
      for (int j = 0; j < 3; j++)  {
        str[i++] = 'x';
      }
      edits++;
    }
  }

  return edits;
}

int main(int argc, char const *argv[])
{
    if (argc == 2) {
        printf("You entered: %s\n", argv[1]);
        char censored[128];
        strcpy(censored, argv[1]);
        int edits = censor(censored);
        printf("%d replacements made!\n", edits);
        printf("Your new string: %s", censored);
    } else {
        printf("Invalid number of arguments.\n");
    }
    return 0;
}
