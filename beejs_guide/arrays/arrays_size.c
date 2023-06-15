// Size of Arrays

#include <stdio.h>

void get_size_of_array(int x[12]);

int main(void)
{
    int x[12];

    printf("%zu\n", sizeof x);                  // 48 total abytes
    printf("%zu\n", sizeof(int));               // 4 bytes per int      
    printf("%zu\n", sizeof x / sizeof(int));    // 48 / 4 = 12 ints!

    get_size_of_array(x);     // this doesn't work, why not?                                   
}

// this function demonstrates that you can get an array size when passed a pointer
// to one, because it just gets the size of the pointer to the array...
void get_size_of_array(int x[12])
{
    printf("%zu\n", sizeof x);                  // 8? but where's 48 gone?
    printf("%zu\n", sizeof(int));               // 4 bytes per int  
    printf("%zu\n", sizeof x / sizeof(int));    // 8/4 = 2 ints? we've lost 10?
}