// Passing Structs to Functions
//  if you have a struct, use a dot operator (.)
//  if you have a pointer to a struct, use the arrow (->)

#include <stdio.h>

struct car {
    char *name;
    float price;
    int speed;
};

void set_price_idiomatically(struct car *c, float new_price);

int main(void)
{
    struct car saturn = {.speed=175, .name="Saturn SL/2"};
    // pass a pointer to this struct car, along with a new
    // more realistic price
    set_price_idiomatically(&saturn, 799.99);
    printf("Price: %.2f\n", saturn.price);

    // structs can be copied simply by assigning to another
    // this is a shallow copy, not a deep copy!
    struct car b = saturn;
    printf("\n%s", b.name);
}

// THIS CAUSES A COMPILATION ERROR
/*  void set_price_crash(struct car *c, float new_price) {
        c.price = new_price; // ERROR!
    } 
*/

// both of these work exactly the same way, but the latter
// is considered best practice.
void set_price_ugly(struct car *c, float new_price) {
    (*c).price = new_price;
}

void set_price_idiomatically(struct car *c, float new_price) {
    c->price = new_price;
}
