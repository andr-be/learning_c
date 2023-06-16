// BROKER V2
// andr-be 06/2023
/*
    A few syntactical and lexical experiments going on here
    with control flows. I like that C allows me to put
    stuff basically wherever I want and fuck you if that's
    nonstandard lmao
*/

#include <stdio.h>

float get_my_commission(float);
float get_rival_commission(float);

int main(void)
{
    float my_commission = 0, 
          rival_commission = 0, 
          share_price = 0, 
          value = 0, 
          num_shares = 0;

    while(1){
        printf("Enter number of shares & price per share e.g. 10 @ 23.4 ");
        scanf("%f @ %f", &num_shares, &share_price);

        value = num_shares * share_price;
        printf("\n%.2f  %.2f  %.2f\n", value, num_shares, share_price);
        my_commission = get_my_commission(value);
        rival_commission = get_rival_commission(num_shares);

        printf("Our Commission:   $%.2f\n", my_commission);
        printf("Rival Commission: $%.2f\n\n", rival_commission);
        fflush(stdin);
    }

    return 0;
}

float get_my_commission(float value)
{
    float commission;
    if (value < 2500.00f)        commission = 30.00f  + 0.17f * value;
    else if (value < 6250.00f)   commission = 56.00f  + 0.66f * value;
    else if (value < 20000.00f)  commission = 76.00f  + 0.34f * value;
    else if (value < 50000.00f)  commission = 100.00f + 0.22f * value;
    else if (value < 500000.00f) commission = 155.00f + 0.11f * value;
    else                         commission = 255.00f + 0.09f * value;
    if (commission < 39.00f)     commission = 39.00f;

    return commission;
}

float get_rival_commission(float num_shares) {
    float base_commission = 33.00f,
          base_rate_fee   = 0.03f, 
          big_order_fee   = 0.02f,
          bo_breakpoint   = 2000.0f;

    return base_commission += (num_shares < bo_breakpoint)
        ? base_rate_fee * num_shares
        : big_order_fee * num_shares;
}
