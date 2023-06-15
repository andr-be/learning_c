// THE CRASH PROGRAM
// andr-be 06/2023      
/* 
    - this program crashes    
    - that's it that's the program
*/

#include <stddef.h>

int main(void)
{
    int *p;
    p = NULL;
    *p = 12;    // crash?!
}