// ISBN GENERATOR PARSER
// andr-be 06/2023
/*
    This program simply accepts a standard ISBN number and structures that data.
    Another function allows you to display the different fields of the struct.
*/

#include <stdio.h>
#include <stdlib.h>

struct ISBN {
    int GS1;
    int GROUP;
    int PUBLISHER;
    int ITEM_NO;
    int CHECK_DIG;
};

struct ISBN get_isbn(void);
void display_isbn(struct ISBN);

int main(void)
{
    struct ISBN entry = get_isbn();
    display_isbn(entry);
    return 0;
}

struct ISBN get_isbn(void)  
{
    int gs1, group, publisher, item_no, check_dig;
    printf("Enter ISBN:  ");
    scanf("%d-%d-%d-%d-%d", &gs1, &group, &publisher, &item_no, &check_dig);
    struct ISBN new_isbn = {gs1, group, publisher, item_no, check_dig};
    return new_isbn;
}

void display_isbn(struct ISBN input)
{
    printf("GS1 prefix: %d\n", input.GS1);
    printf("Group identifier: %d\n", input.GROUP);
    printf("Publisher code: %d\n", input.PUBLISHER);
    printf("Item number: %d\n", input.ITEM_NO);
    printf("Check digit: %d\n", input.CHECK_DIG);
}