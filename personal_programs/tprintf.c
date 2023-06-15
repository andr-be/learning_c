// TPRINTF -> THE PRINT FACTORY
// andr-be 06/2023
/*
    I'm not entirely sure what the purpose of this program was in the beginning
    now it's taken on the form of a weird cycle counter
    might be cool for a command line application or debugger output?

    It has timestamps!
*/

#include <stdio.h>
#include <windows.h>
#include <time.h>

#define MAX_ITER    1000
#define DELAY_MS    1
#define BUFF_SIZE   32
#define SLEEP       Sleep(DELAY_MS)
#define U_SLEEP     Sleep(DELAY_MS/20)
#define MILESTONE_1 100
#define MILESTONE_2 10

char* timestamp(void);

int main(void)
{
    int counter = 0, c_milestone = 1;
    while (counter < MAX_ITER + 1) {
        char* prompt = (char*)malloc(BUFF_SIZE * sizeof(char));
        snprintf(prompt, BUFF_SIZE, "CYCLE %5d", counter);
        printf("%s", prompt);
        SLEEP;

        if (counter % MILESTONE_2 == 0)
            printf("\t%s", timestamp());

        if (counter % MILESTONE_1 == 0)
            printf("\tMILESTONE %2d\n", c_milestone++);

        for (int i = 0; i < BUFF_SIZE; i++) {
            printf("\b");
            U_SLEEP;
        }
        SLEEP;

        counter++;
        free(prompt);
    }
    return 0;
}

char* timestamp(void)
{
    time_t raw_start_time;
    struct tm *rst;
    char *string;
    string = malloc(sizeof(char) * 80);

    time ( &raw_start_time );
    rst = localtime( &raw_start_time );
    strftime(string, 80, "%X", rst);

    return string;
}