// condensed pointer arithmetic extension finder
// andr-be 11/2023
/*
    Decided to write the most elegant versions of the written exercise
    questions from chapter 13. I think broadly I've accomplished my goal.
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void get_extension(const char *file_name, char *extension)
{
  char const *s = file_name;
  bool copy = false;
  int i = 0;

  while (*s++) {
    if (copy)
        extension[i++] = *s;

    if (*s == '.') {
        copy = true;
        strcpy(extension, "");
        i = 0;
    }
  }
}

bool test_extension(const char *file_name, const char *extension)
{
  char const *f = file_name + strlen(file_name) - strlen(extension);
  char const *e = extension;

  while(*f)
    if (toupper(*f++) != toupper(*e++)) 
      return false;
  
  return true;
}

void remove_filename(char *url)
{
  for (char *u = url + strlen(url); u - url > 0; u--)
    if (*u == '/') { 
      *u = '\0'; 
      return; 
    }
}

int main(int argc, char const *argv[])
{    
    if (argc != 2) return -1;

    char extension[8] = {0};
    get_extension(argv[1], extension);

    printf("filename: %s\n", argv[1]);
    printf("extension: %s\n", extension);
    if (test_extension(argv[1], "PNG"))
        printf("PNG file detected!\n");

    char url[] = "http://www.knking.com/index.html";
    printf("filename: %s\n", url);
    remove_filename(url);
    printf("removed: %s\n", url);

    return 0;
}
