#include <stdint.h>
#include <stdio.h>

#define NUM_SQUARES 64

uint64_t square(uint8_t index)
{
    if (!index) return 0;
    
    uint64_t sum = 1;

    for (uint8_t i = 1; i < index && i < NUM_SQUARES; i++)
        sum = sum << 1;

    return sum;
}


uint64_t total(void)
{
    uint64_t total = 0;
    
    for (uint8_t i = 1; i <= NUM_SQUARES; i++)
    {
        total += square(i);
    }
    
    return total;
}

int main(void) 
{
    printf("%I64u", total());
}