// PRINT THE SIZE OF TYPES
// andr-be 07/2023

#include <stdio.h>

int main(void)
{
    int i;          printf("SIZE OF INT:\t\t %2lld\n", sizeof(i));

    short s;        printf("SIZE OF SHORT:\t\t %2lld\n", sizeof(s));

    long l;         printf("SIZE OF LONG:\t\t %2lld\n", sizeof(l));

    float f;        printf("SIZE OF FLOAT:\t\t %2lld\n", sizeof(f));

    double d;       printf("SIZE OF DOUBLE:\t\t %2lld\n", sizeof(d));

    long double ld; printf("SIZE OF L-DOUBLE:\t %2lld\n", sizeof(ld));
    
    return 0;
}
