// String Variables as Arrays

int main(void)
{
    char *s = "Hello, world!";
    printf("%s\n", s);  // "Hello, world!"

    // if we're lazy the compilter will do this for us
    char t[] = "\nThis is a test!\n";
    printf("%s\n", t);

    for (int i = 0; i < 13; i++)
        // format specifer %c to print single character
        printf("%c\n", s[i]);   

    for (int j = 0; j < 16; j++)
        printf("%c\n", t[j]);
}