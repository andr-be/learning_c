#include <stdio.h>


int main(void)
{
    int hr, min;
    char pm;
    scanf("%2d:%2d %c", &hr, &min, &pm);
    if (pm == 'p') hr += 12;
    printf("%d:%d %c", hr, min, pm);

    return 0;
}
