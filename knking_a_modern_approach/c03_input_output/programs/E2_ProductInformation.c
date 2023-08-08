// PRODUCT INFORMATION FORMATTER
// andr-be 06/2023
/*
    Made use of some good encapsulation to create a really slick main()
    for this problem. My string generation code seems fairly portable;
    would probably be cool to write a real function that can do it based
    on an arbitrary number of arguments!
*/

#include <stdio.h>
#include <stdlib.h>

struct Date {
    int DAY;
    int MONTH;
    int YEAR;
};

int get_item_number(void);
float get_unit_price(void);
struct Date get_date(void);
char* generate_summary(int, float, struct Date);

int main(void)
{
    int item_no = get_item_number();
    float unit_price = get_unit_price();
    struct Date purchase_date = get_date();
    char* summary = generate_summary(item_no, unit_price, purchase_date);
    printf("%s", summary);
}

int get_item_number(void){
    int item_no;
    printf("Enter item number:  ");
    scanf("%d", &item_no);
    return item_no;
}

float get_unit_price(void){
    float unit_price;
    printf("Enter unit price:  ");
    scanf("%f", &unit_price);
    return unit_price;
}

struct Date get_date(void){
    int mm, dd, yyyy;
    printf("Enter purchase date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &dd, &mm, &yyyy);
    struct Date new_date = {dd, mm, yyyy};
    return new_date;
}

char* generate_summary(int item_no, float unit_price, struct Date purchase_date)
{
    int buff_size = 100;
    char* summary = (char*)malloc(buff_size * sizeof(char));
    snprintf(
        summary, 
        buff_size, 
        "\nItem\t\tUnit\t\tPurchase\n\t\tPrice\t\tDate\n%d\t\t$%6.2f\t\t%0.2d/%0.2d/%0.4d\n", 
        item_no, unit_price, 
        purchase_date.DAY, purchase_date.MONTH, purchase_date.YEAR
    );
    return summary;
}

