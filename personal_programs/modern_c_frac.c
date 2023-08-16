// MODERN C STYLE FRACTION CALCULATOR
// andr-be 08/2023
/*
    After watching a talk on Modern C conventions by Luca Sas, 
    I was inspired to re-write this calculator to implement
    some of the stylistic conventions of the community that uses 
    and works with C daily in 2023.

    update 16/08/23: fixed logic errors in program
*/

#include <stdio.h>

#define OPTION_NUM 6
#define OPTION_BUF 40

typedef struct frac { int n, d; } frac;
typedef struct two_fracs { frac l, r; } two_fracs;

void title(void);
int menu(void);
frac from_user(void);
frac from_ints(int n, int d);
frac frac_addi(frac l, frac r);
frac frac_mult(frac l, frac r);
frac frac_divi(frac l, frac r);
frac frac_subt(frac l, frac r);
frac frac_simp(frac input);
int gcd(int a, int b);
void frac_prnt(frac input);
two_fracs get_two(void);

int main(void)
{
    frac result = {0};
    two_fracs couple = {0};
    title();
    for(;;)
        switch (menu())
        {
        case -1: // EXIT
            return 0;
        case 1:  // ADDITION
            couple = get_two();
            result = frac_addi(couple.l, couple.r);
            break;
        case 2:  // SUBTRACTION
            couple = get_two();
            result = frac_subt(couple.l, couple.r);
            break;
        case 3:  // MULTIPLICATION
            couple = get_two();
            result = frac_mult(couple.l, couple.r);
            break;
        case 4:  // DIVISION
            couple = get_two();
            result = frac_divi(couple.l, couple.r);
            break;
        case 5:  // SIMPLIFY
            result = from_user();
            break;
        default: 
            frac_prnt( frac_simp(result) );
        }
}

int menu(void) {
    int choice = 0; 
    const char options[OPTION_NUM][OPTION_BUF] = 
    {
        "\n 1: ADD", 
        "\n 2: SUBTRACT", 
        "\n 3: MULTIPLY",
        "\n 4: DIVIDE",
        "\n 5: SIMPLIFY",
        "\n-1: EXIT",
    };
    for (int i = 0; i < OPTION_NUM; i++){
        printf("%s", options[i]);
    } 
    printf("\n    ENTER A CHOICE: ");
    scanf("%d", &choice);
    return choice;
}

void title(void) {
    printf("\nFRACTION CALCULATOR\n// andr-be 2023");
}

frac from_user(void){
    int n, d;
    printf("ENTER FRACTION (x/y): ");
    scanf("%d/%d", &n, &d);
    return from_ints(n, d);
}

two_fracs get_two(void){
    frac l = { 0 }, r = { 0 };

    printf("ENTER TWO FRACTIONS (x/y a/b): ");
    scanf("%d/%d %d/%d", &l.n, &l.d, &r.n, &r.d);
    l.d = (l.d == 0) ? 1 : l.d;
    r.d = (r.d == 0) ? 1 : l.d;
    two_fracs result = { l, r };
    return result;
}

frac from_ints(int n, int d)
{
    frac result = { .n = n, .d = (d == 0) ? 1 : d };
    return result;
}

frac frac_addi(frac l, frac r)
{
    frac result = { 
        .n = l.n * r.d + r.n * l.d,
        .d = l.d * r.d
    };
    return result;
}

frac frac_mult(frac l, frac r)
{
    frac result = {
        .n = l.n * r.n,
        .d = l.d * r.d
    };
    return result;
}

frac frac_divi(frac l, frac r)
{
    frac r_flip = { r.d, r.n };
    return frac_mult(l, r_flip);
}

frac frac_subt(frac l, frac r)
{
    frac result = {
        .n = l.n * r.n - r.n * l.d,
        .d = l.d * r.d
    };
    return result;
}

frac frac_simp(frac input)
{
    int divisor = gcd(input.n, input.d);
    frac result = {input.n / divisor, input.d / divisor};
    return result;
}

int gcd(int a, int b)
{
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void frac_prnt(frac input)
{
    printf("\nRESULT: %d/%d\n", input.n, input.d);
}